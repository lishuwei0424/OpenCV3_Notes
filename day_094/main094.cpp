/*
ORB FAST�����ؼ�����

ORB - (Oriented Fast and Rotated BRIEF)�㷨�ǻ���FAST���������BRIEF����������ƥ��ʵ�֣����BRIEF�㷨�����������ʽ��ȡ��ֵ��ԣ�ORBͨ��FAST������FAST��ʽѰ�Һ�ѡ�����㷽ʽ�Ǽ���Ҷ�ͼ�����ص�A��Χ�����ش����������ڻ���С��A�ĻҶ�ֵ��ѡ������һ�����ص�P������뾶Ϊ3����Χ16�����ر�ʾ
��ͼһ��

�����ص�P�����Ϊ��ѡ�����㡢ͨ��NȡֵΪ9��12����ͼN=9��
Ϊ�˼򻯼��㣬���ǿ���ֻ����1��9��5��13�ĸ��㣬��������������������������ʽ���������ɽ�P��Ϊ��ѡ�㡣Ȼ��ͨ����ֵ�������յ�ɸѡ���ɵõ�ORB������

static Ptr&lt;ORB&gt; cv::ORB::create	(
	int nfeatures = 500,
	float scaleFactor = 1.2f,
	int nlevels = 8,
	int edgeThreshold = 31,
	int firstLevel = 0,
	int WTA_K = 2,
	ORB::ScoreType 	scoreType = ORB::HARRIS_SCORE,
	int patchSize = 31,
	int fastThreshold = 20
)
nfeatures ������������������Ŀ
scaleFactor �������ϲ�������
nlevels ����������
edgeThreshold ��Ե��ֵ
firstLevel= 0
WTA_K����Ǹ�BRIEF�������õ�
scoreType �����е���������������õķ���
*/


#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("../images/blob.png");
	auto orb_detector = ORB::create(1000);
	vector<KeyPoint> kpts;
	orb_detector->detect(src, kpts);
	Mat result = src.clone();
	drawKeypoints(src, kpts, result, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	imshow("ORB-detector", result);
	imwrite("../result.png", result);
	waitKey(0);
	destroyAllWindows();

	return 0;
}
