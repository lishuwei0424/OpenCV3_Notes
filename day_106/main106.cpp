/*
AKAZE特征与描述子

AKAZE特征提取算法是局部特征描述子算法，可以看成是SIFT算法的改进、采用非线性扩散滤波迭代来提取与构建尺度空间、采用与SIFT类似的方法寻找特征点、
在描述子生成阶段采用ORB类似的方法生成描述子，但是描述子比ORB多了旋转不变性特征。ORB采用LDB方法，AKAZE采用 M-LDB
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat box = imread("../data/box.png");
	Mat box_in_sence = imread("../data/box_in_scene.png");

	// 创建AKAZE
	auto akaze_detector = AKAZE::create();
	vector<KeyPoint> kpts_01, kpts_02;
	Mat descriptors1, descriptors2;
	akaze_detector->detectAndCompute(box, Mat(), kpts_01, descriptors1);
	akaze_detector->detectAndCompute(box_in_sence, Mat(), kpts_02, descriptors2);

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
