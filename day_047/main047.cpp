/*
��ֵͼ����ͨ���״̬ͳ��

OpenCV�е���ͨ�������㷨��������ص�API��
һ���ǲ���ͳ����Ϣ��API
int cv::connectedComponents(
	InputArray 	image, // �����ֵͼ�񣬺�ɫ����
	OutputArray 	labels, // ����ı��ͼ�񣬱���index=0
	int 	connectivity = 8, // ��ͨ��Ĭ����8��ͨ
	int 	ltype = CV_32S // �����labels���ͣ�Ĭ����CV_32S
)
����һ���ǻ������ͨ���ͳ����Ϣ�����API��
int cv::connectedComponentsWithStats(
	InputArray image,
	OutputArray labels,
	OutputArray stats,
	OutputArray centroids,
	int connectivity,
	int ltype,
	int ccltype
)
��ص�ͳ����Ϣ���������stats�Ķ����У�ÿ����ͨ�����һ������������ṹ�塣
CC_STAT_LEFT
Python : cv.CC_STAT_LEFT
	��ͨ�����Ӿ������Ͻ������Xλ����Ϣ

	CC_STAT_TOP
	Python : cv.CC_STAT_TOP
	��ͨ���������Ͻ������Yλ����Ϣ

	CC_STAT_WIDTH
	Python : cv.CC_STAT_WIDTH
	��ͨ�����Ӿ��ο��

	CC_STAT_HEIGHT
	Python : cv.CC_STAT_HEIGHT
	��ͨ�����Ӿ��θ߶�

	CC_STAT_AREA
	Python : cv.CC_STAT_AREA
	��ͨ����������С���������ض���ͳ�ơ�

	Centroids�������ÿ����ͨ���������λ������(x, y)
*/


#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

RNG rng(12345);
void componentwithstats_demo(Mat &image);
int main(int argc, char** argv) {
	Mat src = imread("../images/rice.png");
	if (src.empty()) {
		printf("could not load image...\n");
	}
	imshow("input", src);
	componentwithstats_demo(src);

	waitKey(0);
	return 0;
}

void componentwithstats_demo(Mat &image) {
	// extract labels
	Mat gray, binary;
	GaussianBlur(image, image, Size(3, 3), 0);
	cvtColor(image, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	Mat labels = Mat::zeros(image.size(), CV_32S);
	Mat stats, centroids;
	int num_labels = connectedComponentsWithStats(binary, labels, stats, centroids, 8, 4);
	printf("total labels : %d\n", (num_labels - 1));
	vector<Vec3b> colors(num_labels);

	// background color
	colors[0] = Vec3b(0, 0, 0);

	// object color
	for (int i = 1; i < num_labels; i++) {
		colors[i] = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
	}

	// extract stats info
	Mat dst = image.clone();
	int w = image.cols;
	int h = image.rows;
	for (int i = 1; i < num_labels; i++) {
		// ����λ��
		int cx = centroids.at<double>(i, 0);
		int cy = centroids.at<double>(i, 1);

		int x = stats.at<int>(i, CC_STAT_LEFT);
		int y = stats.at<int>(i, CC_STAT_TOP);
		int w = stats.at<int>(i, CC_STAT_WIDTH);
		int h = stats.at<int>(i, CC_STAT_HEIGHT);
		int area = stats.at<int>(i, CC_STAT_AREA);

		// ����λ�û���
		circle(dst, Point(cx, cy), 2, Scalar(0, 255, 0), 2, 8, 0);
		// ��Ӿ���
		Rect rect(x, y, w, h);
		rectangle(dst, rect, colors[i], 1, 8, 0);
		putText(dst, format("num:%d", i), Point(x, y), FONT_HERSHEY_SIMPLEX, .5, Scalar(0, 0, 255), 1);
		printf(" num: %d,  rice area %d\n", i, area);
	}
	imshow("ccla-demo", dst);
	imwrite("D:/ccla_dst.png", dst);
}
