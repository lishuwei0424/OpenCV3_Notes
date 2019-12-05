/*
二值图像分析 – 矩形面积与弧长
对图像二值图像的每个轮廓，我们可以计算轮廓的弧长与面积，根据轮廓的面积与弧长可以实现对不同大小对象的过滤，寻找到我们感兴趣的roi区域，这个也是图像二值分析的任务之一。OpenCV对轮廓点集计算面积的API函数如下
double cv::contourArea(
InputArray 	contour,
bool oriented = false
)

计算轮廓的面积，其原理是基于格林公式。
参数contour表示输入的轮廓点集
参数oriented默认是false返回的面积是正数，如果方向参数为true表示会根据是顺时针或者逆时针方向返回正值或者负值面积。

double cv::arcLength(
InputArray curve,
bool closed
)
计算轮廓曲线的弧长。
参数curve表示输入的轮廓点集
参数closed默认表示是否闭合区域
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("../images/zhifang_ball.png");
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
		// rectangle(src, rect, Scalar(0, 0, 255), 1, 8, 0);

		// 面积过滤
		double area = contourArea(contours[t]);
		double curvelen = arcLength(contours[t], true);
		if (area < 100 || curvelen < 100) {
			continue;
		}

		// 最小外接轮廓
		RotatedRect rrt = minAreaRect(contours[t]);
		Point2f pts[4];
		rrt.points(pts);

		// 绘制旋转矩形与中心位置
		for (int i = 0; i < 4; i++) {
			line(src, pts[i % 4], pts[(i + 1) % 4], Scalar(0, 255, 0), 2, 8, 0);
		}
		Point2f cpt = rrt.center;
		circle(src, cpt, 2, Scalar(255, 0, 0), 2, 8, 0);
	}
	imshow("contours", src);

	waitKey(0);
	destroyAllWindows();

	return 0;
}