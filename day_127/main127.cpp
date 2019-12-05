/*
OpenCV DNN 基于残差网络的视频人脸检测

OpenCV在DNN模块中提供了基于残差SSD网络训练的人脸检测模型，还支持单精度的fp16的检测准确度更好的Caffe模型加载与使用，这里实现了一个基于Caffe Model的视频实时人脸监测模型，基于Python与C++代码CPU运行，帧率均可以到达15以上。非常好用。

昨天微信公众号的文章：
两种移动端可以实时运行的网络模型
两种移动端可以实时运行的网络模型
*/

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>

using namespace cv;
using namespace cv::dnn;
using namespace std;

const size_t width = 300;
const size_t height = 300;
String model_bin = "../models/face_detector/res10_300x300_ssd_iter_140000_fp16.caffemodel";
String config_text = "../models/face_detector/deploy.prototxt";

int main(int argc, char** argv) {

	VideoCapture capture = VideoCapture(0);
	namedWindow("ssd-face-video", WINDOW_AUTOSIZE);

	Net net = readNetFromCaffe(config_text, model_bin);
	net.setPreferableBackend(DNN_BACKEND_INFERENCE_ENGINE);
	net.setPreferableTarget(DNN_TARGET_CPU);
	Mat frame;
	while (true) {
		capture.read(frame);
		Mat blobImage = blobFromImage(frame, 1.0,
			Size(300, 300),
			Scalar(104.0, 177.0, 123.0), false, false);

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
				putText(frame, format(" confidence %.2f", confidence),
					Point(tl_x - 10, tl_y - 5), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 1, 8);
			}
		}
		char c = waitKey(5);
		if (c == 27) {
			break;
		}
		imshow("ssd-face-video", frame);
	}

	waitKey(0);
	destroyAllWindows();

	return 0;
}