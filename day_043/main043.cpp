/*
OpenCV��ͼ���ֵѰ���㷨 �C TRIANGLE

ͼ���ֵ�������������ϴη�����ֶ���ֵ��������ݻҶ�ͼ���ֵ�ķ���֮�⣬���м�������ͼ��ֱ��ͼʵ���Զ�ȫ����ֵѰ�ҵķ�����OpenCV��֧�ֵ���OTSU��Triangle����ֱ��ͼ��ֵѰ���㷨���ϴη����ᵽOTSU����������С����ʵ����ֵѰ��, ��������������֮����һ�����ȵ�ֱ��ͼ�ر��,������ʱ��ͼ���ֱ��ͼֻ��һ������,���ʱ��ʹ��TRIANGLE����Ѱ����ֵ�ǱȽϺõ�һ��ѡ��

OpenCV��TRIANGLE�㷨ʹ��ֻ��Ҫ��
threshold������type��������THRESH_TRIANGLE����
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("../images/master.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// �Զ���ֵѰ�����ֵ��
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	double t = threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_TRIANGLE);
	printf("threshold : %.2f\n", t);


	imshow("binary", binary);
	imwrite("./binary.png", binary);

	waitKey(0);
	destroyAllWindows();

	return 0;
}