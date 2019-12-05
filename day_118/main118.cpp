/*
Grabcutͼ��ָ�

Grabcut�ǻ���ͼ��(graph cut)ʵ�ֵ�ͼ��ָ��㷨������Ҫ�û�����һ��bounding box��Ϊ�ָ�Ŀ��λ�ã�ʵ�ֶ�Ŀ���뱳���ķ���/�ָ
�����KMeans��MeanShift��ͼ��ָ���кܴ�Ĳ�ͬ������Grabcut�ָ��ٶȿ죬Ч���ã�֧�ֽ�������������ںܶ�APPͼ��ָ�/�����黯
������п��Կ�������Ӱ��
void cv::grabCut(
	InputArray 	img,
	InputOutputArray 	mask,
	Rect 	rect,
	InputOutputArray 	bgdModel,
	InputOutputArray 	fgdModel,
	int 	iterCount,
	int 	mode = GC_EVAL
)
img�������ͨ��ͼ��
mask����ĵ�ͨ��ͼ�񣬳�ʼ����ʽΪGC_INIT_WITH_RECT��ʾROI������Ա���ʼ��Ϊ��
GC_BGD ����Ϊ���Եı������� 0
GC_FGD ����Ϊ���Ե�ǰ������ 1
GC_PR_BGD ����Ϊ���ܵı������� 2
GC_PR_FGD ����Ϊ���ܵ�ǰ������ 3
rect ��ʾroi����
bgdModel��ʾ��ʱ����ģ������
fgdModel��ʾ��ʱǰ��ģ������
iterCount��ʾͼ���㷨��������
mode��ʹ���û��ṩ��roiʱ��ʹ��GC_INIT_WITH_RECT
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("../images/master.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		return 0;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	Mat mask = Mat::zeros(src.size(), CV_8UC1);
	Rect rect(180, 20, 180, 220);
	Mat bgdmodel = Mat::zeros(1, 65, CV_64FC1);
	Mat fgdmodel = Mat::zeros(1, 65, CV_64FC1);
	grabCut(src, mask, rect, bgdmodel, fgdmodel, 5, GC_INIT_WITH_RECT);
	Mat result;
	for (int row = 0; row < mask.rows; row++) {
		for (int col = 0; col < mask.cols; col++) {
			int pv = mask.at<uchar>(row, col);
			if (pv == 1 || pv == 3) {
				mask.at<uchar>(row, col) = 255;
			}
			else {
				mask.at<uchar>(row, col) = 0;
			}
		}
	}
	bitwise_and(src, src, result, mask);
	imshow("grabcut result", result);
	waitKey(0);
	destroyAllWindows();

	return 0;
}