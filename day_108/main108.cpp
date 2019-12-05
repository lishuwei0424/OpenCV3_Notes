/*
特征提取之关键点检测 - GFTTDetector
该方法是基于shi-tomas角点检测变化而来的一种特征提取方法，OpenCV创建该检测器的API与goodfeaturetotrack的API参数极其类似：
Ptr<GFTTDetector> cv::GFTTDetector::create(
	int maxCorners = 1000,
	double qualityLevel = 0.01,
	double minDistance = 1,
	int blockSize = 3,
	bool useHarrisDetector = false,
	double k = 0.04
)
唯一不同的，该方法返回一个指针。

PS:
需要注意的是该方法无法提取描述子，只支持提取关键点！
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("../images/test1.png");
	auto keypoint_detector = GFTTDetector::create(1000, 0.01, 1.0, 3, false, 0.04);
	vector<KeyPoint> kpts;
	keypoint_detector->detect(src, kpts);
	Mat result = src.clone();
	drawKeypoints(src, kpts, result, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	imshow("GFTT-Keypoint-Detect", result);
	imwrite("D:/result.png", result);
	waitKey(0);
	destroyAllWindows();

	return 0;
}
