/*
��ֵģ��

��ֵ�˲���������ͳ�������˲�����һ�֣���ֵ�˲���ͼ���ض��������ͣ�������������ȡ�ñȽϺõ�ȥ��Ч����Ҳ�ǳ�����ͼ��ȥ��������ǿ�ķ���֮һ����ֵ�˲�Ҳ�Ǵ�����ͼ�����ƶ����串�ǵĶ�ӦROI�����£���������ֵ����ȡ��ֵ��Ϊ�������ص�����ֵ

OpenCV��ֵ�˲�API�������£�
medianBlur	(
InputArray 	src,
OutputArray 	dst,
int 	ksize // ���������������ұ������1
)

Python:
dst = cv.medianBlur(	src, ksize[, dst]	)

PS��ƽʱ�Ͽ��õ���ʾͼ��һ������������ҵ�
https://github.com/gloomyfish1998/opencv_tutorial/tree/master/data/images
*/
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int artc, char** argv) {
	Mat src = imread("../images/sp_noise.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	Mat dst;
	medianBlur(src, dst, 5);
	imshow("medianblur ksize=5", dst);

	waitKey(0);
	destroyAllWindows();

	return 0;
}



