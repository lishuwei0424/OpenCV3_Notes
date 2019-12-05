/*
图像透视变换应用
对于很多的文本扫描图像，有时候因为放置的原因导致ROI区域倾斜，这个时候我们会想办法把它纠正为正确的角度视角来，方便下一步的布局分析与文字识别，这个时候通过透视
变换就可以取得比较好的裁剪效果，一步就可以实现裁剪与调整。使用透视变换相关几何变换的好处如下：
1.	透视变换不会涉及到几何变换角度旋转
2.	透视变换对畸变图像有一定的展开效果
3.	透视变换可以完成对图像ROI区域提取

PS:周五-2018-11-30的分享！
*/

#include <opencv2/opencv.hpp>
#include <math.h>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat src = imread("../images/55.jpg");
	imshow("input", src);

	// 二值图像
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	imshow("binary", binary);

	// 定义结构元素
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(binary, binary, MORPH_OPEN, se);

	// 寻找最大轮廓
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	int index = -1;
	int max = 0;
	for (size_t t = 0; t < contours.size(); t++) {
		double area = contourArea(contours[t]);
		if (area > max) {
			max = area;
			index = t;
		}
	}
	// drawContours(src, contours, index, Scalar(0, 0, 255), 2, 8);
	imshow("src", src);

	// 寻找最小外接矩形
	RotatedRect rect = minAreaRect(contours[index]);
	int width = static_cast<int>(rect.size.height);
	int height = static_cast<int>(rect.size.width);
	printf("height %d, width :%d\n", height, width);

	Point2f vertices[4];
	rect.points(vertices);
	vector<Point> src_pts;
	vector<Point> dst_pts;
	dst_pts.push_back(Point(width, height));
	dst_pts.push_back(Point(0, height));
	dst_pts.push_back(Point(0, 0));
	dst_pts.push_back(Point(width, 0));
	for (int i = 0; i < 4; i++) {
		printf("x=%.2f, y=%.2f\n", vertices[i].x, vertices[i].y);
		src_pts.push_back(vertices[i]);
	}

	// 透视变换
	Mat M = findHomography(src_pts, dst_pts);
	Mat result = Mat::zeros(Size(width, height), CV_8UC3);
	warpPerspective(src, result, M, result.size());
	imshow("result", result);
	waitKey(0);
	destroyAllWindows();

	return 0;
}