/*
二值图像连通组件状态统计

OpenCV中的连通组件标记算法有两个相关的API，
一个是不带统计信息的API
int cv::connectedComponents(
	InputArray 	image, // 输入二值图像，黑色背景
	OutputArray 	labels, // 输出的标记图像，背景index=0
	int 	connectivity = 8, // 连通域，默认是8连通
	int 	ltype = CV_32S // 输出的labels类型，默认是CV_32S
)
另外一个是会输出连通组件统计信息的相关API，
int cv::connectedComponentsWithStats(
	InputArray image,
	OutputArray labels,
	OutputArray stats,
	OutputArray centroids,
	int connectivity,
	int ltype,
	int ccltype
)
相关的统计信息包括在输出stats的对象中，每个连通组件有一个这样的输出结构体。
CC_STAT_LEFT
Python : cv.CC_STAT_LEFT
	连通组件外接矩形左上角坐标的X位置信息

	CC_STAT_TOP
	Python : cv.CC_STAT_TOP
	连通组件外接左上角坐标的Y位置信息

	CC_STAT_WIDTH
	Python : cv.CC_STAT_WIDTH
	连通组件外接矩形宽度

	CC_STAT_HEIGHT
	Python : cv.CC_STAT_HEIGHT
	连通组件外接矩形高度

	CC_STAT_AREA
	Python : cv.CC_STAT_AREA
	连通组件的面积大小，基于像素多少统计。

	Centroids输出的是每个连通组件的中心位置坐标(x, y)
*/


#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

RNG rng(12345);
void componentwithstats_demo(Mat &image);
int main(int argc, char** argv) {
	Mat src = imread("../images/rice.png");
	if (src.empty()) {
		printf("could not load image...\n");
	}
	imshow("input", src);
	componentwithstats_demo(src);

	waitKey(0);
	return 0;
}

void componentwithstats_demo(Mat &image) {
	// extract labels
	Mat gray, binary;
	GaussianBlur(image, image, Size(3, 3), 0);
	cvtColor(image, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	Mat labels = Mat::zeros(image.size(), CV_32S);
	Mat stats, centroids;
	int num_labels = connectedComponentsWithStats(binary, labels, stats, centroids, 8, 4);
	printf("total labels : %d\n", (num_labels - 1));
	vector<Vec3b> colors(num_labels);

	// background color
	colors[0] = Vec3b(0, 0, 0);

	// object color
	for (int i = 1; i < num_labels; i++) {
		colors[i] = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
	}

	// extract stats info
	Mat dst = image.clone();
	int w = image.cols;
	int h = image.rows;
	for (int i = 1; i < num_labels; i++) {
		// 中心位置
		int cx = centroids.at<double>(i, 0);
		int cy = centroids.at<double>(i, 1);

		int x = stats.at<int>(i, CC_STAT_LEFT);
		int y = stats.at<int>(i, CC_STAT_TOP);
		int w = stats.at<int>(i, CC_STAT_WIDTH);
		int h = stats.at<int>(i, CC_STAT_HEIGHT);
		int area = stats.at<int>(i, CC_STAT_AREA);

		// 中心位置绘制
		circle(dst, Point(cx, cy), 2, Scalar(0, 255, 0), 2, 8, 0);
		// 外接矩形
		Rect rect(x, y, w, h);
		rectangle(dst, rect, colors[i], 1, 8, 0);
		putText(dst, format("num:%d", i), Point(x, y), FONT_HERSHEY_SIMPLEX, .5, Scalar(0, 0, 255), 1);
		printf(" num: %d,  rice area %d\n", i, area);
	}
	imshow("ccla-demo", dst);
	imwrite("D:/ccla_dst.png", dst);
}
