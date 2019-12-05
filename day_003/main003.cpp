#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat  image = cv::imread("1.jpg");
	if (image.empty())
	{
		cout << "image is  empty ,plese input right directy" << endl;
		return -1;
	}

	cv::namedWindow("original image", WINDOW_AUTOSIZE);
	cv::imshow("original image", image);

	//克隆
	Mat  m1 = image.clone();

	//复制
	Mat  m2;
	image.copyTo(m2);

	//赋值
	Mat m3 = image;

    //创造空白的图像
	Mat m4 = Mat::zeros(image.size(), image.type());
	Mat m5 = Mat::zeros(Size(512,512),CV_8UC3);
	Mat m6 = Mat::ones(Size(512, 512), CV_8UC3);

	Mat m7 = (Mat_<char>(3, 3) << 1, 3, 43, 5, 6, 7, 7, 7,8);


	imwrite("m4.jpg",m4);
	imwrite("m5.jpg", m4);


}