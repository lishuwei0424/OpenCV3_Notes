/*
二值图像分析 – 轮廓发现

图像连通组件分析，可以得到二值图像的每个连通组件，但是我们还无法得知各个组件之间的层次关系与几何拓扑关系，如果我们需要进一步分析图像轮廓拓扑信息就可以通过OpenCV的轮廓发现API获取二值图像的轮廓拓扑信息，轮廓发现API如下：
void cv::findContours(
	InputOutputArray image,
	OutputArrayOfArrays contours,
	OutputArray hierarchy,
	int mode,
	int method,
	Point offset = Point()
)
各个参数详解如下：
Image表示输入图像，必须是二值图像，二值图像可以threshold输出、Canny输出、inRange输出、自适应阈值输出等。
Contours获取的轮廓，每个轮廓是一系列的点集合
Hierarchy轮廓的层次信息，每个轮廓有四个相关信息，分别是同层下一个、前一个、第一个子节点、父节点
mode 表示轮廓寻找时候的拓扑结构返回
-RETR_EXTERNAL表示只返回最外层轮廓
-RETR_TREE表示返回轮廓树结构

Method表示轮廓点集合取得是基于什么算法，常见的是基于CHAIN_APPROX_SIMPLE链式编码方法

对于得到轮廓，OpenCV通过下面的API绘制每个轮廓
void cv::drawContours(
	InputOutputArray image,
	InputArrayOfArrays contours,
	int contourIdx,
	const Scalar & 	color,
	int thickness = 1,
	int lineType = LINE_8,
	InputArray 	hierarchy = noArray(),
	int maxLevel = INT_MAX,
	Point offset = Point()
)
当thickness为正数的时候表示绘制该轮廓
当thickness为-1表示填充该轮廓
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("../images/coins.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// 去噪声与二值化
	Mat dst, gray, binary;
	GaussianBlur(src, dst, Size(3, 3), 0, 0);
	cvtColor(dst, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary", binary);
	imwrite("../binary.png", binary);

	// 轮廓发现与绘制
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
	for (size_t t = 0; t < contours.size(); t++) {
		drawContours(src, contours, t, Scalar(0, 0, 255), 2, 8);
	}
	imshow("contours", src);

	waitKey(0);
	destroyAllWindows();

	return 0;
}