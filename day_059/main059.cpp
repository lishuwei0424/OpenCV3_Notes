/*
��ֵͼ����� �C ����ֱ�߼��
ͼ�����任��һ���ر����õ�ͼ��任��ͨ����ͼ��������2Dƽ������ϵ�任��������ռ䣬���Է���ԭ����ƽ������������ȡ�ļ���������Ϣ���磺ֱ�ߡ�Բ�ȣ���ͼ���ֱ����Բ�����ǵ��͵����û���ռ�����ʵ�ֶ�ֵͼ�񼸺η��������ӡ����������µ�ֱ�߲������̣�
r = x*cos(theta) + y * sin(theta)
���нǶ�thetaָr��X��֮��ļнǣ�rΪ��ֱ�߼��δ�ֱ���롣


OpenCV���ڻ���ֱ�߼��������API���������ȷ����һ��������������ȡ��ֱ���ڻ���ռ�ü���������Ȼ�����ֱ�ߵ���������������������������������ǿ�����ϵõ��ռ�����ֱ�ߡ���API���£�
void cv::HoughLines(
	InputArray  image,
	OutputArray lines,
	double rho,
	double theta,
	int threshold,
	double srn = 0,
	double stn = 0,
	double min_theta = 0,
	double max_theta = CV_PI
)
Image ����ͼ��
Lines ���ֱ��
Rho ������r�ò���
Theta�ǶȲ���
Threshold�ۼ�����ֵ
Srn��stn��߶Ȼ���任ʱ����Ҫ�ò������������任����Ҫ
min_theta ��С�Ƕ�
max_theta���Ƕ�
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("../images/hand.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// ȥ�������ֵ��
	Mat dst, gray, binary;
	Canny(src, binary, 80, 160, 3, false);
	imshow("binary", binary);
	imwrite("./binary.png", binary);

	// ��׼����ֱ�߼��
	vector<Vec2f> lines;
	HoughLines(binary, lines, 1, CV_PI / 180, 150, 0, 0);

	// ����ֱ��
	Point pt1, pt2;
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0];
		float theta = lines[i][1];
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(src, pt1, pt2, Scalar(0, 0, 255), 3);
	}

	imshow("contours", src);

	waitKey(0);
	return 0;
}


