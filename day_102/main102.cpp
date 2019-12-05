/*
HOG���������� �C ��ȡ������

����HOG���������ǿ���ͨ��Ԥ��ѵ�����������ݣ����ж�߶ȵĶ����⣬OpenCV�л���HOG�����˼����һ�����Ͱ�����ͬʱ���ǻ�����ʵ���Զ������ļ�⣬�����Զ�������⣬���Է�Ϊ�������֣���һ���֣�ͨ����ȡ������HOG�����ӣ������������������ݣ��ڶ�����ͨ��SVM���з���ѧϰ��ѵ��������Ϊģ�͡����������Ժ�Ϳ���ͨ��ģ����ʵ���Զ�����������������������ȷ����һ���֣���ȡHOG�����ӡ�OpenCV����ȡHOG�����ӵ�API��ʾ���£�

virtual void cv::HOGDescriptor::compute(
	InputArray 	img,
	std::vector< float > & 	descriptors,
	Size 	winStride = Size(),
	Size 	padding = Size(),
	const std::vector< Point > & locations = std::vector< Point >()
)
����ͼ���СWxH=72x128
Ĭ�ϵ�HOG�����Ӵ��ڴ�СΪ64x128�������ƶ��Ĳ���8x8
����ÿ�������ڲ���ÿ��Cell��С��8x8�ģ����Դ��ڿ��Ի���Ϊ8x16��Cells��С
����ÿ��Block������˵��ÿ���ƶ�������һ��Cell��8x16Cells���Եõ�����7x15��Block
ÿ��Block����4��Cell, 36�����������Զ�������ͼ��õ���
7x15x36x2 = 7560�����������ӣ���Щ�����ӿ�����Ϊ�������������ݣ�������Ҫ���������ͼ����˵����Ҫ����ִ������Ԥ������ͼ���СresizeΪ�����ڴ�Сһ�»��߰Ѵ���resize��ͼ���Сһ�£�������������һ������
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