/*
OpenCV DNN 基于SSD实现对象检测

OpenCV DNN模块支持常见得对象检测模型SSD， 以及它的移动版Mobile Net-SSD，特别是后者在端侧边缘设备上可以实时计算，基于Caffe训练好的mobile-net SSD支持20类别对象检测，其模型下载地址如下：
opencv_tutorial/data/models/ssd at master · gloomy...

加载网络之后，推断调用的关键API如下：
Mat cv::dnn::Net::forward(
const String & 	outputName = String()
)
参数缺省值为空

对对象检测网络来说：
该API会返回一个四维的tensor，前两个维度是1，后面的两个维度，分别表示检测到BOX数量，以及每个BOX的坐标，对象类别，得分等信息。这里需要特别注意的是，这个坐标是浮点数的比率，不是像素值，所以必须转换为像素坐标才可以绘制BOX/矩形。

PS:给大家推荐一篇关于OpenCV DNN加速的文章，欢迎转发
使用OpenVINO ToolKit 实时推断

请关注【OpenCV学堂】微信公众号，即时获取更多信息

*/

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>

using namespace cv;
using namespace cv::dnn;
using namespace std;

const size_t width = 300;
const size_t height = 300;
String labelFile = "../models/ssd/labelmap_det.txt";
String modelFile = "../models/ssd/MobileNetSSD_deploy.caffemodel";
String model_text_file = "../models/ssd/MobileNetSSD_deploy.prototxt";

String objNames[] = { "background",
"aeroplane", "bicycle", "bird", "boat",
"bottle", "bus", "car", "cat", "chair",
"cow", "diningtable", "dog", "horse",
"motorbike", "person", "pottedplant",
"sheep", "sofa", "train", "tvmonitor" };

int main(int argc, char** argv) {
	Mat frame = imread("../data/chicky_512.png");
	if (frame.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input image", WINDOW_AUTOSIZE);
	imshow("input image", frame);

	Net net = readNetFromCaffe(model_text_file, modelFile);
	net.setPreferableBackend(DNN_BACKEND_INFERENCE_ENGINE);
	net.setPreferableTarget(DNN_TARGET_CPU);
	Mat blobImage = blobFromImage(frame, 0.007843,
		Size(300, 300),
		Scalar(127.5, 127.5, 127.5), true, false);
	printf("blobImage width : %d, height: %d\n", blobImage.cols, blobImage.rows);

	net.setInput(blobImage, "data");
	Mat detection = net.forward("detection_out");
	vector<double> layersTimings;
	double freq = getTickFrequency() / 1000;
	double time = net.getPerfProfile(layersTimings) / freq;
	printf("execute time : %.2f ms\n", time);


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
			rectangle(frame, object_box, Scalar(0, 0, 255), 2, 8, 0);
			putText(frame, format(" confidence %.2f, %s", confidence, objNames[objIndex].c_str()), Point(tl_x - 10, tl_y - 5), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 0, 0), 2, 8);
		}
	}
	imshow("ssd-demo", frame);

	waitKey(0);
	destroyAllWindows();

	return 0;
}