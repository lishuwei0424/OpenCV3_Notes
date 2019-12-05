/*
��ֵͼ����� �C ��������뻡��
��ͼ���ֵͼ���ÿ�����������ǿ��Լ��������Ļ������������������������뻡������ʵ�ֶԲ�ͬ��С����Ĺ��ˣ�Ѱ�ҵ����Ǹ���Ȥ��roi�������Ҳ��ͼ���ֵ����������֮һ��OpenCV�������㼯���������API��������
double cv::contourArea(
InputArray 	contour,
bool oriented = false
)

�����������������ԭ���ǻ��ڸ��ֹ�ʽ��
����contour��ʾ����������㼯
����orientedĬ����false���ص����������������������Ϊtrue��ʾ�������˳ʱ�������ʱ�뷽�򷵻���ֵ���߸�ֵ�����

double cv::arcLength(
InputArray curve,
bool closed
)
�����������ߵĻ�����
����curve��ʾ����������㼯
����closedĬ�ϱ�ʾ�Ƿ�պ�����
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("../images/zhifang_ball.png");
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
		// rectangle(src, rect, Scalar(0, 0, 255), 1, 8, 0);

		// �������
		double area = contourArea(contours[t]);
		double curvelen = arcLength(contours[t], true);
		if (area < 100 || curvelen < 100) {
			continue;
		}

		// ��С�������
		RotatedRect rrt = minAreaRect(contours[t]);
		Point2f pts[4];
		rrt.points(pts);

		// ������ת����������λ��
		for (int i = 0; i < 4; i++) {
			line(src, pts[i % 4], pts[(i + 1) % 4], Scalar(0, 255, 0), 2, 8, 0);
		}
		Point2f cpt = rrt.center;
		circle(src, cpt, 2, Scalar(255, 0, 0), 2, 8, 0);
	}
	imshow("contours", src);

	waitKey(0);
	destroyAllWindows();

	return 0;
}