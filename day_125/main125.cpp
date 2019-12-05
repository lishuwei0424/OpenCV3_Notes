/*
OpenCV-day-125

OpenCV DNN 基于SSD实现实时视频检测

OpenCV DNN模块支持常见得对象检测模型SSD， 以及它的移动版Mobile Net-SSD，特别是后者在端侧边缘设备上可以实时计算，基于Caffe训练好的mobile-net SSD支持20类别对象检测，其模型下载地址如下：
opencv_tutorial/data/models/ssd at master · gloomy...

SSD的mobilenet版本不仅可以检测图像，还可以检测视频，达到稳定实时的效果，基于124的分享内容，我稍微做了一下改动实现了在Python与C++中的基于SSD视频对象检测的代码，详细参见源码zip文件即可。
介绍一个API， 获取网络各层执行时间与总的执行时间API:
int64 cv::dnn::Net::getPerfProfile(
	std::vector< double > & timings
)
返回值是网络执行推断的时间
Timings是网络对应的各层执行时间

PS：祝大家周末愉快，下周继续更新！
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
	// load model
	Net net = readNetFromCaffe(model_text_file, modelFile);
	net.setPreferableBackend(DNN_BACKEND_OPENCV);
	net.setPreferableTarget(DNN_TARGET_CPU);

	VideoCapture cap = VideoCapture(1);
	Mat frame;
	while (true) {
		bool ret = cap.read(frame);
		if (!ret) break;
		Mat blobImage = blobFromImage(frame, 0.007843,
			Size(300, 300),
			Scalar(127.5, 127.5, 127.5), true, false);
		printf("blobImage width : %d, height: %d\n", blobImage.size[2], blobImage.size[3]);

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
		imshow("ssd-video-demo", frame);
		char c = waitKey(10);
		if (c == 27) {
			break;
		}
	}

	waitKey(0);
	destroyAllWindows();

	return 0;
}