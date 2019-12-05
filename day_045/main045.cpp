/*
ͼ���ֵ����ȥ��

����һ����Ҫ��ֵ����ͼ������������ѡ��
ѡ��һ
ֱ�Ӷ�����ͼ��ת��Ϊ�Ҷ�ͼ��Ȼ���ֵ��
ѡ���
���ȶ�����ͼ����н��룬ȥ���������ţ�Ȼ���ٶ�ֵ��

�ڽ���ȥ������ʱ�򣬻��ǵ�ǰ�����Ƿ���ļ���ȥ��������������ѡ�����
��ֵģ��ȥ����
��˹ģ��ȥ����
˫��/��ֵǨ��ģ��ȥ����
�Ǿֲ���ֵȥ����

���������ͼ��
��һ��ͼ������ͼ��ֱ��ת��Ϊ��ֵͼ��
�ڶ���ͼ������ͼ���ȸ�˹ģ��ȥ������Ȼ���ֵ��ͼ��
������ͼ������ͼ���Ⱦ�ֵǨ��ȥ������Ȼ���ֵ����ͼ��
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("../images/coins.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// ȥ�������ֵ��
	Mat dst, gray, binary;
	pyrMeanShiftFiltering(src, dst, 10, 100);
	// GaussianBlur(src, dst, Size(3, 3), 0, 0);
	cvtColor(dst, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary", binary);
	imwrite("./binary.png", binary);

	waitKey(0);
	destroyAllWindows();

	return 0;
}