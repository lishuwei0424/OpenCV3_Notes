/*
BRIEF���������� ƥ��
�õ�����������֮�󣬸���BRIEF�㷨�Ϳ��Խ��������ӡ�ѡ���ѡ��������ΧSxS��С�����ؿ顢���ѡ��n�����ص㡣
����P(x)��ͼ��ģ������֮�������ֵ��ԭ�����ڸ�˹ģ��������������Ӱ�졢�ṩ�������ȶ��ԣ���ʵ�ʴ���ʵ����
ͨ���þ�ֵ�˲������˹�˲��Ա����û���ͼ��ʽ���ټ����ø��õ����ܱ��֡������˲�ʱ��ʹ��3x3~9x9֮��ľ���ˡ�
�˲�֮�󣬸������������ӵ������������õ������ӡ�

���������ᵽn��ȡֵͨ��Ϊ128��256����512���õ������Ʒ�ʽ���ַ���������֮��ƥ��Ϳ���ͨ��XOR��ʽ���Σ���
�㺺�����롣ORB������ȡ����BRIEF������ȡ��Ƚϣ�BRIEF��ʽ��������㷽ʽ�����������ӡ���ORBͨ��FAST�õ�������Ȼ��õ������ӡ�

*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat box = imread("../data/box.png");
	Mat box_in_sence = imread("../data/box_in_scene.png");

	// ����ORB
	auto orb_detector = ORB::create();
	vector<KeyPoint> kpts_01, kpts_02;
	Mat descriptors1, descriptors2;
	orb_detector->detectAndCompute(box, Mat(), kpts_01, descriptors1);
	orb_detector->detectAndCompute(box_in_sence, Mat(), kpts_02, descriptors2);

	// ����������ƥ�� - ����ƥ��
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
	std::vector< DMatch > matches;
	matcher->match(descriptors1, descriptors2, matches);

	// ����ƥ��
	Mat img_matches;
	drawMatches(box, kpts_01, box_in_sence, kpts_02, matches, img_matches);
	imshow("ORB-Matches", img_matches);
	imwrite("D:/result.png", img_matches);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
