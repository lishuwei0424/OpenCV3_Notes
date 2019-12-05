/*
USM ����ǿ�㷨

ͼ��������ʵ������һ�ֳ��õ��㷨����Unsharpen Mask�����������񻯵ķ������Ƕ�ԭͼ������һ����˹ģ����Ȼ����ԭ����ͼ���ȥһ��ϵ�����Ը�˹ģ��֮���ͼ��Ȼ���ٰ�ֵScale��0��255��RGB����ֵ��Χ֮�ڡ�����USM�񻯵ķ�������ȥ��һЩϸС�ĸ���ϸ�ں���������һ��ֱ��ʹ�þ�������ӵõ���ͼ���񻯽��������ʵ���š�

USM�񻯹�ʽ��ʾ���£�
��Դͼ��C w*��˹ģ����/��1-w��������w��ʾȨ�أ�0.1��0.9����Ĭ��Ϊ0.6

OpenCV�еĴ���ʵ�ֲ���
1.	��˹ģ��
2.	Ȩ�ص���
3.	������
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int artc, char** argv) {
	Mat src = imread("../images/master.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	Mat blur_img, usm;
	GaussianBlur(src, blur_img, Size(0, 0), 25);
	addWeighted(src, 1.5, blur_img, -0.5, 0, usm);
	imshow("mask image", usm);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
