/*
OpenCV�е��Զ����˲���

ͼ��������Ҫ������ͼ��ģ�����񻯡��ݶȱ�Ե�ȣ�ǰ���Ѿ�����ͼ����ģ�������֪ʶ�㣬OpenCV����֧�������ľ��ģ������ֵ���Ե��������֧���Զ������ˣ�ʵ���Զ�����˲��������Զ������˳�������Ҫ�Ǿ�ֵ���񻯡��ݶȵ����ӡ�����������Զ������˷ֱ����ʵ�־���ľ�ֵģ�����񻯡��ݶȹ��ܡ�

1��	1�� 1      0�� -1�� 0        1�� 0
1��	1�� 1      -1�� 5�� -1        0  -1
1��	1�� 1      0�� -1�� 0

OpenCV�Զ����˲���API:
void cv::filter2D(
InputArray src,
OutputArray dst,
int ddepth, // Ĭ��-1
InputArray kernel, // ����˻��߾�����ڴ�С
Point anchor = Point(-1,-1),
double delta = 0,
int borderType = BORDER_DEFAULT
)
Python:
dst=cv.filter2D(src, ddepth, kernel[, dst[, anchor[, delta[, borderType]]]]	)

int ddepth, // Ĭ��-1����ʾ���������ͼ������һ�£����ǵ��漰����������ʱ����Ҫ����ΪCV_32F���˲����֮����Ҫʹ��convertScaleAbs���������ת��Ϊ�ֽ����͡�



void cv::convertScaleAbs(
	cv::InputArray src, // ��������
	cv::OutputArray dst, // �������
	double alpha = 1.0, // ��������
	double beta = 0.0 // ƫ����
);
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int artc, char** argv) {
	Mat src = imread("../images/test.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	Mat kernel1 = Mat::ones(5, 5, CV_32F) / (float)(25);

	Mat kernel2 = (Mat_<char>(3, 3) << 0, -1, 0,
		-1, 5, -1,
		0, -1, 0);

	Mat kernel3 = (Mat_<int>(2, 2) << 1, 0, 0, -1);

	Mat dst1, dst2, dst3;
	filter2D(src, dst1, -1, kernel1);
	filter2D(src, dst2, -1, kernel2);
	filter2D(src, dst3, CV_32F, kernel3);
	convertScaleAbs(dst3, dst3);

	imshow("blur=5x5", dst1);
	imshow("shape=3x3", dst2);
	imshow("gradient=2x2", dst3);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
