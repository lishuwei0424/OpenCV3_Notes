/*
视频分析KLT光流跟踪02 - 删除静止点与绘制跟踪轨迹

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

在84的知识点分享中我们已经可以跟踪到前后两帧之前的位置移动，但是这个还不足够，我们需要绘制移动对象从初始到最终的完整可以检测的运动轨迹，同时对一些静止的角点进行删除，所以我们需要对状态为1的角点，计算它们之间的距离，只有dx+dy&gt;2（dx=abs(p1.x –p2.x), dy=abs(p1.y-p2.y)）的我们才对它进行保留跟踪。

完整流程图见图3所示！
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
void draw_goodFeatures(Mat &image, vector<Point2f> goodFeatures);
void draw_lines(Mat &image, vector<Point2f> pt1, vector<Point2f> pt2);
vector<Point2f> featurePoints;
vector<Scalar> color_lut;
RNG rng(5000);
int main(int argc, char** argv) {
	VideoCapture capture("../images/video.avi");


	double qualityLevel = 0.01;
	int minDistance = 10;
	int blockSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;
	int maxCorners = 5000;
	Mat frame, gray;
	vector<Point2f> pts[2];
	vector<Point2f> initPoints;
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
	initPoints.insert(initPoints.end(), featurePoints.begin(), featurePoints.end());
	pts[0].insert(pts[0].end(), featurePoints.begin(), featurePoints.end());
	int width = capture.get(CAP_PROP_FRAME_WIDTH);
	int height = capture.get(CAP_PROP_FRAME_HEIGHT);
	VideoWriter writer("D:/test.mp4", VideoWriter::fourcc('D', 'I', 'V', 'X'), 10, Size(width * 2, height), true);
	Mat result = Mat::zeros(Size(width * 2, height), CV_8UC3);
	Rect roi(0, 0, width, height);
	while (true) {
		bool ret = capture.read(frame);
		if (!ret) break;
		imshow("frame", frame);
		roi.x = 0;
		frame.copyTo(result(roi));
		cvtColor(frame, gray, COLOR_BGR2GRAY);

		// calculate optical flow
		calcOpticalFlowPyrLK(old_gray, gray, pts[0], pts[1], status, err, Size(31, 31), 3, criteria, derivlambda, flags);
		size_t i, k;
		for (i = k = 0; i < pts[1].size(); i++)
		{
			// 距离与状态测量
			double dist = abs(pts[0][i].x - pts[1][i].x) + abs(pts[0][i].y - pts[1][i].y);
			if (status[i] && dist > 2) {
				pts[0][k] = pts[0][i];
				initPoints[k] = initPoints[i];
				pts[1][k++] = pts[1][i];
				circle(frame, pts[1][i], 3, Scalar(0, 255, 0), -1, 8);
			}
		}
		// resize 有用特征点
		pts[1].resize(k);
		pts[0].resize(k);
		initPoints.resize(k);
		// 绘制跟踪轨迹
		draw_lines(frame, initPoints, pts[1]);
		imshow("result", frame);
		roi.x = width;
		frame.copyTo(result(roi));
		char c = waitKey(50);
		if (c == 27) {
			break;
		}

		// update old
		std::swap(pts[1], pts[0]);
		cv::swap(old_gray, gray);

		// need to re-init
		if (initPoints.size() < 40) {
			goodFeaturesToTrack(old_gray, featurePoints, maxCorners, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
			initPoints.insert(initPoints.end(), featurePoints.begin(), featurePoints.end());
			pts[0].insert(pts[0].end(), featurePoints.begin(), featurePoints.end());
			printf("total feature points : %d\n", pts[0].size());
		}
		writer.write(result);
	}
	return 0;
}

void draw_goodFeatures(Mat &image, vector<Point2f> goodFeatures) {
	for (size_t t = 0; t < goodFeatures.size(); t++) {
		circle(image, goodFeatures[t], 2, Scalar(0, 255, 0), 2, 8, 0);
	}
}

void draw_lines(Mat &image, vector<Point2f> pt1, vector<Point2f> pt2) {
	if (color_lut.size() < pt1.size()) {
		for (size_t t = 0; t < pt1.size(); t++) {
			color_lut.push_back(Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)));
		}
	}
	for (size_t t = 0; t < pt1.size(); t++) {
		line(image, pt1[t], pt2[t], color_lut[t], 2, 8, 0);
	}
}