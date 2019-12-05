/*
拉普拉斯金字塔

对输入图像实现金字塔的reduce操作就会生成不同分辨率的图像、对这些图像进行金字塔expand操作，然后使用reduce减去expand之后的结果就会得到图像拉普拉斯金字塔图像。

举例如下：
输入图像G(0)
金字塔reduce操作生成 G(1), G(2), G(3)
拉普拉斯金字塔：
L0 = G(0)-expand(G(1))
L1 = G(1)-expand(G(2))
L2 = G(2)–expand(G(3))

G(0)减去expand(G(1))得到的结果就是两次高斯模糊输出的不同，所以L0称为DOG（高斯不同）、它约等于LOG所以又称为拉普拉斯金字塔。所以要求的图像的拉普拉斯金字塔，首先要进行金字塔的reduce操作，然后在通过expand操作，最后相减得到拉普拉斯金字塔图像。
*/
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void pyramid_up(Mat &image, vector<Mat> &pyramid_images, int level);
void laplaian_demo(vector<Mat> &pyramid_images, Mat &image);
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
	laplaian_demo(p_images, src);

	waitKey(0);
	destroyAllWindows();

	return 0;
}

void pyramid_up(Mat &image, vector<Mat> &pyramid_images, int level) {
	Mat temp = image.clone();
	Mat dst;
	for (int i = 0; i < level; i++) {
		pyrDown(temp, dst);
		//imshow(format("pyramid_up_%d", i), dst);
		temp = dst.clone();
		pyramid_images.push_back(temp);
	}
}

void laplaian_demo(vector<Mat> &pyramid_images, Mat &image) {
	for (int t = pyramid_images.size() - 1; t > -1; t--) {
		Mat dst;
		if (t - 1 < 0) {
			pyrUp(pyramid_images[t], dst, image.size());
			subtract(image, dst, dst);
			dst = dst + Scalar(127, 127, 127);
			imshow(format("laplaian_layer_%d", t), dst);
		}
		else {
			pyrUp(pyramid_images[t], dst, pyramid_images[t - 1].size());
			subtract(pyramid_images[t - 1], dst, dst);
			dst = dst + Scalar(127, 127, 127);
			imshow(format("laplaian_layer_%d", t), dst);
		}
	}
}
