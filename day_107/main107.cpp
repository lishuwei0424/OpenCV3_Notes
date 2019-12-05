/*
OpenCV-day-107

Brisk特征提取与描述子匹配
BRISK(Binary robust invariant scalable keypoints)是一种基于尺度空间不变性类似ORB特征描述子的特征提取算法。BRISK主要步骤可以分为如下两步：
1.	构建尺度空间金字塔实现关键点定位
2.	根据关键点生成描述子

代码与106类似！
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat box = imread("../data/box.png");
	Mat box_in_sence = imread("../data/box_in_scene.png");

	// 创建BRISK
	auto brisk_detector = BRISK::create();
	vector<KeyPoint> kpts_01, kpts_02;
	Mat descriptors1, descriptors2;
	brisk_detector->detectAndCompute(box, Mat(), kpts_01, descriptors1);
	brisk_detector->detectAndCompute(box_in_sence, Mat(), kpts_02, descriptors2);

	// 定义描述子匹配 - 暴力匹配
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
	std::vector< DMatch > matches;
	matcher->match(descriptors1, descriptors2, matches);

	// 绘制匹配
	Mat img_matches;
	drawMatches(box, kpts_01, box_in_sence, kpts_02, matches, img_matches);
	imshow("AKAZE-Matches", img_matches);
	imwrite("D:/result.png", img_matches);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
