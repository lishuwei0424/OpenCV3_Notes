/*
���ٵ�ͼ���Ե�˲��㷨

��˹˫��ģ����mean shift��ֵģ�����ֱ�Ե�����˲��㷨������Ϊ�������Ƚϴ��޷�ʵʱʵ��ͼ���Ե�����˲������������ǵ�ʹ�ó�����OpenCV�л�ʵ����һ�ֿ��ٵı�Ե�����˲��㷨����˹˫����mean shift��ֵ�ڼ���ʱ��ʹ����ά����������������ٶ����ĸ���ԭ�򣬸��㷨ͨ���ȼ۱任����γά�ȿռ䣬ʵ�������ݽ�ά����ټ��㡣

OpenCV API����Ϊ��
void cv::edgePreservingFilter(
InputArray src,
OutputArray dst,
int flags = 1,
float sigma_s = 60,
float sigma_r = 0.4f
)

Python:
dst	= cv.edgePreservingFilter(	src[, dst[, flags[, sigma_s[, sigma_r]]]])

����sigma_s��ȡֵ��ΧΪ0��200�� sigma_r��ȡֵ��ΧΪ0��1
��sigma_sȡֵ����ʱ��sigma_rԽ��ͼ���˲�Ч��Խ����
��sigma_rȡֵ����ʱ�򣬴���sigma_sԽ��ͼ��ģ��Ч��Խ����
��sgma_rȡֵ��С��ʱ�򣬴���sigma_sȡֵ������α仯��ͼ��˫���˲�Ч�������ã�

*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int artc, char** argv) {
	Mat src = imread("../images/example.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	Mat dst;
	double tt = getTickCount();
	edgePreservingFilter(src, dst, 1, 60, 0.44);
	double end = (getTickCount() - tt) / getTickFrequency();
	printf("time consume : %f\n ", end);
	imshow("result", dst);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
