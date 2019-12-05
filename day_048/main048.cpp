/*
��ֵͼ����� �C ��������

ͼ����ͨ������������Եõ���ֵͼ���ÿ����ͨ������������ǻ��޷���֪�������֮��Ĳ�ι�ϵ�뼸�����˹�ϵ�����������Ҫ��һ������ͼ������������Ϣ�Ϳ���ͨ��OpenCV����������API��ȡ��ֵͼ�������������Ϣ����������API���£�
void cv::findContours(
	InputOutputArray image,
	OutputArrayOfArrays contours,
	OutputArray hierarchy,
	int mode,
	int method,
	Point offset = Point()
)
��������������£�
Image��ʾ����ͼ�񣬱����Ƕ�ֵͼ�񣬶�ֵͼ�����threshold�����Canny�����inRange���������Ӧ��ֵ����ȡ�
Contours��ȡ��������ÿ��������һϵ�еĵ㼯��
Hierarchy�����Ĳ����Ϣ��ÿ���������ĸ������Ϣ���ֱ���ͬ����һ����ǰһ������һ���ӽڵ㡢���ڵ�
mode ��ʾ����Ѱ��ʱ������˽ṹ����
-RETR_EXTERNAL��ʾֻ�������������
-RETR_TREE��ʾ�����������ṹ

Method��ʾ�����㼯��ȡ���ǻ���ʲô�㷨���������ǻ���CHAIN_APPROX_SIMPLE��ʽ���뷽��

���ڵõ�������OpenCVͨ�������API����ÿ������
void cv::drawContours(
	InputOutputArray image,
	InputArrayOfArrays contours,
	int contourIdx,
	const Scalar & 	color,
	int thickness = 1,
	int lineType = LINE_8,
	InputArray 	hierarchy = noArray(),
	int maxLevel = INT_MAX,
	Point offset = Point()
)
��thicknessΪ������ʱ���ʾ���Ƹ�����
��thicknessΪ-1��ʾ��������
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
	GaussianBlur(src, dst, Size(3, 3), 0, 0);
	cvtColor(dst, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary", binary);
	imwrite("../binary.png", binary);

	// �������������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
	for (size_t t = 0; t < contours.size(); t++) {
		drawContours(src, contours, t, Scalar(0, 0, 255), 2, 8);
	}
	imshow("contours", src);

	waitKey(0);
	destroyAllWindows();

	return 0;
}