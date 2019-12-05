/*
OpenCV中图像二值寻找算法 – TRIANGLE

图像二值化，除了我们上次分享的手动阈值设置与根据灰度图像均值的方法之外，还有几个根据图像直方图实现自动全局阈值寻找的方法，OpenCV中支持的有OTSU与Triangle两种直方图阈值寻找算法。上次分享提到OTSU基于类内最小方差实现阈值寻找, 它对有两个波峰之间有一个波谷的直方图特别好,但是有时候图像的直方图只有一个波峰,这个时候使用TRIANGLE方法寻找阈值是比较好的一个选择。

OpenCV中TRIANGLE算法使用只需要在
threshold函数的type类型声明THRESH_TRIANGLE即可
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("../images/master.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// 自动阈值寻找与二值化
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	double t = threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_TRIANGLE);
	printf("threshold : %.2f\n", t);


	imshow("binary", binary);
	imwrite("./binary.png", binary);

	waitKey(0);
	destroyAllWindows();

	return 0;
}