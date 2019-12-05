/*
OpenCV��ͼ���������Ӧ��ֵ�㷨

OpenCV�е�����Ӧ��ֵ�㷨��Ҫ�ǻ��ھ�ֵʵ�֣����ݼ����ֵ�ķ�����ͬ��Ϊ����ģ����ֵ���˹ģ����ֵ��Ȼ��ʹ��ԭͼ��ȥ��ֵͼ�񣬵õ��Ĳ�ֵͼ���������Ӧ�ָ��ص�API���£�
void cv::adaptiveThreshold(
InputArray src,
OutputArray dst,
double maxValue,
int adaptiveMethod,
int thresholdType,
int blockSize,
double C
)
����blockSizeȡֵ������������Cȡֵ��10����

����Ӧ�������ͣ�
ADAPTIVE_THRESH_GAUSSIAN_C = 1
ADAPTIVE_THRESH_MEAN_C = 0

����ֵ��������thresholdTypeΪ��THRESH_BINARY
��ֵͼ�� = ԭͼ �C ��ֵͼ�� > -C ? 255 : 0

����ֵ��������thresholdTypeΪ��THRESH_BINARY_INV
��ֵͼ�� = ԭͼ �C ��ֵͼ�� > -C ? 0 : 255
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("../images/text1.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// �Զ���ֵѰ�����ֵ��
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	adaptiveThreshold(gray, binary, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 25, 10);

	imshow("binary", binary);
	imwrite("./binary.png", binary);

	waitKey(0);
	destroyAllWindows();

	return 0;
}