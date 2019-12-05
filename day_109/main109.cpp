/*
BLOB特征分析 – simpleblobdetector使用

BLOB是图像中灰度块的一种专业称呼，更加变通一点的可以说它跟我们前面二值图像分析的联通组件类似，通过特征提取中的SimpleBlobDetector可以实现常见的各种灰度BLOB对象组件检测与分离。使用该检测器的时候，可以根据需要输入不同参数，得到的结果跟输入的参数息息相关。常见的BLOB分析支持如下：
-	根据BLOB面积过滤
-	根据灰度/颜色值过滤
-	根据圆度过滤
-	根据长轴与短轴过滤
-	根据凹凸进行过滤

参数列表！
SimpleBlobDetector::Params::Params()
bool 	filterByArea
bool 	filterByCircularity
bool 	filterByColor
bool 	filterByConvexity
bool 	filterByInertia
float 	maxArea
float 	maxCircularity
float 	maxConvexity
float 	maxInertiaRatio
float 	maxThreshold
float 	minArea
float 	minCircularity
float 	minConvexity
float 	minDistBetweenBlobs
float 	minInertiaRatio
*/

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	// 加载图像
	Mat src = imread("../images/test1.png");
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);

	// 初始化参数设置
	SimpleBlobDetector::Params params;
	params.minThreshold = 10;
	params.maxThreshold = 200;
	params.filterByArea = true;
	params.minArea = 100;
	params.filterByCircularity = true;
	params.minCircularity = 0.1;
	params.filterByConvexity = true;
	params.minConvexity = 0.87;
	params.filterByInertia = true;
	params.minInertiaRatio = 0.01;

	// 创建BLOB Detetor
	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

	// BLOB分析与显示
	Mat result;
	vector<KeyPoint> keypoints;
	detector->detect(gray, keypoints);
	drawKeypoints(src, keypoints, result, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imshow("Blob Detection Demo", result);
	waitKey(0);
	destroyAllWindows();

}