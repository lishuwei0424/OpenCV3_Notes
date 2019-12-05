#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat  src1 = cv::imread("../data/LinuxLogo.jpg");
	cv::Mat  src2 = cv::imread("../data/WindowsLogo.jpg");

	if (src1.empty()|| src2.empty())
	{
		cout << "image is  empty ,plese input right directy" << endl;
		return -1;
	}

	cv::imshow("src1 image", src1);
	cv::imshow("src2 image", src2);

	int height = src1.rows;
	int width = src1.cols;

	int b1 = 0, g1 = 0, r1 = 0;
	int b2 = 0, g2 = 0, r2 = 0;
	int b = 0, g = 0, r = 0;
	Mat result = Mat::zeros(src1.size(), src1.type());
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			b1 = src1.at<Vec3b>(row, col)[0];
			g1 = src1.at<Vec3b>(row, col)[1];
			r1 = src1.at<Vec3b>(row, col)[2];

			b2 = src2.at<Vec3b>(row, col)[0];
			g2 = src2.at<Vec3b>(row, col)[1];
			r2 = src2.at<Vec3b>(row, col)[2];

			result.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b1 + b2);
			result.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g1 + g2);
			result.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r1 + r2);
		}
	}

	imshow("output", result);

	Mat  add_result = Mat::zeros(src1.size(), src1.type());
	add(src1, src2, add_result);
	imshow("add image", add_result);

	Mat  mul_result = Mat::zeros(src1.size(), src1.type());
	multiply(src1, src2, mul_result);
	imshow("mult image", mul_result);

	Mat  sub_result = Mat::zeros(src1.size(), src1.type());
	subtract(src1, src2, sub_result);
	imshow("sub image", sub_result);

	waitKey();
	destroyAllWindows();
	//return 0;
}