/*
二值图像分析 – 霍夫直线检测
图像霍夫变换是一种特别有用的图像变换，通过把图像的坐标从2D平面坐标系变换到极坐标空间，可以发现原来在平面坐标难以提取的几何特征信息（如：直线、圆等），图像的直线与圆检测就是典型的利用霍夫空间特性实现二值图像几何分析的例子。假设有如下的直线参数方程：
r = x*cos(theta) + y * sin(theta)
其中角度theta指r与X轴之间的夹角，r为到直线几何垂直距离。


OpenCV关于霍夫直线检测有两个API，我们首先分享第一个函数，它是提取到直线在霍夫空间得几何特征，然后输出直线得两个极坐标参数。根据这两个参数我们可以组合得到空间坐标直线。该API如下：
void cv::HoughLines(
	InputArray  image,
	OutputArray lines,
	double rho,
	double theta,
	int threshold,
	double srn = 0,
	double stn = 0,
	double min_theta = 0,
	double max_theta = CV_PI
)
Image 输入图像
Lines 输出直线
Rho 极坐标r得步长
Theta角度步长
Threshold累加器阈值
Srn、stn多尺度霍夫变换时候需要得参数，经典霍夫变换不需要
min_theta 最小角度
max_theta最大角度
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("../images/hand.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// 去噪声与二值化
	Mat dst, gray, binary;
	Canny(src, binary, 80, 160, 3, false);
	imshow("binary", binary);
	imwrite("./binary.png", binary);

	// 标准霍夫直线检测
	vector<Vec2f> lines;
	HoughLines(binary, lines, 1, CV_PI / 180, 150, 0, 0);

	// 绘制直线
	Point pt1, pt2;
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0];
		float theta = lines[i][1];
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(src, pt1, pt2, Scalar(0, 0, 255), 3);
	}

	imshow("contours", src);

	waitKey(0);
	return 0;
}


