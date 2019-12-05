#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("../data/butterfly.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	vector<Mat> mv;
	Mat dst1, dst2, dst3;
	// 蓝色通道为零
	split(src, mv);
	//mv[0] = Scalar(0);
	merge(mv, dst1);
	imshow("output1", mv[0]);

	// 绿色通道为零
	split(src, mv);
	//mv[1] = Scalar(0);
	merge(mv, dst2);
	imshow("output2", mv[1]);

	// 红色通道为零
	split(src, mv);
	//mv[2] = Scalar(0);
	merge(mv, dst3);
	imshow("output3", mv[2]);

	waitKey(0);
	destroyAllWindows();
	return 0;
}