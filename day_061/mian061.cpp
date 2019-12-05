/*
��ֵͼ����� �C ����Բ���
���ݼ�����,Բ������һ���������Ա�ʾΪ������ʽ, ���Զ�������һ��Բ, �����������ص�p(x0, y0)���ص���֪, Բ�뾶��֪,����ת360�ɼ����귽�̿��Եõ�ÿ�����ϵ�����ͬ��,���ֻ��֪��ͼ�������ص�, Բ�뾶,��ת360�������ĵ㴦������ֵ�ض���ǿ.�����ǻ���任���Բ����ѧԭ��
X = x0+rcos(theta)
Y = y0+rsin(theta)

OpenCV�л���Բ����API������������£�
void cv::HoughCircles(
	InputArray image,
	OutputArray circles,
	int method,
	double dp,
	double minDist,
	double param1 = 100,
	double param2 = 100,
	int minRadius = 0,
	int maxRadius = 0
)
image��ʾ���뵥ͨ���ĻҶ�ͼ��
circles ��ʾ����Բ��Ϣ��Բ��+�뾶��
method Բ���ķ���
dp��ʾͼ��ֱ����Ƿ��б仯��Ĭ��1��ʾ���ָ�ԭͼ��Сһ��
minDist��ʾ��⵽��Բ������Բ��֮�����С����
param1 ��ʾ��Ե��ȡ�ĸ���ֵ
param2��ʾ����ռ���ۼ���ֵ
minRadius ��ʾ���Լ��Բ����С�뾶
maxRadius ��ʾ���Լ��Բ�����
*/

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat gray;
	int dp = 2; // �������������ֲ��������¡�dp��ȡֵԽ�ߣ�Խ���׼�⵽Բ��
	int min_radius = 20;
	int max_radius = 100;
	int minDist = 10;
	Mat src = imread("../images/coins.jpg");
	imshow("input", src);
	cvtColor(src, gray, COLOR_BGR2GRAY);
	GaussianBlur(gray, gray, Size(9, 9), 2, 2);
	vector<Vec3f> circles;
	HoughCircles(gray, circles, HOUGH_GRADIENT, dp, minDist, 100, 100, min_radius, max_radius);
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// ����Բ
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		circle(src, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	}
	namedWindow("circles", 1);
	imshow("circles", src);
	waitKey(0);

	destroyAllWindows();
	return 0;
}