/*
ͼ�������

ͼ�����������
ͼ��������Ƕ�һ������ͼ����ģ�����²���Ϊԭ����С��1/4�������Сһ�룩�������ظ�ģ�����²����Ĺ��̾͵õ��˲�ͬ�ֱ��ʵ����ͼ�񣬵�����һ����γ���ͼ�������������ͼ���������ͼ��Ŀռ��ֱ��ʴ�����ʽ�������ģ����ָ��˹ģ�������������ʽ���ɵĽ�����ͼ���ֳ�Ϊ��˹������ͼ�񡣸�˹������ͼ����������������
reduce �Ǵ�ԭͼ���ɸ�˹������ͼ������һϵ�еͷֱ�ͼ��
expand�ǴӸ�˹������ͼ�������ɸ߷ֱ���ͼ��

����
1.	ͼ���������redude���̻���expand�����б��������
2.	reduce������ÿһ�㶼��ǰһ���1/4

���API
reduce ���� pyrDown
expand���� pyrUp
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
