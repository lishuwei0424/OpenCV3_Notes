/*
视频分析 - 背景/前景 提取
视频场景分析中最常用的技术之一就是通过背景消除来提取前景移动对象，得到前景的对象mask图像，最常用的背景消除技术就是通过帧差相减，
用前面一帧作为背景图像，与当前帧进行相减，不过这种方法对光照与噪声影响非常敏感，所有好的办法是通过对前面一系列帧提取背景模型进行
相减，OpenCV中实现的背景模型提取算法有两种，一种是基于高斯混合模型GMM实现的背景提取，另外一种是基于最近邻KNN实现的。都有相关的AP
I可以供开发者使用。
相关API
Ptr<BackgroundSubtractorMOG2> cv::createBackgroundSubtractorMOG2(
int  history = 500,
double 	varThreshold = 16,
bool  detectShadows = true
)
参数解释如下：
history表示过往帧数，500帧，选择history = 1就变成两帧差
varThreshold表示像素与模型之间的马氏距离，值越大，只有那些最新的像素会被归到前景，值越小前景对光照越敏感。
detectShadows 是否保留阴影检测，请选择False这样速度快点。

创建
Ptr<BackgroundSubtractor> pBackSub = createBackgroundSubtractorMOG2();
Ptr<BackgroundSubtractor> pBackSub = createBackgroundSubtractorKNN();

背景消除的基本原理见图一：
*/

#include <opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {

	VideoCapture capture("../images/video.avi");

	if (!capture.isOpened()) {
		printf("could not open camera...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	namedWindow("mask", WINDOW_AUTOSIZE);

	int fps = capture.get(CAP_PROP_FPS);
	int width = capture.get(CAP_PROP_FRAME_WIDTH);
	int height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int num_of_frames = capture.get(CAP_PROP_FRAME_COUNT);
	printf("frame width: %d, frame height: %d, FPS : %d \n", width, height, fps);
	Ptr<BackgroundSubtractor> pMOG2 = createBackgroundSubtractorMOG2(500, 1000, false);
	Mat frame, mask, back_img;
	while (true) {
		bool ret = capture.read(frame);
		if (!ret) break;
		pMOG2->apply(frame, mask);
		pMOG2->getBackgroundImage(back_img);
		imshow("input", frame);
		imshow("mask", mask);
		imshow("back ground image", back_img);
		char c = waitKey(5);
		if (c == 27) {
			break;
		}
	}

	waitKey(0);
	destroyAllWindows();

	return 0;
}