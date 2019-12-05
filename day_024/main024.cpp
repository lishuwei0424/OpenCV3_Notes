/*
ͼ������

ͼ������������ԭ��ܸ��ӣ��еĿ����������ź��ڴ�������з����˶�ʧ�����ܵ����ţ��е��ǳ����豸���߻��������³����������ȶ�����Ӧ��ͼ���Ͼ���ͼ�����������ɫ����ĳ�̶ֳȵĲ�һ���ԡ��������������ϣ�������ͼ���������Է�Ϊ���¼��֣�

- ����������
��һ�������ͼ���г��ֵ�ϡ��ֲ��ĺڰ����ص㣬 �Խ�������һ����Ч��ȥ���ֶξ���ͼ����ֵ�˲�

- ��˹����/���ϸ�˹�ֲ�
һ��������������ͼ��ɼ�(acquisition)�׶η���,���ʱ����������/��/��ȸ����źŶ����ܵ��²�����˹�ֲ�������

- ���ȷֲ�����
����/��������һ�㶼����ΪĳЩ�����ԵĴ����µ�

������ʾ
- ͼ������������
- ͼ���˹��������
*/
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void add_salt_pepper_noise(Mat &image);
void gaussian_noise(Mat &image);
int main(int artc, char** argv) {
	Mat src = imread("../images/cos.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);
	gaussian_noise(src);

	waitKey(0);
	destroyAllWindows();
	return 0;
}

void add_salt_pepper_noise(Mat &image) {
	RNG rng(12345);
	int h = image.rows;
	int w = image.cols;
	int nums = 10000;
	for (int i = 0; i < nums; i++) {
		int x = rng.uniform(0, w);
		int y = rng.uniform(0, h);
		if (i % 2 == 1) {
			image.at<Vec3b>(y, x) = Vec3b(255, 255, 255);
		}
		else {
			image.at<Vec3b>(y, x) = Vec3b(0, 0, 0);
		}
	}
	imshow("salt pepper", image);
}

void gaussian_noise(Mat &image) {
	Mat noise = Mat::zeros(image.size(), image.type());
	randn(noise, (15, 15, 15), (30, 30, 30));
	Mat dst;
	add(image, noise, dst);
	imshow("gaussian noise", dst);
}
