/*
视频分析 - 移动对象的KLT光流跟踪算法

光流跟踪方法分为稠密光流跟踪与稀疏光流跟踪算法，KLT是稀疏光流跟踪算法，这个算法最早是由Bruce D. Lucas and Takeo Kanade两位作者提出来的，所以又被称为KLT。稀疏光流算法工作有三个假设前提条件：
-	亮度恒定
-	短距离移动
-	空间一致性

OpenCV中KLT算法API及其参数解释如下：
void cv::calcOpticalFlowPyrLK(
	InputArray 	prevImg, // 前一帧图像
	InputArray 	nextImg, // 后一帧图像
	InputArray 	prevPts, // 前一帧的稀疏光流点
	InputOutputArray 	nextPts, // 后一帧光流点
	OutputArray 	status, // 输出状态，1 表示正常该点保留，否则丢弃
	OutputArray 	err, // 表示错误
	Size winSize = Size(21, 21), // 光流法对象窗口大小
	int maxLevel = 3, // 金字塔层数，0表示只检测当前图像，不构建金字塔图像
	TermCriteria 	criteria = TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 30, 0.01), // 窗口搜索时候停止条件
	int flags = 0, // 操作标志
	double 	minEigThreshold = 1e-4 // 最小特征值响应，低于最小值不做处理
)

PS:明天介绍如何绘制跟踪轨迹与删除静止点！
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
vector<Point2f> featurePoints;
RNG rng(5000);
int main(int argc, char** argv) {
	VideoCapture capture("../images/video.avi");


	double qualityLevel = 0.01;
	int minDistance = 10;
	int blockSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;
	int maxCorners = 100;
	Mat frame, gray;

	vector<Point2f> pts[2];
	vector<uchar> status;
	vector<float> err;
	TermCriteria criteria = TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 30, 0.01);
	double derivlambda = 0.5;
	int flags = 0;

	// detect first frame and find corners in it
	Mat old_frame, old_gray;
	capture.read(old_frame);
	cvtColor(old_frame, old_gray, COLOR_BGR2GRAY);
	goodFeaturesToTrack(old_gray, featurePoints, maxCorners, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
	pts[0].insert(pts[0].end(), featurePoints.begin(), featurePoints.end());
	int width = capture.get(CAP_PROP_FRAME_WIDTH);
	int height = capture.get(CAP_PROP_FRAME_HEIGHT);
	Rect roi(0, 0, width, height);

	while (true) {
		bool ret = capture.read(frame);
		if (!ret) break;
		imshow("frame", frame);
		roi.x = 0;
		cvtColor(frame, gray, COLOR_BGR2GRAY);

		// calculate optical flow
		calcOpticalFlowPyrLK(old_gray, gray, pts[0], pts[1], status, err, Size(31, 31), 3, criteria, derivlambda, flags);
		size_t i, k;
		for (i = k = 0; i < pts[1].size(); i++)
		{
			// 距离与状态测量
			if (status[i]) {
				pts[0][k] = pts[0][i];
				pts[1][k++] = pts[1][i];
				int b = rng.uniform(0, 256);
				int g = rng.uniform(0, 256);
				int r = rng.uniform(0, 256);
				circle(frame, pts[1][i], 3, Scalar(b, g, r), -1, 8);
				line(frame, pts[0][i], pts[1][i], Scalar(b, g, r), 2, 8, 0);
			}
		}
		// resize 有用特征点
		pts[1].resize(k);
		pts[0].resize(k);
		imshow("result", frame);
		roi.x = width;
		char c = waitKey(50);
		if (c == 27) {
			break;
		}

		// update old
		std::swap(pts[1], pts[0]);
		cv::swap(old_gray, gray);
	}
	return 0;
}