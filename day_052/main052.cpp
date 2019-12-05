/*
二值图像分析 – 使用几何矩计算轮廓中心与横纵比过滤
对图像二值图像的每个轮廓，可以计算轮廓几何矩，根据几何矩可以计算图像的中心位置，估计得到中心位置可以计算中心矩、然后再根据中心矩可以计算胡矩。OpenCV中可以通过如下的API一次计算出上述三种矩，API如下：
Moments cv::moments(
	InputArray 	array,
	bool binaryImage = false
)
array是输入的图像轮廓点集合
输出的图像几何矩。关于几何矩的计算与解释看图一：
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
		RotatedRect rrt = minAreaRect(contours[t]);
		float w = rrt.size.width;
		float h = rrt.size.height;
		Point2f pts[4];
		rrt.points(pts);

		// 计算横纵比
		float ratio = min(w, h) / max(w, h);
		Point2f cpt = rrt.center;
		circle(src, cpt, 2, Scalar(255, 0, 0), 2, 8, 0);
		if (ratio > 0.9) {
			circle(src, cpt, 2, Scalar(255, 0, 0), 2, 8, 0);
			// 绘制旋转矩形与中心位置
			for (int i = 0; i < 4; i++) {
				line(src, pts[i % 4], pts[(i + 1) % 4], Scalar(0, 0, 255), 2, 8, 0);
			}
		}
		if (ratio < 0.5) {
			circle(src, cpt, 2, Scalar(255, 0, 0), 2, 8, 0);
			// 绘制旋转矩形与中心位置
			for (int i = 0; i < 4; i++) {
				line(src, pts[i % 4], pts[(i + 1) % 4], Scalar(0, 255, 0), 2, 8, 0);
			}
		}
	}
	imshow("contours", src);

	waitKey(0);
	destroyAllWindows();

	return 0;
}