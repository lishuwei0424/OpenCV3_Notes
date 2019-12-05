/*
ͼ����̬ѧ �C ��ñ����
��̬ѧ�ĺ�ñ�����Ǳղ���������ͼ��֮��Ĳ��죬��ñ�������Ա�ʾ���£�
��ñ���� = �ղ��� �C ����ͼ��
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
����opָ��ΪMORPH_BLACKHAT����ʾʹ�ö�ñ����
*/

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat dresult, eresult;
	Mat src = imread("../images/cells.png");

	// ��ֵͼ��
	Mat gray, binary, result;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary", binary);

	// ����ṹԪ��
	Mat se = getStructuringElement(MORPH_RECT, Size(9, 9), Point(-1, -1));
	// ��ñ����
	morphologyEx(binary, result, MORPH_BLACKHAT, se);

	// ��ʾ
	imshow("tophat demo", result);
	waitKey(0);
	destroyAllWindows();

	return 0;
}