/*
视频读写与处理

OpenCV中对视频内容的处理本质上对读取视频的关键帧进行解析图像，然后对图像进行各种处理，OpenCV的VideoCapture是
一个视频读取与解码的API接口，支持各种视频格式、网络视频流、摄像头读取。正常的视频处理与分析，主要是针对读取到
每一帧图像，衡量一个算法处理是否能够满足实时要求的时候通常通过FPS（每秒多少帧的处理能力）。一般情况下每秒大于
5帧基本上可以认为是在进行视频处理。

PS: 2018年最后一个月，我们一起努力！！
*/
#include <opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;
void process_frame(Mat &image, int opts);
int main(int argc, char** argv) {
	VideoCapture capture(1);

	if (!capture.isOpened()) {
		printf("could not open camera...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);

	int fps = capture.get(CAP_PROP_FPS);
	int width = capture.get(CAP_PROP_FRAME_WIDTH);
	int height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int num_of_frames = capture.get(CAP_PROP_FRAME_COUNT);

	printf("frame width: %d, frame height: %d, FPS : %d \n", width, height, fps);

	Mat frame;
	int index = 2;
	while (true) {
		bool ret = capture.read(frame);
		if (!ret) break;
		imshow("input", frame);
		char c = waitKey(50);
		if (c >= 49) {
			index = c - 49;
		}
		process_frame(frame, index);
		imshow("result", frame);
		if (c == 27) {
			break;
		}
	}

	waitKey(0);
	destroyAllWindows();

	return 0;
}

void process_frame(Mat &image, int opts) {
	Mat dst = image.clone();
	if (opts == 0) {
		bitwise_not(image, dst);
	}
	if (opts == 1) {
		GaussianBlur(image, dst, Size(0, 0), 15);
	}
	if (opts == 2) {
		Canny(image, dst, 100, 200);
	}
	dst.copyTo(image);
	dst.release();
}
