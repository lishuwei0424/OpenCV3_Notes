/*
������ȡ֮�ؼ����� - GFTTDetector
�÷����ǻ���shi-tomas�ǵ���仯������һ��������ȡ������OpenCV�����ü������API��goodfeaturetotrack��API�����������ƣ�
Ptr<GFTTDetector> cv::GFTTDetector::create(
	int maxCorners = 1000,
	double qualityLevel = 0.01,
	double minDistance = 1,
	int blockSize = 3,
	bool useHarrisDetector = false,
	double k = 0.04
)
Ψһ��ͬ�ģ��÷�������һ��ָ�롣

PS:
��Ҫע����Ǹ÷����޷���ȡ�����ӣ�ֻ֧����ȡ�ؼ��㣡
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
