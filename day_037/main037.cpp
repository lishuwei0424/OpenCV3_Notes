/*
图像金字塔

图像金字塔概念
图像金字塔是对一张输入图像先模糊再下采样为原来大小的1/4（宽高缩小一半）、不断重复模糊与下采样的过程就得到了不同分辨率的输出图像，叠加在一起就形成了图像金字塔、所以图像金字塔是图像的空间多分辨率存在形式。这里的模糊是指高斯模糊，所以这个方式生成的金字塔图像又称为高斯金字塔图像。高斯金字塔图像有两个基本操作
reduce 是从原图生成高斯金字塔图像、生成一系列低分辨图像
expand是从高斯金字塔图像反向生成高分辨率图像

规则：
1.	图像金字塔在redude过程或者expand过程中必须是逐层
2.	reduce过程中每一层都是前一层的1/4

相关API
reduce 操作 pyrDown
expand操作 pyrUp
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void pyramid_up(Mat &image, vector<Mat> &pyramid_images, int level);
void pyramid_down(vector<Mat> &pyramid_images);
int main(int artc, char** argv) {
	Mat src = imread("../images/master.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	vector<Mat> p_images;
	pyramid_up(src, p_images, 3);
	pyramid_down(p_images);

	waitKey(0);
	destroyAllWindows();

	return 0;
}

void pyramid_up(Mat &image, vector<Mat> &pyramid_images, int level) {
	Mat temp = image.clone();
	Mat dst;
	for (int i = 0; i < level; i++) {
		pyrDown(temp, dst);
		imshow(format("pyramid_up_%d", i), dst);
		temp = dst.clone();
		pyramid_images.push_back(temp);
	}
}

void pyramid_down(vector<Mat> &pyramid_images) {
	for (int t = pyramid_images.size() - 1; t > -1; t--) {
		Mat dst;
		pyrUp(pyramid_images[t], dst);
		imshow(format("pyramid_down_%d", t), dst);
	}
}
