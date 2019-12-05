/*
KMeans ���ݷ���

K-Means�㷨��������MacQueen�� K-Means���㷨�Ƕ����ݽ��з�����㷨�����õ�Ӳ���෽ʽ�������ڷǼලѧϰ���㷨��Ԥ��Ҫ��֪����Ϊ�������Ȼ��ÿ�������һ�����ĵ㣬
���ݾ������������ÿ�����ݵ������ĸ�����ǩ��һ��ѭ��ʵ�ֶ��������ݵ����֮�󣬻���ݱ�ǩ���¼���������͵�����λ�ã�Ȼ�����ѭ�����ݼ��ٴη����ǩ�������ݣ���
�˲��ϵ�����ֱ��ָ����ѭ����Ŀ����ǰ������deltaС��ָ����ֵ��ֹͣ���㣬�õ����ո����������ݵı�ǩ��

OpenCV��KMeans���ݷ����APIΪ��
double cv::kmeans(
	InputArray data,
	int K,
	InputOutputArray bestLabels,
	TermCriteria criteria,
	int attempts,
	int flags,
	OutputArray centers = noArray()
)
data��ʾ������������ݣ������ǰ�����֯������ÿһ��Ϊһ���������ݣ��б�ʾ������ά��
K��ʾ���յķ�����Ŀ
bestLabels ��ʾ���շ���ÿ�������ı�ǩ
criteria ��ʾKMeans�ָ��ֹͣ����
attempts ��ʾ������ͬ��ʼ����ǩ���Դ���
flag��ʾ���ĳ�ʼ������
-	KMEANS_RANDOM_CENTERS
-	KMEANS_PP_CENTERS
-	KMEANS_USE_INITIAL_LABELS
centers��ʾ���շָ��Ժ��ÿ��cluster������λ��
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat img(500, 500, CV_8UC3);
	RNG rng(12345);

	Scalar colorTab[] = {
		Scalar(0, 0, 255),
		Scalar(255, 0, 0),
	};

	int numCluster = 2;
	int sampleCount = rng.uniform(5, 500);
	Mat points(sampleCount, 1, CV_32FC2);

	// ���������
	for (int k = 0; k < numCluster; k++) {
		Point center;
		center.x = rng.uniform(0, img.cols);
		center.y = rng.uniform(0, img.rows);
		Mat pointChunk = points.rowRange(k*sampleCount / numCluster,
			k == numCluster - 1 ? sampleCount : (k + 1)*sampleCount / numCluster);
		rng.fill(pointChunk, RNG::NORMAL, Scalar(center.x, center.y), Scalar(img.cols*0.05, img.rows*0.05));
	}
	randShuffle(points, 1, &rng);

	// ʹ��KMeans
	Mat labels;
	Mat centers;
	kmeans(points, numCluster, labels, TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1), 3, KMEANS_PP_CENTERS, centers);

	// �ò�ͬ��ɫ��ʾ����
	img = Scalar::all(255);
	for (int i = 0; i < sampleCount; i++) {
		int index = labels.at<int>(i);
		Point p = points.at<Point2f>(i);
		circle(img, p, 2, colorTab[index], -1, 8);
	}

	// ÿ�����������������Բ
	for (int i = 0; i < centers.rows; i++) {
		int x = centers.at<float>(i, 0);
		int y = centers.at<float>(i, 1);
		printf("c.x= %d, c.y=%d", x, y);
		circle(img, Point(x, y), 40, colorTab[i], 1, LINE_AA);
	}

	imshow("KMeans-Data-Demo", img);
	waitKey(0);
	destroyAllWindows();

	return 0;
}