/*
二值图像分析 – 点多边形测试
对于轮廓图像，有时候还需要判断一个点是在轮廓内部还是外部，OpenCV中实现这个功能的API叫做点多边形测试，它可以准确的得到一个点距离多边形的距离，如果点是轮廓点或者属于轮廓多边形上的点，距离是零，如果是多边形内部的点是是正数，如果是负数返回表示点是外部。表示如下：
double cv::pointPolygonTest(
	InputArray contour,
	Point2f pt,
	bool measureDist
)
Contour轮廓所有点的集合
Pt 图像中的任意一点
MeasureDist如果是True，则返回每个点到轮廓的距离，如果是False则返回+1，0，-1三个值，其中+1表示点在轮廓内部，0表示点在轮廓上，-1表示点在轮廓外
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("../images/contours.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// 二值化
	Mat dst, gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

	// 轮廓发现与绘制
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
	int h = src.rows;
	int w = src.cols;
	Mat image = Mat::zeros(src.size(), CV_32FC3);
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			double dist = pointPolygonTest(contours[0], Point(col, row), true);
			if (dist == 0) {
				image.at<Vec3f>(row, col) = Vec3f(255, 255, 255);
			}
			if (dist > 0) {
				image.at<Vec3f>(row, col) = Vec3f(255 - dist, 0, 0);
			}
			if (dist < 0) {
				image.at<Vec3f>(row, col) = Vec3f(0, 0, 255 + dist);
			}

		}
	}
	convertScaleAbs(image, image);
	image.convertTo(image, CV_8UC3);
	imshow("points", image);

	waitKey(0);
	destroyAllWindows();

	return 0;
}