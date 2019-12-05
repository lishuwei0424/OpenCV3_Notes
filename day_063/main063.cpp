/*
ͼ����̬ѧ - �����븯ʴ
�����븯ʴ�����������ԶԶ�ֵͼ����Ч�������Բ�ɫ��Ҷ�ͼ��Ҳ�����ã����ڶ�ֵͼ��ĸ�ʴ��������˵��ѡ��һ���õĽṹԪ��������Ҫ��OpenCV�л�ȡ�ṹԪ�ص�API������������£�
Mat cv::getStructuringElement(
	int shape,
	Size ksize,
	Point anchor = Point(-1,-1)
)
shape��ָ�ṹԪ�ص����ͣ��������о��Ρ�Բ�Ρ�ʮ�ֽ���
ksize ��ָ�ṹԪ�ش�С
anchor ����ê���λ��
*/

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat dresult, eresult;
	Mat src = imread("../images/coins.jpg");

	// ��ֵͼ��
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary", binary);

	// ����ṹԪ�� 3x3��С����
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	// ����
	dilate(binary, dresult, se, Point(-1, -1), 1, 0);
	// ��ʴ
	erode(binary, eresult, se, Point(-1, -1), 1, 0);

	// ��ʾ
	imshow("dilate", dresult);
	imshow("erode", eresult);
	waitKey(0);
	return 0;
}