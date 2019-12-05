/*
图像去水印/修复

在OpenCV中有时候我们需要一个批量的去水印的方法，这个在很多时候需要用到，对得到图像进行批量的去水印，其本质上是一种图像修复，OpenCV也提供一个图像修复的API，可以部分解决这里问题，
void cv::inpaint(
InputArray  src,
InputArray  ipaintMask,
OutputArray  dst
double  npaintRadius,
int  fags
)

基于Navier-Stokes的修复方法
基于图像梯度的快速匹配方法又称(Telea法)
*/

#include <opencv2/opencv.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat hsv, mask, result;
	Mat src = imread("../images/master2.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	cvtColor(src, hsv, COLOR_BGR2HSV);

	// mask
	inRange(hsv, Scalar(100, 43, 46), Scalar(124, 255, 255), mask);
	Mat se = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
	dilate(mask, mask, se);
	imshow("mask", mask);

	// ÐÞ¸´
	inpaint(src, mask, result, 3, INPAINT_TELEA);
	imshow("result", result);
	waitKey(0);
	destroyAllWindows();

	return 0;
}