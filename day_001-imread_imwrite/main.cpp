//lishuwei   imread  cvnamewindow  imwrite  imshow

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

	//显示窗口的名称和属性
	cv::namedWindow("original image", WINDOW_AUTOSIZE);
	cv::imshow("original image", image);
	waitKey();
	return 0;
}




