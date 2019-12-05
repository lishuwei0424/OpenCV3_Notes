/*
Canny边缘检测器

1986年，JOHN CANNY 提出一个很好的边缘检测算法，被称为Canny编边缘检测器。Canny边缘检测器是一种经典的图像边缘检测与提取算法，应用广泛，主要是因为Canny边缘检测具备以下特点：
1.	有效的噪声抑制
2.	更强的完整边缘提取能力

Canny算法是如何做到精准的边缘提取的，主要是靠下面五个步骤
1.	高斯模糊 – 抑制噪声
2.	梯度提取得到边缘候选
3.	角度计算与非最大信号抑制
4.	高低阈值链接、获取完整边缘
5.	输出边缘

OpenCV中Canny边缘检测的API如下：
void cv::Canny(
InputArray image,
OutputArray edges,
double threshold1,
double threshold2,
int apertureSize = 3,
bool L2gradient = false
)
threshold1 是Canny边缘检测算法第四步中高低阈值链接中低阈值
threshold2 是Canny边缘检测算法第四步中高低阈值链接中高阈值、高低阈值之比在2:1～3:1之间
最后一个参数是计算gradient的方法L1或者L2
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int artc, char** argv) {
	Mat src = imread("../images/master.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	Mat edges;
	Canny(src, edges, 100, 300, 3, false);
	imshow("edge image", edges);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
