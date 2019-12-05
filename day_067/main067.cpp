/*
ͼ����̬ѧ �C ��ñ����
��̬ѧ�Ķ�ñ������ͼ�������뿪����֮��Ĳ��죬��ñ������ʱ�����������ȡͼ����΢С�����ر����ã���ñ������
��ñ = ԭͼ �C ������
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
����opָ��ΪMORPH_TOPHAT ����ʾʹ�ö�ñ����
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
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(binary, result, MORPH_TOPHAT, se);

	// ��ʾ
	imshow("tophat demo", result);
	waitKey(0);
	destroyAllWindows();

	return 0;
}