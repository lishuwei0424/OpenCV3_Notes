/*
快速的图像边缘滤波算法

高斯双边模糊与mean shift均值模糊两种边缘保留滤波算法，都因为计算量比较大，无法实时实现图像边缘保留滤波，限制了它们的使用场景，OpenCV中还实现了一种快速的边缘保留滤波算法。高斯双边与mean shift均值在计算时候使用五维向量是其计算量大速度慢的根本原因，该算法通过等价变换到低纬维度空间，实现了数据降维与快速计算。

OpenCV API函数为：
void cv::edgePreservingFilter(
InputArray src,
OutputArray dst,
int flags = 1,
float sigma_s = 60,
float sigma_r = 0.4f
)

Python:
dst	= cv.edgePreservingFilter(	src[, dst[, flags[, sigma_s[, sigma_r]]]])

其中sigma_s的取值范围为0～200， sigma_r的取值范围为0～1
当sigma_s取值不变时候，sigma_r越大图像滤波效果越明显
当sigma_r取值不变时候，窗口sigma_s越大图像模糊效果越明显
当sgma_r取值很小的时候，窗口sigma_s取值无论如何变化，图像双边滤波效果都不好！

*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int artc, char** argv) {
	Mat src = imread("../images/example.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	Mat dst;
	double tt = getTickCount();
	edgePreservingFilter(src, dst, 1, 60, 0.44);
	double end = (getTickCount() - tt) / getTickFrequency();
	printf("time consume : %f\n ", end);
	imshow("result", dst);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
