/*
OpenCV-day-107

Brisk������ȡ��������ƥ��
BRISK(Binary robust invariant scalable keypoints)��һ�ֻ��ڳ߶ȿռ䲻��������ORB���������ӵ�������ȡ�㷨��BRISK��Ҫ������Է�Ϊ����������
1.	�����߶ȿռ������ʵ�ֹؼ��㶨λ
2.	���ݹؼ�������������

������106���ƣ�
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat box = imread("../data/box.png");
	Mat box_in_sence = imread("../data/box_in_scene.png");

	// ����BRISK
	auto brisk_detector = BRISK::create();
	vector<KeyPoint> kpts_01, kpts_02;
	Mat descriptors1, descriptors2;
	brisk_detector->detectAndCompute(box, Mat(), kpts_01, descriptors1);
	brisk_detector->detectAndCompute(box_in_sence, Mat(), kpts_02, descriptors2);

	// ����������ƥ�� - ����ƥ��
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
	std::vector< DMatch > matches;
	matcher->match(descriptors1, descriptors2, matches);

	// ����ƥ��
	Mat img_matches;
	drawMatches(box, kpts_01, box_in_sence, kpts_02, matches, img_matches);
	imshow("AKAZE-Matches", img_matches);
	imwrite("D:/result.png", img_matches);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
