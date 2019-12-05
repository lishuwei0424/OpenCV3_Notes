/*
������˹������

������ͼ��ʵ�ֽ�������reduce�����ͻ����ɲ�ͬ�ֱ��ʵ�ͼ�񡢶���Щͼ����н�����expand������Ȼ��ʹ��reduce��ȥexpand֮��Ľ���ͻ�õ�ͼ��������˹������ͼ��

�������£�
����ͼ��G(0)
������reduce�������� G(1), G(2), G(3)
������˹��������
L0 = G(0)-expand(G(1))
L1 = G(1)-expand(G(2))
L2 = G(2)�Cexpand(G(3))

G(0)��ȥexpand(G(1))�õ��Ľ���������θ�˹ģ������Ĳ�ͬ������L0��ΪDOG����˹��ͬ������Լ����LOG�����ֳ�Ϊ������˹������������Ҫ���ͼ���������˹������������Ҫ���н�������reduce������Ȼ����ͨ��expand�������������õ�������˹������ͼ��
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
