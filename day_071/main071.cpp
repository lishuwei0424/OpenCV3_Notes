/*
��̬ѧ���� �C ���л�����

��̬ѧ�Ļ��л����в��������ݽṹԪ�ز�ͬ��������ȡ��ֵͼ���е�һЩ�������򣬵õ�������Ҫ�Ľ�������л����в�����APIҲ������ǰ��һֱ�õ�API��ֻ�Ƕ�OP�������޸�
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
����opָ��ΪMORPH_HITMISS����ʾʹ�û��л�����
*/

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat dresult, eresult;
	Mat src = imread("../images/cross.png");

	// ��ֵͼ��
	Mat gray, binary, result;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	imshow("binary", binary);

	// ����ṹԪ��
	Mat se = getStructuringElement(MORPH_CROSS, Size(11, 11), Point(-1, -1));
	// ���л�����
	morphologyEx(binary, result, MORPH_HITMISS, se);

	// ��ʾ
	imshow("hit-and-miss demo", result);
	waitKey(0);
	destroyAllWindows();

	return 0;
}