/*
OpenCV中的基本阈值操作

假设我们已经寻找到合适的阈值T，那么对图像二值化分割可以看成是一种基本的阈值化操作，其实OpenCV除了支持正常的二值化阈值分割操作之外，还支持一些其它的阈值操作，OpenCV中支持的阈值操作的API如下：
double cv::threshold(
InputArray src,
OutputArray dst,
double thresh,
double maxval,
int type
)
其中type表示阈值分割的方法，支持如下五种：
THRESH_BINARY = 0  二值分割
THRESH_BINARY_INV = 1 反向二值分割
THRESH_TRUNC = 2 截断
THRESH_TOZERO = 3 取零
THRESH_TOZERO_INV = 4 反向取零
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

	// תۻΪܒ׈ͼб
	int T = 127;
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	for (int i = 0; i < 5; i++) {
		threshold(gray, binary, T, 255, i);
		imshow(format("binary_%d", i), binary);
		imwrite(format("./binary_%d.png", i), binary);
	}
	waitKey(0);
	destroyAllWindows();

	return 0;
}