/*
ͼ���ֵ���˹ģ��

��ֵģ�� �Ǿ���˵�ϵ����ȫһ�£���˹ģ���������������ؾ����Ӱ�죬�Ծ�����������ʹ�ø�˹�ֲ���ʽ���ɲ�ͬ��Ȩ��ϵ��������ˣ�Ȼ���ô˾�������ͼ�����õ�����������ͼ���˹ģ��֮��������

OpenCV��˹ģ�� API����
void GaussianBlur(
InputArray src,
OutputArray dst,
Size ksize, // KsizeΪ��˹�˲������ڴ�С
double sigmaX, // X�����˲�ϵ��
double sigmaY=0, // Y�����˲�ϵ��
int borderType=BORDER_DEFAULT // Ĭ�ϱ�Ե��ֵ����
)
��Size(0, 0)�ͻ��sigmax��ʼ�������ɸ�˹�����ϵ������ʱsize��Ϊ�������ȴ�size��ʼ�����˹�����ϵ��
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int artc, char** argv) {
	Mat src = imread("../images/test.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	Mat dst1, dst2;
	blur(src, dst1, Size(5, 5), Point(-1, -1), 4);
	GaussianBlur(src, dst2, Size(5, 5), 15, 0, 4);


	imshow("blur", dst1);
	imshow("gaussian blur", dst2);

	waitKey(0);
	destroyAllWindows();
	return 0;
}



