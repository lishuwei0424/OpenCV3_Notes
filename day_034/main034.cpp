/*
ͼ����

ͼ��������Ҫ�������ֱܷ���ͼ���ģ��/ȥ�롢ͼ���ݶ�/��Ե���֡�ͼ����/��ǿ��ǰ�����������������ǰͨ�����֪ʶ��ķ�������˽⣬ѧϰ�����API��ʹ�á�ͼ���񻯵ı�����ͼ��������˹�˲���ԭͼȨ�����ص��ӵ���� ��

-1   -1  -1
-1    C  -1
-1    -1 -1

��Cֵ����8ʱ���ʾͼ���񻯡�Խ�ӽ�8��ʾ��Ч��Խ��
��Cֵ����8ʱ��ͼ��ĸ�ͨ�˲�
��CֵԽ��ͼ����Ч���ڼ������������ص�����������
*/
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int artc, char** argv) {
	Mat src = imread("../images/ttt.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	Mat sharpen_op = (Mat_<char>(3, 3) << 0, -1, 0,
		-1, 5, -1,
		0, -1, 0);

	Mat result;
	filter2D(src, result, CV_32F, sharpen_op);
	convertScaleAbs(result, result);

	imshow("sharpen image", result);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
