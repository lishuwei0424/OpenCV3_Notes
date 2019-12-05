/*
��ֵͼ����� �C ֱ������뼫ֵ��Ѱ��
���������з��������˿��Զ�����������Բ����Բ�����֮�⣬�����Զ������㼯����ֱ����ϣ�ֱ����ϵ��㷨�кܶ࣬����ľ�����С���˷������ڶ�Լ�����Է��̣���С���˿����Һ�ֱ�߷��̵�����������ʵ��ֱ����ϣ�OpenCV��ֱ��������ǻ�����С���˷�ʵ�ֵġ�OpenCVʵ��ֱ����ϵ�API���£�
void cv::fitLine(
	InputArray points,
	OutputArray line,
	int distType,
	double param,
	double reps,
	double aeps
)
points��ʾ����ϵ�����㼯��
line�ڶ�ά���ʱ���������vec4f���͵����ݣ�����ά��ϵ�ʱ�������vec6f��vector
distType��ʾ�����ʱ��ʹ�þ�����㹫ʽ����һ�֣�OpenCV֧���������ַ�ʽ��
DIST_L1 = 1
DIST_L2 = 2
DIST_L12 = 4
DIST_FAIR = 5
DIST_WELSCH = 6
DIST_HUBER = 7
param��ģ����Ͼ�����㹫ʽ��Ҫ����C��5~7 distType��Ҫ����C
reps��aeps��ָ����Ͻ���ľ���Ҫ��
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("../images/twolines.png");
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
	imwrite("D:/binary.png", binary);

	Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	dilate(binary, binary, k);

	// �������������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());

	for (size_t t = 0; t < contours.size(); t++) {
		// ����������
		Rect rect = boundingRect(contours[t]);
		int m = max(rect.width, rect.height);
		if (m < 30) continue;
		// ֱ�����
		Vec4f oneline;
		fitLine(contours[t], oneline, DIST_L1, 0, 0.01, 0.01);
		float vx = oneline[0];
		float vy = oneline[1];
		float x0 = oneline[2];
		float y0 = oneline[3];

		// ֱ�߲���б��k��ؾ�b
		float k = vy / vx;
		float b = y0 - k * x0;

		// Ѱ��������ֵ��
		int minx = 0, miny = 10000;
		int maxx = 0, maxy = 0;
		for (int i = 0; i < contours[t].size(); i++) {
			Point pt = contours[t][i];
			if (miny > pt.y) {
				miny = pt.y;
			}
			if (maxy < pt.y) {
				maxy = pt.y;
			}
		}
		maxx = (maxy - b) / k;
		minx = (miny - b) / k;
		line(src, Point(maxx, maxy), Point(minx, miny), Scalar(0, 0, 255), 2, 8, 0);
	}
	imshow("contours", src);

	waitKey(0);
	destroyAllWindows();

	return 0;
}