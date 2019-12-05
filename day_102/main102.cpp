/*
HOG特征描述子 – 提取描述子

对于HOG特征，我们可以通过预先训练的特征数据，进行多尺度的对象检测，OpenCV中基于HOG的行人检测是一个典型案例，同时我们还可以实现自定义对象的检测，这种自定义对象检测，可以分为两个部分，第一部分：通过提取样本的HOG描述子，生成样本的特征数据，第二部分通过SVM进行分类学习与训练，保存为模型。这样我们以后就可以通过模型来实现自定义对象检测啦。今天我们首先分享第一部分，提取HOG描述子。OpenCV中提取HOG描述子的API表示如下：

virtual void cv::HOGDescriptor::compute(
	InputArray 	img,
	std::vector< float > & 	descriptors,
	Size 	winStride = Size(),
	Size 	padding = Size(),
	const std::vector< Point > & locations = std::vector< Point >()
)
输入图像大小WxH=72x128
默认的HOG描述子窗口大小为64x128，窗口移动的步长8x8
对于每个窗口内部，每个Cell大小是8x8的，所以窗口可以划分为8x16的Cells大小
对于每个Block区域来说，每次移动步长是一个Cell，8x16Cells可以得到总数7x15个Block
每个Block都是4个Cell, 36个向量，所以对于输入图像得到：
7x15x36x2 = 7560个特征描述子，这些描述子可以作为浮点数特征数据，对于需要输入的样本图像来说，需要首先执行以下预处理，把图像大小resize为跟窗口大小一致或者把窗口resize跟图像大小一致，这样有利于下一步处理
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("../images/gaoyy_min.png");
	if (src.empty()) {
		printf("could not load image..\n");
		return -1;
	}
	imshow("input", src);
	HOGDescriptor hog;
	vector<float> features;
	hog.compute(src, features, Size(8, 8), Size(0, 0));

	printf("feature sum size :%d \n", features.size());
	for (int i = 0; i < features.size(); i++) {
		printf("v: %.2f\n ", features[i]);
	}
	imshow("result", src);
	waitKey(0);
	destroyAllWindows();

	return 0;
}