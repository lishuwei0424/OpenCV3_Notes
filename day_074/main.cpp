/*
二值图像分析 – 提取最大轮廓与编码关键点
这个问题来自大概四年前一个网友问我得，他需要提取星云的面积，做一些计算，其实在图像二值化的时候，我们需要考虑下面的因素，二值化方法选择：
全局阈值二值化
基于形态学梯度二值化
inRange二值化
基于Canny边缘二值化
自适应二值化

我们在二值化方法选择上选择了全局阈值（希望大家可以尝试更多不同二值化方法做对比），得到二值图像，然后进行轮廓分析，根据面积寻找最大轮廓，然后
根据轮廓进行多边形逼近，获得轮廓关键点，最后可以绘制轮廓与关键点。首先看代码实现，然后再看原图与绘制效果。
*/
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat src = imread("../images/gaoyy.png");
	imshow("input", src);

	// 二值图像
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary", binary);

	// 定义结构元素
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(binary, binary, MORPH_CLOSE, se);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
	int height = src.rows;
	int width = src.cols;
	int index = -1;
	int max = 0;
	for (size_t t = 0; t < contours.size(); t++) {
		Rect rect = boundingRect(contours[t]);
		if (rect.height >= height || rect.width >= width) {
			continue;
		}
		double area = contourArea(contours[t]);
		if (area > max) {
			max = area;
			index = t;
		}
	}
	Mat result = Mat::zeros(src.size(), src.type());
	Mat pts;
	drawContours(src, contours, index, Scalar(0, 0, 255), 1, 8);
	approxPolyDP(contours[index], pts, 4, true);
	for (int i = 0; i < pts.rows; i++) {
		Vec2i pt = pts.at<Vec2i>(i, 0);
		circle(src, Point(pt[0], pt[1]), 2, Scalar(0, 255, 0), 2, 8, 0);
		circle(result, Point(pt[0], pt[1]), 2, Scalar(0, 255, 0), 2, 8, 0);
	}
	imshow("result", src);
	waitKey(0);
	destroyAllWindows();

	return 0;
}