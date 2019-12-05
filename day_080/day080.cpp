/*
视频分析 – 背景消除与前景ROI提取

通过视频中的背景进行建模，实现背景消除，生成mask图像，通过对mask二值图像分析实现对前景活动对象ROI区域的提取，是很多视频监控分析软件常用的手段之一，该方法很实时！整个步骤如下：
1.	初始化背景建模对象GMM
2.	读取视频一帧
3.	使用背景建模消除生成mask
4.	对mask进行轮廓分析提取ROI
5.	绘制ROI对象

PS:请关注一下：
在OpenCV4.0中已经没有CV_XXX类型的枚举类型了，希望大家周知！都是直接XXX
举例如下：
CV_WINDOW_AUTOSIZE
去掉CV_ 改用
WINDOW_AUTOSIZE
*/

#include <opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;
void process_frame(Mat &image, int opts);
Ptr<BackgroundSubtractor> pMOG2 = createBackgroundSubtractorMOG2(500, 100, false);
int main(int argc, char** argv) {
	VideoCapture capture("../data/vtest.avi");

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
	Mat mask;
	pMOG2->apply(image, mask);
	// 定义结构元素
	Mat se = getStructuringElement(MORPH_RECT, Size(1, 5), Point(-1, -1));
	morphologyEx(mask, mask, MORPH_OPEN, se);

	// 寻找最大轮廓
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	for (size_t t = 0; t < contours.size(); t++) {
		double area = contourArea(contours[t]);
		if (area < 100) {
			continue;
		}
		RotatedRect rect = minAreaRect(contours[t]);
		ellipse(image, rect, Scalar(0, 255, 0), 2, 8);
		circle(image, rect.center, 2, Scalar(255, 0, 0), 2, 8, 0);
	}
}
