/*
Canny��Ե�����

1986�꣬JOHN CANNY ���һ���ܺõı�Ե����㷨������ΪCanny���Ե�������Canny��Ե�������һ�־����ͼ���Ե�������ȡ�㷨��Ӧ�ù㷺����Ҫ����ΪCanny��Ե���߱������ص㣺
1.	��Ч����������
2.	��ǿ��������Ե��ȡ����

Canny�㷨�����������׼�ı�Ե��ȡ�ģ���Ҫ�ǿ������������
1.	��˹ģ�� �C ��������
2.	�ݶ���ȡ�õ���Ե��ѡ
3.	�Ƕȼ����������ź�����
4.	�ߵ���ֵ���ӡ���ȡ������Ե
5.	�����Ե

OpenCV��Canny��Ե����API���£�
void cv::Canny(
InputArray image,
OutputArray edges,
double threshold1,
double threshold2,
int apertureSize = 3,
bool L2gradient = false
)
threshold1 ��Canny��Ե����㷨���Ĳ��иߵ���ֵ�����е���ֵ
threshold2 ��Canny��Ե����㷨���Ĳ��иߵ���ֵ�����и���ֵ���ߵ���ֵ֮����2:1��3:1֮��
���һ�������Ǽ���gradient�ķ���L1����L2
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

	Mat edges;
	Canny(src, edges, 100, 300, 3, false);
	imshow("edge image", edges);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
