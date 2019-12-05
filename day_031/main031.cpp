/*
ͼ���ݶ� �C Sobel����

��������ó���ʵ��ͼ��ģ������ȥ�룬������Ѱ��һ��ͼ���������ݶ���Ϣ����Щ�ݶ���Ϣ��ͼ�����ԭʼ�������ݣ���һ������֮��Ϳ�������һЩ�Ƚϸ߼�������������ʾһ��ͼ��ʵ�ֻ���ͼ��������ƥ�䣬ͼ������Ӧ�á�Sobel������һ�ֺܾ����ͼ���ݶ���ȡ���ӣ��䱾���ǻ���ͼ��ռ������������˼����ͼ��һ�׵������ӵ�����֧�֡�OpenCVʵ���˻���Sobel������ȡͼ���ݶȵ�API����ʾ��������£�
void cv::Sobel(
InputArray src, // ����ͼ��
OutputArray dst, // ������
int ddepth, // ͼ�����CV_32F
int dx,// 1��X���� һ�׵���
int dy, // 1��Y���� һ�׵���
int ksize = 3, // ���ڴ�С
double scale = 1, // �������ʣ�1 ��ʾ����
double delta = 0, // ��������ͼ����ϳ���ֵ
int borderType = BORDER_DEFAULT
)
Python:
dst = cv.Sobel(src, ddepth, dx, dy[, dst[, ksize[, scale[, delta[, borderType]]]]])
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

	Mat grad_x, grad_y;
	Mat dst;
	Sobel(src, grad_x, CV_32F, 1, 0, 3, 1, 0, BORDER_DEFAULT);
	Sobel(src, grad_y, CV_32F, 0, 1, 3, 1, 0, BORDER_DEFAULT);

	convertScaleAbs(grad_x, grad_x);
	convertScaleAbs(grad_y, grad_y);

	add(grad_x, grad_y, dst, Mat(), CV_16S);
	convertScaleAbs(dst, dst);

	imshow("gradient", dst);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
