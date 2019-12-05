/*
图像锐化

图像卷积的主要有三功能分别是图像的模糊/去噪、图像梯度/边缘发现、图像锐化/增强，前面的两个功能我们以前通过相关知识点的分享加以了解，学习了相关API的使用。图像锐化的本质是图像拉普拉斯滤波加原图权重像素叠加的输出 ：

-1   -1  -1
-1    C  -1
-1    -1 -1

当C值大于8时候表示图像锐化、越接近8表示锐化效果越好
当C值等于8时候图像的高通滤波
当C值越大，图像锐化效果在减弱、中心像素的作用在提升
*/
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int artc, char** argv) {
	Mat src = imread("../images/ttt.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	Mat sharpen_op = (Mat_<char>(3, 3) << 0, -1, 0,
		-1, 5, -1,
		0, -1, 0);

	Mat result;
	filter2D(src, result, CV_32F, sharpen_op);
	convertScaleAbs(result, result);

	imshow("sharpen image", result);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
