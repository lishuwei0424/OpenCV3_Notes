/*
二值图像分析 – 霍夫直线检测二
OpenCV中还有另外一个霍夫直线检测的API，该API更为常用，它会直接返回直线的空间坐标点，比返回霍夫空间参数更加的直观，容易理解，而且还可以声明线段长度、间隔等参数，非常有用。该参数详解如下：
void cv::HoughLinesP(
	InputArray image,
	OutputArray lines,
	double rho,
	double theta,
	int threshold,
	double 	minLineLength = 0,
	double 	maxLineGap = 0
)
Image输入二值图像
Lines 返回的直线两个点
Rho 极坐标r得步长
Theta角度步长
Threshold累加器阈值
minLineLength最小线段长度
maxLineGap线段间隔
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("../images/morph01.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// 去噪声与二值化
	Mat gray, binary;
	Canny(src, binary, 80, 160, 3, false);
	imshow("binary", binary);
	imwrite("D:/binary.png", binary);

	vector<Vec4i> lines;
	HoughLinesP(binary, lines, 1, CV_PI / 180, 80, 30, 10);
	Mat result = Mat::zeros(src.size(), src.type());
	for (size_t i = 0; i < lines.size(); i++)
	{
		line(result, Point(lines[i][0], lines[i][1]),
			Point(lines[i][2], lines[i][3]), Scalar(0, 255, 0), 1, 8);
	}
	imshow("contours", result);

	waitKey(0);
	destroyAllWindows();

	return 0;
}