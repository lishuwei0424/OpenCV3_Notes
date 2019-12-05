/*
OpenCV中图像二值寻找算法 – OTSU

图像二值化，除了我们上次分享的手动阈值设置与根据灰度图像均值的方法之外，还有几个根据图像直方图实现自动全局阈值寻找的方法，OpenCV中支持的有OTSU与Triangle两种直方图阈值寻找算法。其中OTSU的是通过计算类间最大方差来确定分割阈值的阈值选择算法，OTSU算法对直方图有两个峰，中间有明显波谷的直方图对应图像二值化效果比较好，而对于只有一个单峰的直方图对应的图像分割效果没有双峰的好。

OpenCV中OTSU算法使用只需要在
threshold函数的type类型声明THRESH_OTSU即可
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
	double t = threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	printf("threshold : %.2f\n", t);


	imshow("binary", binary);
	imwrite("./binary.png", binary);

	waitKey(0);
	destroyAllWindows();

	return 0;
}