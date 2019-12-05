/*
## 二值图像分析 – 轮廓外接矩形

对图像二值图像的每个轮廓，OpenCV都提供了API可以求取轮廓的外接矩形，其中求取轮廓外接矩形有两种方式，一种是可以基于像素的最大外接轮廓矩形，API解释如下：
Rect cv::boundingRect(
InputArray points
)

输入参数points可以一系列点的集合，对轮廓来说就是该轮廓的点集
返回结果是一个矩形，x, y, w, h

RotatedRect cv::minAreaRect(
InputArray points
)

输入参数points可以一系列点的集合，对轮廓来说就是该轮廓的点集
返回结果是一个旋转矩形，包含下面的信息：
-	矩形中心位置
-	矩形的宽高
-	旋转角度

首先看一下代码演示与应用Python与C++
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("../images/stuff.jpg");
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
	imwrite("./binary.png", binary);

	Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	dilate(binary, binary, k);

	// 轮廓发现与绘制
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
	for (size_t t = 0; t < contours.size(); t++) {
		// 最大外接轮廓
		cv::Rect rect = boundingRect(contours[t]);
		rectangle(src, rect, Scalar(0, 0, 255), 1, 8, 0);

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