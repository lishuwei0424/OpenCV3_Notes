/*
��Ե�����˲��㷨 �C ��ֵǨ��ģ��(mean-shift blur)
��ֵǨ��ģ����ͼ���Ե�����˲��㷨��һ�֣����������ڶ�ͼ����з�ˮ��ָ�֮ǰȥ���������Դ����������ˮ��ָ��Ч������ֵǨ��ģ������Ҫ˼�����£�
������ͼ����п�����ʱ��ͬ������������ֵ�ռ䷶Χ�ֲ���ֻ�з��Ϸֲ������ص�Ų�����㣬����õ����ؾ�ֵ��ռ�λ�þ�ֵ��ʹ���µľ�ֵλ����Ϊ��������λ�ü������ڸ�������ֵ�ռ�ֲ������ֵ���ֵλ�ã���˲���Ǩ������λ��ֱ�����ٱ仯λ�ã�dx=dy=0����������ʵ����������ǻ���Ϊ����һ��ֹͣ��������Ǩ�Ƽ��Σ������Ϳ��԰�����RGB��ֵ��ֵ������λ�á�

OpenCV�о�ֵǨ���˲���API������
C++:
pyrMeanShiftFiltering(
InputArray 	src,
OutputArray 	dst,
double 	sp,
double 	sr,
int 	maxLevel = 1,
TermCriteria  termcrit =
TermCriteria(TermCriteria::MAX_ITER+TermCriteria::EPS, 5, 1)
)
Python:
dst=cv.pyrMeanShiftFiltering(	src, sp, sr[, dst[, maxLevel[, termcrit]]])
*/
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int artc, char** argv) {
	Mat src = imread("../images/example.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	Mat dst;
	pyrMeanShiftFiltering(src, dst, 15, 50, 1, TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 5, 1));
	imshow("result", dst);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
