/*
二值图像分析 – 缺陷检测一
大家好，我们这周打算分享二值图像分析的案例，通过这些案例知识把前面所学的知识点串联起来使用，实现有一定工业实用价值的代码。
今天这个也是别人问我的，分为两个部分，一个部分是提取指定的轮廓，第二个部分通过对比实现划痕检测与缺角检测。本次分享主要搞定
第一部分，学会观察图像与提取图像ROI对象轮廓外接矩形与轮廓。
*/

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat src = imread("../images/ce_02.jpg");
	imshow("input", src);

	// 二值图像
	Mat gray, binary, result;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	imshow("binary", binary);

	// 定义结构元素
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(binary, binary, MORPH_OPEN, se);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
	int height = src.rows;
	for (size_t t = 0; t < contours.size(); t++) {
		Rect rect = boundingRect(contours[t]);
		double area = contourArea(contours[t]);
		if (rect.height > (height / 2)) {
			continue;
		}

		if (area < 150)
			continue;
		rectangle(src, rect, Scalar(0, 0, 255), 1, 8, 0);
		drawContours(src, contours, t, Scalar(0, 255, 0), 2, 8);
	}
	// 显示
	imshow("result", src);
	waitKey(0);
	destroyAllWindows();

	return 0;
}