/*
视频分析 – 稠密光流分析

光流跟踪方法分为稠密光流跟踪与稀疏光流跟踪算法，KLT是稀疏光流跟踪算法，前面我们已经介绍过了，OpenCV还支持稠密光流的移动对象跟踪方法，
OpenCV中支持的稠密光流算法是由Gunner Farneback在2003年提出来的，它是基于前后两帧所有像素点的移动估算算法，其效果要比稀疏光流算法更好，相关的API如下：
void cv::calcOpticalFlowFarneback(
	InputArray 	prev,
	InputArray 	next,
	InputOutputArray 	flow,
	double 	pyr_scale,
	int 	levels,
	int 	winsize,
	int 	iterations,
	int 	poly_n,
	double 	poly_sigma,
	int 	flags
)
prev 前一帧
next 后一帧
flow 光流，计算得到的移动能量场
pyr_scale 金字塔放缩比率
levels 金字塔层级数目
winsize 表示窗口大小
iterations 表示迭代次数
poly_n 表示光流生成时候，对邻域像素的多项式展开，n越大越模糊越稳定
poly_sigma 表示光流多项式展开时候用的高斯系数，n越大，sigma应该适当增加
flags有两个OPTFLOW_USE_INITIAL_FLOW表示使用盒子模糊进行初始化光流
OPTFLOW_FARNEBACK_GAUSSIAN表示使用高斯窗口

PS:这个月每周五的时候事情比较多，延时送上！请大家原谅！
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main(int argc, char** argv) {
	VideoCapture capture("../images/video.avi");

	Mat preFrame, preGray;
	capture.read(preFrame);
	cvtColor(preFrame, preGray, COLOR_BGR2GRAY);
	Mat hsv = Mat::zeros(preFrame.size(), preFrame.type());
	Mat frame, gray;
	Mat_<Point2f> flow;
	vector<Mat> mv;
	split(hsv, mv);
	Mat mag = Mat::zeros(hsv.size(), CV_32FC1);
	Mat ang = Mat::zeros(hsv.size(), CV_32FC1);
	Mat xpts = Mat::zeros(hsv.size(), CV_32FC1);
	Mat ypts = Mat::zeros(hsv.size(), CV_32FC1);
	while (true) {
		bool ret = capture.read(frame);
		if (!ret) break;
		imshow("frame", frame);
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		calcOpticalFlowFarneback(preGray, gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
		for (int row = 0; row < flow.rows; row++)
		{
			for (int col = 0; col < flow.cols; col++)
			{
				const Point2f& flow_xy = flow.at<Point2f>(row, col);
				xpts.at<float>(row, col) = flow_xy.x;
				ypts.at<float>(row, col) = flow_xy.y;
			}
		}
		cartToPolar(xpts, ypts, mag, ang);
		ang = ang * 180.0 / CV_PI / 2.0;
		normalize(mag, mag, 0, 255, NORM_MINMAX);
		convertScaleAbs(mag, mag);
		convertScaleAbs(ang, ang);
		mv[0] = ang;
		mv[1] = Scalar(255);
		mv[2] = mag;
		merge(mv, hsv);
		Mat bgr;
		cvtColor(hsv, bgr, COLOR_HSV2BGR);
		imshow("result", bgr);
		int ch = waitKey(5);
		if (ch == 27) {
			break;
		}
	}
	waitKey(0);
	destroyAllWindows();

	return 0;
}