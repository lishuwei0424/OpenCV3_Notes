/*
图像二值化与去噪

对于一张需要二值化的图像，我们有两种选择
选择一
直接对输入图像转换为灰度图像，然后二值化
选择二
首先对输入图像进行降噪，去除噪声干扰，然后再二值化

在进行去噪声的时候，还记得前面我们分享的几种去噪声方法，可以选择的有
均值模糊去噪声
高斯模糊去噪声
双边/均值迁移模糊去噪声
非局部均值去噪声

下面的三张图，
第一张图是输入图像直接转换为二值图像
第二张图是输入图像先高斯模糊去噪声，然后二值化图像
第三张图是输入图像先均值迁移去噪声，然后二值化的图像
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
	pyrMeanShiftFiltering(src, dst, 10, 100);
	// GaussianBlur(src, dst, Size(3, 3), 0, 0);
	cvtColor(dst, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary", binary);
	imwrite("./binary.png", binary);

	waitKey(0);
	destroyAllWindows();

	return 0;
}