/*
KMeans 图像分割
KMean不光可以对数据进行分类，还可以实现对图像分割，什么图像分割，简单的说就要图像的各种像素值，分割为几个指定类别颜色值，这种分割有两个应用，
一个可以实现图像主色彩的简单提取，另外针对特定的应用场景可以实现证件照片的背景替换效果，这个方面早期最好的例子就是证件之星上面的背景替换。当
然要想实现类似的效果，绝对不是简单的KMeans就可以做到的，还有一系列后续的交互操作需要完成。对图像数据来说，要把每个像素点作为单独的样本，按行组织
，只需要调用OpenCV的Mat中函数reshape即可实现
Mat cv::Mat::reshape(
	int cn,
	int rows = 0
)const
cn参数表示通道数
rows表示改为多少行

PS:最近比较忙，上周五与今天的分享有点拖拉
请大家原谅，我还是会继续更新的！
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("../images/toux.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input image", WINDOW_AUTOSIZE);
	imshow("input image", src);

	Scalar colorTab[] = {
		Scalar(0, 0, 255),
		Scalar(0, 255, 0),
		Scalar(255, 0, 0),
		Scalar(0, 255, 255),
		Scalar(255, 0, 255)
	};

	int width = src.cols;
	int height = src.rows;
	int dims = src.channels();

	// 初始化定义
	int sampleCount = width * height;
	int clusterCount = 3;
	Mat labels;
	Mat centers;

	// RGB 数据转换到样本数据
	Mat sample_data = src.reshape(3, sampleCount);
	Mat data;
	sample_data.convertTo(data, CV_32F);

	// 运行K-Means
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
	kmeans(data, clusterCount, labels, criteria, clusterCount, KMEANS_PP_CENTERS, centers);

	// 显示图像分割结果
	int index = 0;
	Mat result = Mat::zeros(src.size(), src.type());
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			index = row * width + col;
			int label = labels.at<int>(index, 0);
			result.at<Vec3b>(row, col)[0] = colorTab[label][0];
			result.at<Vec3b>(row, col)[1] = colorTab[label][1];
			result.at<Vec3b>(row, col)[2] = colorTab[label][2];
		}
	}

	imshow("KMeans-image-Demo", result);
	waitKey(0);
	destroyAllWindows();

	return 0;
}