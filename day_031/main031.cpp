/*
图像梯度 – Sobel算子

卷积的作用除了实现图像模糊或者去噪，还可以寻找一张图像上所有梯度信息，这些梯度信息是图像的最原始特征数据，进一步处理之后就可以生成一些比较高级的特征用来表示一张图像实现基于图像特征的匹配，图像分类等应用。Sobel算子是一种很经典的图像梯度提取算子，其本质是基于图像空间域卷积，背后的思想是图像一阶导数算子的理论支持。OpenCV实现了基于Sobel算子提取图像梯度的API，表示与解释如下：
void cv::Sobel(
InputArray src, // 输入图像
OutputArray dst, // 输出结果
int ddepth, // 图像深度CV_32F
int dx,// 1，X方向 一阶导数
int dy, // 1，Y方向 一阶导数
int ksize = 3, // 窗口大小
double scale = 1, // 放缩比率，1 表示不变
double delta = 0, // 对输出结果图像加上常量值
int borderType = BORDER_DEFAULT
)
Python:
dst = cv.Sobel(src, ddepth, dx, dy[, dst[, ksize[, scale[, delta[, borderType]]]]])
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int artc, char** argv) {
	Mat src = imread("../images/ttt.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	Mat grad_x, grad_y;
	Mat dst;
	Sobel(src, grad_x, CV_32F, 1, 0, 3, 1, 0, BORDER_DEFAULT);
	Sobel(src, grad_y, CV_32F, 0, 1, 3, 1, 0, BORDER_DEFAULT);

	convertScaleAbs(grad_x, grad_x);
	convertScaleAbs(grad_y, grad_y);

	add(grad_x, grad_y, dst, Mat(), CV_16S);
	convertScaleAbs(dst, dst);

	imshow("gradient", dst);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
