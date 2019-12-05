/*
ͼ����̬ѧ - �����븯ʴ

�����븯ʴ��ͼ����̬ѧ�������������������̬ѧ�������������ǻ������������������ϵõ��ģ�ͼ����̬ѧ�Ƕ�ֵͼ���������Ҫ��֧ѧ�ơ���OpenCV�������븯ʴ��Ӧ������ص�API�����Ϳ��Կ��������ֵ�˲����������ֵ�滻�������ص㣻��ʴ���Կ�������Сֵ�˲���������Сֵ�滻�������ص㡣

���͵�API���£�

void cv::dilate(
InputArray src,
OutputArray dst,
InputArray kernel,
Point anchor = Point(-1,-1),
int iterations = 1,
int borderType = BORDER_CONSTANT,
const Scalar & borderValue = morphologyDefaultBorderValue()
)

src ����ͼ������ͨ����
dst ���ͼ��������ͨ����Ŀ��������뱣��һ��
kernel �ṹԪ��
anchor ����λ��ê��
iterations ѭ������
borderType ��Ե�������


��ʴ��API���£�

void cv::erode(
InputArray src,
OutputArray dst,
InputArray kernel,
Point anchor = Point(-1,-1),
int iterations = 1,
int borderType = BORDER_CONSTANT,
const Scalar & borderValue = morphologyDefaultBorderValue()
)
src ����ͼ������ͨ����
dst ���ͼ��������ͨ����Ŀ��������뱣��һ��
kernel �ṹԪ��
anchor ����λ��ê��
iterations ѭ������
borderType ��Ե�������

PS: ������ʵıȽ϶࣬��ÿ�����һ��֪ʶ�����������⣬��֤�ô�ҵ����ⲻ������õ��ظ�����л�����⣡
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
	imshow("input", src);
	// ����ṹԪ�� 3x3��С����
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	// ����
	dilate(src, dresult, se, Point(-1, -1), 1, 0);
	// ��ʴ
	erode(src, eresult, se, Point(-1, -1), 1, 0);

	// ��ʾ
	imshow("dilate", dresult);
	imshow("erode", eresult);
	waitKey(0);
	destroyAllWindows();

	return 0;
}