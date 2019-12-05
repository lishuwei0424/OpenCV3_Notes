/*
KNN�㷨����

OpenCV�л���ѧϰģ���������㷨KNN�� ʹ��KNN�㷨ʵ����д����ʶ��OpenCV��sample/data����һ���Դ�����д�������ݼ�ͼ��
0~9 ÿ����500���������ܼ���5000�����֡�ͼ���СΪ1000x2000�Ĵ�Сͼ�񣬷ָ�Ϊ20x20��С�ĵ�������ͼ��ÿ������400�����ء�
Ȼ��ʹ��KNN���APIʵ��ѵ�������ı��档���µ�˳�����£�
1.	�������ͼ��digit.png(�������ҵ�github���أ���֪����ַ���ö�����)
2.	���������������ǩ
3.	����KNNѵ��������ѵ�����

OpenCV��KNN������API���£�
Ptr&lt;KNearest&gt; knn = KNearest::create();
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace cv::ml;
using namespace std;

int main(int argc, char** argv) {
	Mat data = imread("../images/digits.png");
	Mat gray;
	cvtColor(data, gray, COLOR_BGR2GRAY);

	// �ָ�Ϊ5000��cells
	Mat images = Mat::zeros(5000, 400, CV_8UC1);
	Mat labels = Mat::zeros(5000, 1, CV_8UC1);
	Rect rect;
	rect.height = 20;
	rect.width = 20;
	int index = 0;
	Rect roi;
	roi.x = 0;
	roi.height = 1;
	roi.width = 400;
	for (int row = 0; row < 50; row++) {
		int label = row / 5;
		for (int col = 0; col < 100; col++) {
			Mat digit = Mat::zeros(20, 20, CV_8UC1);
			index = row * 100 + col;
			rect.x = col * 20;
			rect.y = row * 20;
			gray(rect).copyTo(digit);
			Mat one_row = digit.reshape(1, 1);
			roi.y = index;
			one_row.copyTo(images(roi));
			labels.at<uchar>(index, 0) = label;
		}
	}
	printf("load sample hand-writing data...\n");

	// ת��Ϊ������
	images.convertTo(images, CV_32FC1);
	labels.convertTo(labels, CV_32SC1);

	// ��ʼKNNѵ��
	printf("Start to knn train...\n");
	Ptr<KNearest> knn = KNearest::create();
	knn->setDefaultK(5);
	knn->setIsClassifier(true);
	Ptr<ml::TrainData> tdata = ml::TrainData::create(images, ml::ROW_SAMPLE, labels);
	knn->train(tdata);
	knn->save("./knn_knowledge.yml");
	printf("Finished KNN...\n");
	return true;
}