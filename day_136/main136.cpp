/*
OpenCV DNN解析网络输出结果

多数时候DNN模块中深度学习网络的输出结果，可能是二维、三维、或者四维的，具体跟网络的结构有很大的关系，一般常见的图像分类网络，是一个1XN维的向量，通过reshape之后就很容易解析，
解析代码如下：
Mat flat = prob.reshape(1,1)
Point maxLoc;
minMaxLoc(flat, 0, 0, &maxLoc)
int predict = maxLoc.x;

如果是对象检测网络SSD/RCNN/Faster-RCNN网络，输出的是NX7的模式
所以其解析方式如下：
Mat detectionMat(out.size[2]， out.size[3], CV_32F, out.ptr<float>())
就可以解析该结构！

如果对象检测网络是基于Region的YOLO网络，则解析方式变为
Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
前面五个为cx,cy,w, h, objectness

如果模型网络是图像分割的网络，最后一层输出是3通道的图像对象，则解析方式为：
Mat green(224, 224, CV_32F, blob.ptr<float>(0, 1)) // 表示绿色通道！

PS: 今天是对OpenCV DNN各种网络模型输出解析方法的总结！
*/

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>

using namespace cv;
using namespace cv::dnn;
using namespace std;

const size_t width = 300;
const size_t height = 300;
String model_bin = "../models/face_detector/opencv_face_detector_uint8.pb";
String config_text = "../models/face_detector/opencv_face_detector.pbtxt";

String ageProto = "../models/cnn_age_gender_models/age_deploy.prototxt";
String ageModel = "../models/cnn_age_gender_models/age_net.caffemodel";

String genderProto = "../models/cnn_age_gender_models/gender_deploy.prototxt";
String genderModel = "../models/cnn_age_gender_models/gender_net.caffemodel";
String  ageList[] = { "(0-2)", "(4-6)", "(8-12)", "(15-20)", "(25-32)", "(38-43)", "(48-53)", "(60-100)" };
String genderList[] = { "Male", "Female" };
int main(int argc, char** argv) {
	Mat frame = imread("D:/images/dannis2.jpg");
	if (frame.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input image", WINDOW_AUTOSIZE);
	imshow("input image", frame);

	Net net = readNetFromTensorflow(model_bin, config_text);
	net.setPreferableBackend(DNN_BACKEND_OPENCV);
	net.setPreferableTarget(DNN_TARGET_CPU);

	Net ageNet = readNet(ageModel, ageProto);
	Net genderNet = readNet(genderModel, genderProto);

	Mat blobImage = blobFromImage(frame, 1.0,
		Size(300, 300),
		Scalar(104.0, 177.0, 123.0), false, false);

	net.setInput(blobImage, "data");
	Mat detection = net.forward("detection_out");
	vector<double> layersTimings;
	double freq = getTickFrequency() / 1000;
	double time = net.getPerfProfile(layersTimings) / freq;
	printf("execute time : %.2f ms\n", time);
	int padding = 20;
	Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
	float confidence_threshold = 0.5;
	for (int i = 0; i < detectionMat.rows; i++) {
		float confidence = detectionMat.at<float>(i, 2);
		if (confidence > confidence_threshold) {
			size_t objIndex = (size_t)(detectionMat.at<float>(i, 1));
			float tl_x = detectionMat.at<float>(i, 3) * frame.cols;
			float tl_y = detectionMat.at<float>(i, 4) * frame.rows;
			float br_x = detectionMat.at<float>(i, 5) * frame.cols;
			float br_y = detectionMat.at<float>(i, 6) * frame.rows;

			Rect object_box((int)tl_x, (int)tl_y, (int)(br_x - tl_x), (int)(br_y - tl_y));

			Rect roi;
			roi.x = max(0, object_box.x - padding);
			roi.y = max(0, object_box.y - padding);
			roi.width = min(object_box.width + padding, frame.cols - 1);
			roi.height = min(object_box.height + padding, frame.rows - 1);
			Mat face = frame(roi);
			Mat faceblob = blobFromImage(face, 1.0, Size(227, 227), Scalar(78.4263377603, 87.7689143744, 114.895847746), false, false);
			ageNet.setInput(faceblob);
			genderNet.setInput(faceblob);
			Mat agePreds = ageNet.forward();
			Mat genderPreds = genderNet.forward();

			Mat probMat = agePreds.reshape(1, 1);
			Point classNumber;
			double classProb;
			minMaxLoc(probMat, NULL, &classProb, NULL, &classNumber);
			int classidx = classNumber.x;
			String age = ageList[classidx];

			probMat = genderPreds.reshape(1, 1);
			minMaxLoc(probMat, NULL, &classProb, NULL, &classNumber);
			classidx = classNumber.x;
			String gender = genderList[classidx];
			rectangle(frame, object_box, Scalar(0, 0, 255), 2, 8, 0);
			putText(frame, format("age:%s gender:%s", age.c_str(), gender.c_str()), object_box.tl(), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 0, 0), 1, 8);
		}
	}
	imshow("ssd-face-detection", frame);

	waitKey(0);
	destroyAllWindows();

	return 0;
}