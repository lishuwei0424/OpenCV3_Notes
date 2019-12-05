/*
二值图像分析 – 使用轮廓逼近
对图像二值图像的每个轮廓，可以使用轮廓逼近，逼近每个轮廓的真实几何形状，从而通过轮廓逼近的输出结果判断一个对象是什么形状。OpenCV轮廓逼近的API如下：
void cv::approxPolyDP(
	InputArray curve,
	OutputArray approxCurve,
	double epsilon,
	bool closed
)
其中
Curve表示轮廓曲线
approxCurve 表示轮廓逼近输出的顶点数目
epsilon 轮廓逼近的顶点距离真实轮廓曲线的最大距离，该值越小表示越逼近真实轮廓
close 表示是否为闭合区域
C++代码实现部分见第一张图，
Python语言代码实现部分见第二张图：
原图与运行效果见三，四两张图
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
RNG rng(50000);
int main(int argc, const char *argv[])
{
	Mat src = imread("../images/contours.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// 去噪声与二值化
	Mat dst, gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary", binary);
	imwrite("D:/binary.png", binary);

	// 轮廓发现与绘制
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
	Scalar color = Scalar(255, 0, 0);
	for (size_t t = 0; t < contours.size(); t++) {
		RotatedRect rrt = minAreaRect(contours[t]);
		Point2f cpt = rrt.center;
		circle(src, cpt, 2, Scalar(0, 255, 0), 2, 8, 0);

		Mat result;
		approxPolyDP(contours[t], result, 4, true);
		printf("corners : %d\n", result.rows);
		if (result.rows == 6) {
			putText(src, "poly", cpt, FONT_HERSHEY_SIMPLEX, .7, color, 1, 8);
		}
		if (result.rows == 3) {
			putText(src, "triangle", cpt, FONT_HERSHEY_SIMPLEX, .7, color, 1, 8);
		}
		if (result.rows == 4) {
			putText(src, "rectangle", cpt, FONT_HERSHEY_SIMPLEX, .7, color, 1, 8);
		}
		if (result.rows > 10) {
			putText(src, "circle", cpt, FONT_HERSHEY_SIMPLEX, .7, Scalar(0, 255, 0), 1, 8);
		}
	}
	imshow("contours", src);

	waitKey(0);
	destroyAllWindows();

	return 0;
}