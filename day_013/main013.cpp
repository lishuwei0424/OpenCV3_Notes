/*
	ͼ��ת(Image Flip)
		ͼ��ת�ı�������ӳ�䣬OpenCV֧������ͼ��ת��ʽ
		- X�ᷭת��flipcode = 0
		- Y�ᷭת, flipcode = 1
		- XY�ᷭת, flipcode = -1

		��ص�API
		flip
		- src�������
		- dst ��ת��ͼ��
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


