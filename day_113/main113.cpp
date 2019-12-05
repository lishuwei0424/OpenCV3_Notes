/*
KMeans 图像分割 – 主色彩提取
KMeans分割会计算出每个聚类的像素平均值，根据这个可以得到图像的主色彩RGB分布成分多少，得到各种色彩在图像中的比重，绘制出图像对应的取色卡！
这个方面在纺织与填色方面特别有用！主要步骤显示如下：
1.	读入图像建立KMenas样本
2.	使用KMeans图像分割，指定分类数目
3.	统计各个聚类占总像素比率，根据比率建立色卡！
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("../images/master.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input image", WINDOW_AUTOSIZE);
	imshow("input image", src);

	int width = src.cols;
	int height = src.rows;
	int dims = src.channels();

	// 初始化定义
	int sampleCount = width * height;
	int clusterCount = 4;
	Mat labels;
	Mat centers;

	// RGB 数据转换到样本数据
	Mat sample_data = src.reshape(3, sampleCount);
	Mat data;
	sample_data.convertTo(data, CV_32F);

	// 运行K-Means
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
	kmeans(data, clusterCount, labels, criteria, clusterCount, KMEANS_PP_CENTERS, centers);

	Mat card = Mat::zeros(Size(width, 50), CV_8UC3);
	vector<float> clusters(clusterCount);
	for (int i = 0; i < labels.rows; i++) {
		clusters[labels.at<int>(i, 0)]++;
	}
	for (int i = 0; i < clusters.size(); i++) {
		clusters[i] = clusters[i] / sampleCount;
	}
	int x_offset = 0;
	for (int x = 0; x < clusterCount; x++) {
		Rect rect;
		rect.x = x_offset;
		rect.y = 0;
		rect.height = 50;
		rect.width = round(clusters[x] * width);
		x_offset += rect.width;
		int b = centers.at<float>(x, 0);
		int g = centers.at<float>(x, 1);
		int r = centers.at<float>(x, 2);
		rectangle(card, rect, Scalar(b, g, r), -1, 8, 0);
	}

	imshow("Image Color Card", card);
	waitKey(0);
	destroyAllWindows();

	return 0;
}