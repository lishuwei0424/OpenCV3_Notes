/*
## ͼ���ݶ� �C ������˹����(���׵�������)

ͼ���һ�׵������ӿ��Եõ�ͼ���ݶȾֲ��ݶ���Ӧֵ�����׵�������ͨ�����ٵ�ͼ������ֵǿ�ȵı仯�����ͼ���Ե������ͼ���Ե��ԭ���ͼ���һ�׵����е����ƣ�ֻ���ڶ��׵�������X��Y����Ķ���ƫ��������ͼ����˵��

X����Ķ���ƫ�������� dx = f(x+1, y) + f(x-1, y) �C 2*f(x, y)
Y����Ķ���ƫ�������� dy = f(x, y+1) + f(x, y-1) �C 2*f(x, y)

��X������Y������е������վ͵õ�delta��Ӧ�Ķ��׵������ӣ�����һ��ͼ��������Ĳ��־��Ƕ�Ӧ��������Ķ��׵������ӣ����ǿ��Խ�һ����չ��ǿΪ����������ӡ�

OpenCV��Laplacian�˲��������Ƕ��׵������ֱ�Ե�ĺ�����
void cv::Laplacian(
InputArray src,
OutputArray dst,
int ddepth, // ���Ĭ����-1��ʾ���������ͼ����ͬ
int ksize = 1,// ������������ ����1�����������ӣ�����1���ð���������
double scale = 1,
double delta = 0, // �����ͼ����ϳ���ֵ
int borderType = BORDER_DEFAULT
)

Python:
dst	= cv.Laplacian(src, ddepth[, dst[, ksize[, scale[, delta[, borderType]]]] )

PS:
������˹������һ���ر������ܵ��������ŵı�Ե�������ӣ����Ծ�����Ҫ�����ͼ�����Ƚ���һ����˹ģ����Ȼ���ٽ���������˹���ӵı�Ե��ȡ��������һЩ�����л���������ϲ���Ϊһ�����������Ǿ�����˵��LOG���ӡ�
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int artc, char** argv) {
	Mat image = imread("../images/yuan_test.png");
	if (image.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", image);

	Mat blured, dst;
	GaussianBlur(image, blured, Size(3, 3), 0);
	Laplacian(blured, dst, CV_32F, 1, 1.0, 127.0, BORDER_DEFAULT);
	convertScaleAbs(dst, dst);
	imshow("result", dst);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
