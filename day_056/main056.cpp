/*
二值图像分析 – 直线拟合与极值点寻找
对轮廓进行分析，除了可以对轮廓进行椭圆或者圆的拟合之外，还可以对轮廓点集进行直线拟合，直线拟合的算法有很多，最常见的就是最小二乘法，对于多约束线性方程，最小二乘可以找好直线方程的两个参数、实现直线拟合，OpenCV中直线拟合正是基于最小二乘法实现的。OpenCV实现直线拟合的API如下：
void cv::fitLine(
	InputArray points,
	OutputArray line,
	int distType,
	double param,
	double reps,
	double aeps
)
points表示待拟合的输入点集合
line在二维拟合时候输出的是vec4f类型的数据，在三维拟合的时候输出是vec6f的vector
distType表示在拟合时候使用距离计算公式是哪一种，OpenCV支持如下六种方式：
DIST_L1 = 1
DIST_L2 = 2
DIST_L12 = 4
DIST_FAIR = 5
DIST_WELSCH = 6
DIST_HUBER = 7
param对模型拟合距离计算公式需要参数C，5~7 distType需要参数C
reps与aeps是指对拟合结果的精度要求
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("../images/twolines.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}

	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// 去噪声与二值化
	Mat dst, gray, binary;
	Canny(src, binary, 80, 160, 3, false);
	imshow("binary", binary);
	imwrite("D:/binary.png", binary);

	Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	dilate(binary, binary, k);

	// 轮廓发现与绘制
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());

	for (size_t t = 0; t < contours.size(); t++) {
		// 最大外接轮廓
		Rect rect = boundingRect(contours[t]);
		int m = max(rect.width, rect.height);
		if (m < 30) continue;
		// 直线拟合
		Vec4f oneline;
		fitLine(contours[t], oneline, DIST_L1, 0, 0.01, 0.01);
		float vx = oneline[0];
		float vy = oneline[1];
		float x0 = oneline[2];
		float y0 = oneline[3];

		// 直线参数斜率k与截矩b
		float k = vy / vx;
		float b = y0 - k * x0;

		// 寻找轮廓极值点
		int minx = 0, miny = 10000;
		int maxx = 0, maxy = 0;
		for (int i = 0; i < contours[t].size(); i++) {
			Point pt = contours[t][i];
			if (miny > pt.y) {
				miny = pt.y;
			}
			if (maxy < pt.y) {
				maxy = pt.y;
			}
		}
		maxx = (maxy - b) / k;
		minx = (miny - b) / k;
		line(src, Point(maxx, maxy), Point(minx, miny), Scalar(0, 0, 255), 2, 8, 0);
	}
	imshow("contours", src);

	waitKey(0);
	destroyAllWindows();

	return 0;
}