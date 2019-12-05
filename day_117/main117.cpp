/*
ͼ���ֵƯ�Ʒָ�

ͼ���ֵƯ�Ʒָ���һ���޼ල��ͼ��ָ����ǰ�������ڸ�����ص����ݽ��ܹ���ֵǨ���㷨��֪����ֵǨ�ƿ����ҵ�ͼ��������ֱ��ͼ�ռ�ķ�ֵ�ֲ�
���������ǻ���ʹ�þ�ֵǨ�ƣ�����ȥ���Ϸָ��ҵ��ռ���ɫ�ֲ��ķ�ֵ��Ȼ����ݷ�ֵ�������ƶȺϲ���������ȷָ����⣬�õ����յķָ�ͼ�񣬶���ͼ
���ά��������ɫֵ(RGB)��ռ�λ��(x,y)��������Ҫ�������ڰ뾶��һ���ǿռ�뾶������һ������ɫ�뾶��������ֵƯ�ƴ��ڵ����е����ص�������ͬ
������ֵ��OpenCV�о�ֵƯ�Ʒָ��API���£�
void cv::pyrMeanShiftFiltering(
	InputArray src,
	OutputArray dst,
	double sp,
	double sr,
	int maxLevel = 1,
	TermCriteria termcrit = TermCriteria(TermCriteria::MAX_ITER+TermCriteria::EPS, 5, 1)
)
src ����ͼ��
dst������
sp ��ʾ�ռ䴰�ڴ�С
sr ��ʾ��ʾ��ɫ�ռ�
maxLevel��ʾ�������������ܲ���Ϊmaxlevel+1
termcrit��ʾֹͣ����
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("./images/test.png");
	imshow("input", src);
	Mat dst;
	TermCriteria tc = TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 10, 0.1);
	pyrMeanShiftFiltering(src, dst, 20, 40, 2, tc);
	imshow("mean shift segementation demo", dst);
	waitKey(0);
	destroyAllWindows();

	return 0;
}