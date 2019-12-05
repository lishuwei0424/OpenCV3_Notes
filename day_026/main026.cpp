/*
��Ե�����˲��㷨 �C ��˹˫��ģ��
ǰ�����ǽ��ܵ�ͼ�������������Ǿ�ֵ���Ǹ�˹��������ģ����������Ƕ���һ����ͬ���ص����ģ��֮��ͼ��ı�Ե��Ϣ�������ڣ��ܵ����ƻ������ǽ�����ܵ��˲�����������ͨ���������ʵ��ͼ��ģ����ͬʱ��ͼ���Ե��������ƻ����˲�֮�����������ı�����ͼ�������Ե����������Ϣ�����ǳ������˲��㷨Ϊ��Ե�����˲��㷨��EPF��������ı�Ե�����˲��㷨�����¼���
-	��˹˫��ģ��
-	Meanshift��ֵǨ��ģ��
-	�ֲ�������ģ��
-	OpenCV�жԱ�Ե�����˲�����һ��ר�ŵ�API
�������ǵķ���ʹ����ĸ�˹˫��ģ����ʼ����˹ģ���ǿ���ͼ��ռ�λ�ö�Ȩ�ص�Ӱ�죬������û�п���ͼ�����طֲ���ͼ���������Ӱ�죬˫��ģ������������ֵ�ֲ���Ӱ�죬������ֵ�ռ�ֲ�����ϴ�Ľ��б����Ӷ������ı�����ͼ��ı�Ե��Ϣ��
C++:
bilateralFilter(
InputArray 	src,
OutputArray 	dst,
int 	d,
double 	sigmaColor,
double 	sigmaSpace,
int 	borderType = BORDER_DEFAULT
)
Python:
dst	=	cv.bilateralFilter(	src, d, sigmaColor, sigmaSpace[, dst[, borderType]]	)

PS:���컻���»�Ͳ��һ�л��������У���������������������
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
	bilateralFilter(src, dst, 0, 100, 10, 4);
	imshow("result", dst);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
