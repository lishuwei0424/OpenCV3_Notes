/*
二值图像分析 – 凸包检测
对二值图像进行轮廓分析之后，对获取到的每个轮廓数据，可以构建每个轮廓的凸包，构建完成之后会返回该凸包包含的点集。根据返回的凸包点集可以绘制该轮廓对应的凸包。OpenCV对轮廓提取凸包的API函数如下：
void cv::convexHull(
	InputArray points,
	OutputArray hull,
	bool clockwise = false,
	bool returnPoints = true
)
points参数是输入的轮廓点集
hull凸包检测的输出结果，当参数returnPoints为ture的时候返回凸包的顶点坐标是个点集、returnPoints为false的是返回的是一个integer的vector里面是凸包各个顶点在轮廓点集对应的index
clockwise 表示顺时针方向或者逆时针方向
returnPoints表示是否返回点集
OpenCV中的凸包寻找算法是基于Graham’s扫描法。
OpenCV中还提供了另外一个API函数用来判断一个轮廓是否为凸包，该方法如下：
bool cv::isContourConvex(
InputArray contour
)
该方法只有一个输入参数就是轮廓点集。
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("../images/hand.jpg");
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

	// 删除干扰块
	Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(binary, binary, MORPH_OPEN, k);
	imshow("binary", binary);

	// 轮廓发现与绘制
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
	for (size_t t = 0; t < contours.size(); t++) {
		vector<Point> hull;
		convexHull(contours[t], hull);
		bool isHull = isContourConvex(contours[t]);
		printf("test convex of the contours %s", isHull ? "Y" : "N");
		int len = hull.size();
		for (int i = 0; i < hull.size(); i++) {
			circle(src, hull[i], 4, Scalar(255, 0, 0), 2, 8, 0);
			line(src, hull[i%len], hull[(i + 1) % len], Scalar(0, 0, 255), 2, 8, 0);
		}
	}
	imshow("contours", src);

	waitKey(0);
	destroyAllWindows();

	return 0;
}