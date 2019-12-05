/*
ͼ����̬ѧ �C �ղ���
��̬ѧ�ıղ�����������һ��Ҳ�ǻ��ڸ�ʴ�������������������ʵ�ֵ�
�ղ��� = ���� + ��ʴ
�ղ��������ã�
�ղ�����������ֵͼ���п׶������γ������ıպ�������ͨ���
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

����opָ��ΪMORPH_CLOSE ����ʾʹ�ñղ���
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

	// ����ṹԪ�� 5x5��С����
	Mat se1 = getStructuringElement(MORPH_RECT, Size(25, 5), Point(-1, -1));
	Mat se2 = getStructuringElement(MORPH_RECT, Size(5, 25), Point(-1, -1));
	morphologyEx(binary, result, MORPH_CLOSE, se1);
	morphologyEx(result, result, MORPH_CLOSE, se2);

	// ��ʾ
	imshow("open demo", result);
	waitKey(0);
	destroyAllWindows();

	return 0;
}