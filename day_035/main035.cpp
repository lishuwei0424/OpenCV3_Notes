/*
USM 锐化增强算法

图像卷积处理实现锐化有一种常用的算法叫做Unsharpen Mask方法，这种锐化的方法就是对原图像先做一个高斯模糊，然后用原来的图像减去一个系数乘以高斯模糊之后的图像，然后再把值Scale到0～255的RGB像素值范围之内。基于USM锐化的方法可以去除一些细小的干扰细节和噪声，比一般直接使用卷积锐化算子得到的图像锐化结果更加真实可信。

USM锐化公式表示如下：
（源图像– w*高斯模糊）/（1-w）；其中w表示权重（0.1～0.9），默认为0.6

OpenCV中的代码实现步骤
1.	高斯模糊
2.	权重叠加
3.	输出结果
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int artc, char** argv) {
	Mat src = imread("../images/master.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	Mat blur_img, usm;
	GaussianBlur(src, blur_img, Size(0, 0), 25);
	addWeighted(src, 1.5, blur_img, -0.5, 0, usm);
	imshow("mask image", usm);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
