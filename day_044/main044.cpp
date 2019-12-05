/*
OpenCV中图像二化自适应阈值算法

OpenCV中的自适应阈值算法主要是基于均值实现，根据计算均值的方法不同分为盒子模糊均值与高斯模糊均值，然后使用原图减去均值图像，得到的差值图像进行自适应分割，相关的API如下：
void cv::adaptiveThreshold(
InputArray src,
OutputArray dst,
double maxValue,
int adaptiveMethod,
int thresholdType,
int blockSize,
double C
)
其中blockSize取值必须是奇数，C取值在10左右

自适应方法类型：
ADAPTIVE_THRESH_GAUSSIAN_C = 1
ADAPTIVE_THRESH_MEAN_C = 0

当阈值操作类型thresholdType为：THRESH_BINARY
二值图像 = 原图 – 均值图像 > -C ? 255 : 0

当阈值操作类型thresholdType为：THRESH_BINARY_INV
二值图像 = 原图 – 均值图像 > -C ? 0 : 255
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("../images/text1.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// 自动阈值寻找与二值化
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	adaptiveThreshold(gray, binary, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 25, 10);

	imshow("binary", binary);
	imwrite("./binary.png", binary);

	waitKey(0);
	destroyAllWindows();

	return 0;
}