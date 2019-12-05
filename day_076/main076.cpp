/*
ͼ��͸�ӱ任Ӧ��
���ںܶ���ı�ɨ��ͼ����ʱ����Ϊ���õ�ԭ����ROI������б�����ʱ�����ǻ���취��������Ϊ��ȷ�ĽǶ��ӽ�����������һ���Ĳ��ַ���������ʶ�����ʱ��ͨ��͸��
�任�Ϳ���ȡ�ñȽϺõĲü�Ч����һ���Ϳ���ʵ�ֲü��������ʹ��͸�ӱ任��ؼ��α任�ĺô����£�
1.	͸�ӱ任�����漰�����α任�Ƕ���ת
2.	͸�ӱ任�Ի���ͼ����һ����չ��Ч��
3.	͸�ӱ任������ɶ�ͼ��ROI������ȡ

PS:����-2018-11-30�ķ���
*/

#include <opencv2/opencv.hpp>
#include <math.h>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat src = imread("../images/55.jpg");
	imshow("input", src);

	// ��ֵͼ��
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	imshow("binary", binary);

	// ����ṹԪ��
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(binary, binary, MORPH_OPEN, se);

	// Ѱ���������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	int index = -1;
	int max = 0;
	for (size_t t = 0; t < contours.size(); t++) {
		double area = contourArea(contours[t]);
		if (area > max) {
			max = area;
			index = t;
		}
	}
	// drawContours(src, contours, index, Scalar(0, 0, 255), 2, 8);
	imshow("src", src);

	// Ѱ����С��Ӿ���
	RotatedRect rect = minAreaRect(contours[index]);
	int width = static_cast<int>(rect.size.height);
	int height = static_cast<int>(rect.size.width);
	printf("height %d, width :%d\n", height, width);

	Point2f vertices[4];
	rect.points(vertices);
	vector<Point> src_pts;
	vector<Point> dst_pts;
	dst_pts.push_back(Point(width, height));
	dst_pts.push_back(Point(0, height));
	dst_pts.push_back(Point(0, 0));
	dst_pts.push_back(Point(width, 0));
	for (int i = 0; i < 4; i++) {
		printf("x=%.2f, y=%.2f\n", vertices[i].x, vertices[i].y);
		src_pts.push_back(vertices[i]);
	}

	// ͸�ӱ任
	Mat M = findHomography(src_pts, dst_pts);
	Mat result = Mat::zeros(Size(width, height), CV_8UC3);
	warpPerspective(src, result, M, result.size());
	imshow("result", result);
	waitKey(0);
	destroyAllWindows();

	return 0;
}