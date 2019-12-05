/*
��ֵͼ����� �C ����ֱ�߼���
OpenCV�л�������һ������ֱ�߼���API����API��Ϊ���ã�����ֱ�ӷ���ֱ�ߵĿռ�����㣬�ȷ��ػ���ռ�������ӵ�ֱ�ۣ�������⣬���һ����������߶γ��ȡ�����Ȳ������ǳ����á��ò���������£�
void cv::HoughLinesP(
	InputArray image,
	OutputArray lines,
	double rho,
	double theta,
	int threshold,
	double 	minLineLength = 0,
	double 	maxLineGap = 0
)
Image�����ֵͼ��
Lines ���ص�ֱ��������
Rho ������r�ò���
Theta�ǶȲ���
Threshold�ۼ�����ֵ
minLineLength��С�߶γ���
maxLineGap�߶μ��
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("../images/morph01.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// ȥ�������ֵ��
	Mat gray, binary;
	Canny(src, binary, 80, 160, 3, false);
	imshow("binary", binary);
	imwrite("D:/binary.png", binary);

	vector<Vec4i> lines;
	HoughLinesP(binary, lines, 1, CV_PI / 180, 80, 30, 10);
	Mat result = Mat::zeros(src.size(), src.type());
	for (size_t i = 0; i < lines.size(); i++)
	{
		line(result, Point(lines[i][0], lines[i][1]),
			Point(lines[i][2], lines[i][3]), Scalar(0, 255, 0), 1, 8);
	}
	imshow("contours", result);

	waitKey(0);
	destroyAllWindows();

	return 0;
}