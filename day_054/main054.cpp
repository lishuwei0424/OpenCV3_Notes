/*
二值图像分析 – 对轮廓圆与椭圆拟合
有时候我们需要对找到的轮廓点进行拟合，生成一个拟合的圆形或者椭圆，以便我们对轮廓进行更进一步的处理，满足我们对最终轮廓形状的判断，OpenCV对轮廓进行圆形或者椭圆拟合的API函数如下：
RotatedRect cv::fitEllipse(
InputArray points
)
参数points是轮廓点，
输出RotatedRect包含下面三个信息
-	拟合之后圆或者椭圆的中心位置、
-	长轴与短轴的直径
-	角度
然后我们就可以根据得到拟合信息绘制椭圆、当长轴与短轴相等的时候就是圆。
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("../images/stuff.jpg");
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
	imwrite("D:/binary.png", binary);

	Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	dilate(binary, binary, k);

	// 轮廓发现与绘制
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
	for (size_t t = 0; t < contours.size(); t++) {
		// 最小外接轮廓
		RotatedRect rrt = fitEllipse(contours[t]);
		float w = rrt.size.width;
		float h = rrt.size.height;
		Point centers = rrt.center;
		ellipse(src, rrt, Scalar(0, 0, 255), 2, 8);
	}
	imshow("contours", src);

	waitKey(0);
	destroyAllWindows();
	return 0;
}