/*
KMeans 数据分类

K-Means算法的作者是MacQueen， K-Means的算法是对数据进行分类的算法，采用的硬分类方式，是属于非监督学习的算法，预先要求知道分为几个类别，然后每个类别有一个中心点，
根据距离度量来决定每个数据点属于哪个类别标签，一次循环实现对所有数据点分类之后，会根据标签重新计算各个类型的中心位置，然后继续循环数据集再次分类标签样本数据，如
此不断迭代，直到指定的循环数目或者前后两次delta小于指定阈值，停止计算，得到最终各个样本数据的标签。

OpenCV中KMeans数据分类的API为：
double cv::kmeans(
	InputArray data,
	int K,
	InputOutputArray bestLabels,
	TermCriteria criteria,
	int attempts,
	int flags,
	OutputArray centers = noArray()
)
data表示输入的样本数据，必须是按行组织样本，每一行为一个样本数据，列表示样本的维度
K表示最终的分类数目
bestLabels 表示最终分类每个样本的标签
criteria 表示KMeans分割的停止条件
attempts 表示采样不同初始化标签尝试次数
flag表示中心初始化方法
-	KMEANS_RANDOM_CENTERS
-	KMEANS_PP_CENTERS
-	KMEANS_USE_INITIAL_LABELS
centers表示最终分割以后的每个cluster的中心位置
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

	// 生成随机数
	for (int k = 0; k < numCluster; k++) {
		Point center;
		center.x = rng.uniform(0, img.cols);
		center.y = rng.uniform(0, img.rows);
		Mat pointChunk = points.rowRange(k*sampleCount / numCluster,
			k == numCluster - 1 ? sampleCount : (k + 1)*sampleCount / numCluster);
		rng.fill(pointChunk, RNG::NORMAL, Scalar(center.x, center.y), Scalar(img.cols*0.05, img.rows*0.05));
	}
	randShuffle(points, 1, &rng);

	// 使用KMeans
	Mat labels;
	Mat centers;
	kmeans(points, numCluster, labels, TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1), 3, KMEANS_PP_CENTERS, centers);

	// 用不同颜色显示分类
	img = Scalar::all(255);
	for (int i = 0; i < sampleCount; i++) {
		int index = labels.at<int>(i);
		Point p = points.at<Point2f>(i);
		circle(img, p, 2, colorTab[index], -1, 8);
	}

	// 每个聚类的中心来绘制圆
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