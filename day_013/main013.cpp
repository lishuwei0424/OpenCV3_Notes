/*
	图像翻转(Image Flip)
		图像翻转的本质像素映射，OpenCV支持三种图像翻转方式
		- X轴翻转，flipcode = 0
		- Y轴翻转, flipcode = 1
		- XY轴翻转, flipcode = -1

		相关的API
		flip
		- src输入参数
		- dst 翻转后图像
		- flipcode
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat  src1 = cv::imread("../data/LinuxLogo.jpg");

	if (src1.empty())
	{
		cout << "image is  empty ,plese input right directy" << endl;
		return -1;
	}

	cv::imshow("src1 image", src1);
	Mat dst = Mat::zeros(src1.size(), src1.type());
	flip(src1, dst, 0);
	imshow("x-x", dst);

	flip(src1, dst, 1);
	imshow("y-y", dst);

	flip(src1, dst, -1);
	imshow("x-y", dst);

	waitKey();
	destroyAllWindows();
	return 0;

}


