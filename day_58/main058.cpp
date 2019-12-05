/*
二值图像分析 – 寻找最大内接圆
对于轮廓来说，有时候我们会需要选择最大内接圆，OpenCV中没有现成的API可以使用，但是我们可以通过点多边形测试巧妙的获取轮廓最大内接圆的半径，
从点多边形测试的返回结果我们知道，它返回的是像素距离，而且是当前点距离轮廓最近的距离，当这个点在轮廓内部，其返回的距离是最大值的时候，
其实这个距离就是轮廓的最大内接圆的半径，这样我们就巧妙的获得了圆心的位置与半径，剩下的工作就很容易了完成，绘制一个圆而已，一行代码就可以
搞定，而且前面我们的知识点分享已经交代了如何在OpenCV中去绘制常见几何形状啦。需要特别说明一下的这个估计在OpenCV3.4.x之后的版本中可能会有
出现在opencv官方的tutorial中，研习社的嘉宾禾路是这个PR的提交者，我应禾路老师要求帮他审阅与修改了Java版本与Python版本的程序代码。首先看运
行效果见第一张图
*/

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main(void)
{
	const int r = 100;
	Mat src = Mat::zeros(Size(4 * r, 4 * r), CV_8U);
	vector<Point2f> vert(6);
	vert[0] = Point(3 * r / 2, static_cast<int>(1.34*r));
	vert[1] = Point(1 * r, 2 * r);
	vert[2] = Point(3 * r / 2, static_cast<int>(2.866*r));
	vert[3] = Point(5 * r / 2, static_cast<int>(2.866*r));
	vert[4] = Point(3 * r, 2 * r);
	vert[5] = Point(5 * r / 2, static_cast<int>(1.34*r));
	for (int i = 0; i < 6; i++)
	{
		line(src, vert[i], vert[(i + 1) % 6], Scalar(255), 3);
	}
	// 点多边形测试
	vector<vector<Point> > contours;
	findContours(src, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
	Mat raw_dist(src.size(), CV_32F);
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			raw_dist.at<float>(i, j) = (float)pointPolygonTest(contours[0], Point2f((float)j, (float)i), true);
		}
	}
	// 获取最大内接圆半径
	double minVal, maxVal;
	Point maxDistPt; // inscribed circle center
	minMaxLoc(raw_dist, &minVal, &maxVal, NULL, &maxDistPt);
	minVal = abs(minVal);
	maxVal = abs(maxVal);


	Mat drawing = Mat::zeros(src.size(), CV_8UC3);
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			if (raw_dist.at<float>(i, j) < 0)
			{
				drawing.at<Vec3b>(i, j)[0] = (uchar)(255 - abs(raw_dist.at<float>(i, j)) * 255 / minVal);
			}
			else if (raw_dist.at<float>(i, j) > 0)
			{
				drawing.at<Vec3b>(i, j)[2] = (uchar)(255 - raw_dist.at<float>(i, j) * 255 / maxVal);
			}
			else
			{
				drawing.at<Vec3b>(i, j)[0] = 255;
				drawing.at<Vec3b>(i, j)[1] = 255;
				drawing.at<Vec3b>(i, j)[2] = 255;
			}
		}
	}

	// draw max inner circle
	circle(drawing, maxDistPt, (int)maxVal, Scalar(255, 255, 255));
	imshow("Source", src);
	imshow("Distance and inscribed circle", drawing);
	waitKey();

	destroyAllWindows();

	return 0;
}