//lishuwei     

#include  <opencv2/opencv.hpp>
#include  <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	cv::Mat  image =cv::imread("building.jpg");
	if (image.empty())
	{
		cout << "image is  empty ,plese input right directy" << endl;
		return -1;
	}

	//显示窗口的名称和属性
	cv::namedWindow("original image", WINDOW_AUTOSIZE);
	cv::imshow("original image", image);

	double  minval, maxval;
	Point   minpos, maxpos;

	minMaxLoc(image, &minval, &maxval, &minpos, &maxpos,Mat());
    printf("%f %f\n",minval,maxval);
	printf("min loc: (%d, %d) \n", minpos.x, minpos.y);
	printf("max loc: (%d, %d)\n", maxpos.x, maxpos.y);

	Mat  means, stddev;
	meanStdDev(image, means, stddev);
	printf("blue channel->> mean: %.2f, stddev: %.2f\n", means.at<double>(0, 0), stddev.at<double>(0, 0));
	printf("green channel->> mean: %.2f, stddev: %.2f\n", means.at<double>(1, 0), stddev.at<double>(1, 0));
	printf("red channel->> mean: %.2f, stddev: %.2f\n", means.at<double>(2, 0), stddev.at<double>(2, 0));

	waitKey();
	destroyAllWindows();
	return 0;

}