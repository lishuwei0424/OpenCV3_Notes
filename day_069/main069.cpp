/*
ͼ����̬ѧ �C ͼ���ݶ�
ͼ����̬ѧ���ݶȸ�����ǰ����ܵ�ͼ��������������ݶ��б��ʲ�ͬ����̬ѧ�ݶȿ��԰������ǻ����ͨ����ı�Ե��������ʵ��ͼ���������߱�Ե��ȡ������ʹ�õ���̬ѧ������ͬ����̬ѧ�ݶ��ַ�Ϊ
-	�����ݶ�
-	���ݶ�
-	���ݶ�
�����ݶ���ͼ�������븯ʴ����֮��Ĳ�ֵ
���ݶ�������ͼ���븯ʴ֮��Ĳ�ֵ
���ݶ�������������ͼ��֮��Ĳ�ֵ
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
����opָ��ΪMORPH_GRADIEN����ʾʹ�û����ݶȲ���
*/

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat basic, exter, inter;
	Mat src = imread("../images/cells.png");
	imshow("input", src);

	// ����ṹԪ��
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));

	// �����ݶ�
	morphologyEx(src, basic, MORPH_GRADIENT, se);
	imshow("basic gradient", basic);

	// ���ݶ�
	morphologyEx(src, exter, MORPH_DILATE, se);
	subtract(exter, src, exter);
	imshow("external gradient", exter);

	// ���ݶ�
	morphologyEx(src, inter, MORPH_ERODE, se);
	subtract(src, inter, inter);
	imshow("internal gradient", inter);

	waitKey(0);
	destroyAllWindows();

	return 0;
}