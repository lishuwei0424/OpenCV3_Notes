/*
ͼ����̬ѧ �C ������
��̬ѧ�Ŀ������ǻ��ڸ�ʴ�������������������ʵ�ֵ�
������ = ��ʴ + ����
�����������ã�
����������ɾ����ֵͼ����С�ĸ��ſ飬����ͼ���ֵ��֮������������⣬

void cv::morphologyEx(
	InputArray src,
	OutputArray dst,
	int op,
	InputArray kernel,
	Point anchor = Point(-1,-1),
	int iterations = 1,
	int borderType = BORDER_CONSTANT,
)

src ����ͼ��
dst ���ͼ��
op ��̬ѧ����
kernel �ṹԪ��
anchor ����λ��ê��
iterations ѭ������
borderType ��Ե�������

����opָ��ΪMORPH_OPEN ����ʾʹ�ÿ�����
*/

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat dresult, eresult;
	Mat src = imread("../images/shuini.jpg");

	// ��ֵͼ��
	Mat gray, binary, result;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	GaussianBlur(gray, gray, Size(9, 9), 0, 0);
	adaptiveThreshold(gray, binary, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 45, 15);
	imshow("binary", binary);

	// ����ṹԪ�� 5x5��С����
	Mat se = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
	morphologyEx(binary, result, MORPH_OPEN, se);

	// ��ʾ
	imshow("open demo", result);
	waitKey(0);
	destroyAllWindows();

	return 0;
}