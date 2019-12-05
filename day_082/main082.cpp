/*
角点检测 – shi-tomas角点检测
Harris角点检测是一种计算速度很慢的角点检测算法，很难实时计算，所有最常用的是shi-tomas角点检测算法，它的运行速度很快。
OpenCV中相关API与解释如下：
void cv::goodFeaturesToTrack(
	InputArray image,
	OutputArray corners,
	int maxCorners,
	double qualityLevel,
	double minDistance,
	InputArray mask = noArray(),
	int blockSize = 3,
	bool useHarrisDetector = false,
	double k = 0.04
)
src单通道输入图像，八位或者浮点数
corners是输出的关键点坐标集合
maxCorners表示最大返回关键点数目
qualityLevel表示拒绝的关键点 R < qualityLevel × max response将会被直接丢弃
minDistance 表示两个关键点之间的最短距离
mask 表示mask区域，如果有表明只对mask区域做计算
blockSize 计算梯度与微分的窗口区域
useHarrisDetector 表示是否使用harris角点检测，默认是false 为shi-tomas
k = 0.04默认值，当useHarrisDetector为ture时候起作用

PS: 新的一周，我们一起努力！
*/

#include <opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;
void process_frame(Mat &image, int opts);
RNG rng(12345);
int main(int argc, char** argv) {
	VideoCapture capture("D:/images/video/color_object.mp4");

	if (!capture.isOpened()) {
		printf("could not open camera...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	namedWindow("result", WINDOW_AUTOSIZE);

	int fps = capture.get(CAP_PROP_FPS);
	int width = capture.get(CAP_PROP_FRAME_WIDTH);
	int height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int num_of_frames = capture.get(CAP_PROP_FRAME_COUNT);
	printf("frame width: %d, frame height: %d, FPS : %d \n", width, height, fps);

	Mat frame;
	while (true) {
		bool ret = capture.read(frame);
		imshow("input", frame);
		if (!ret) break;

		process_frame(frame, 0);
		imshow("result", frame);
		char c = waitKey(5);
		if (c == 27) {
			break;
		}
	}

	waitKey(0);
	destroyAllWindows();

	return 0;
}


void process_frame(Mat &image, int opts) {
	// Detector parameters
	int maxCorners = 100;
	double quality_level = 0.01;
	double minDistance = 0.04;

	// Detecting corners
	Mat gray, dst;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	vector<Point2f> corners;
	goodFeaturesToTrack(gray, corners, maxCorners, quality_level, minDistance, Mat(), 3, false);
	for (int i = 0; i < corners.size(); i++) {
		int b = rng.uniform(0, 256);
		int g = rng.uniform(0, 256);
		int r = rng.uniform(0, 256);
		circle(image, corners[i], 5, Scalar(b, g, r), 3, 8, 0);
	}
}
