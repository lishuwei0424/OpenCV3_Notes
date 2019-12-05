#include  <opencv2/opencv.hpp>
#include  <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	cv::Mat  image = cv::imread("1.jpg");
	if (image.empty())
	{
		cout << "image is  empty ,plese input right directy" << endl;
		return -1;
	}

	cv::namedWindow("original image", WINDOW_AUTOSIZE);
	cv::imshow("original image", image);
	cv::Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);

	cv::namedWindow("gray image", WINDOW_AUTOSIZE);
	cv::imshow("gray image", gray);

	imwrite("gary.jpg",gray);

	waitKey();
	return 0;
}





