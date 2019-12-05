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

	int height = image.rows;
	int width = image.cols;
	int ch = image.channels();

	for(int row=0;row<height;row++)
		for (int col = 0; col < width; col++)
		{
			if (ch == 3)
			{
				Vec3b  bgr=image.at<Vec3b>(row,col);
				bgr[0] = 255 - bgr[0];
				bgr[1] = 255 - bgr[1];
				bgr[2] = 255 - bgr[2];
				image.at<Vec3b>(row, col) = bgr;
			}
			else
			{
				int gray = image.at<uchar>(row, col);
				image.at<uchar>(row, col)=255-gray;
			}
		}

	cv::imshow("inverse image", image);
	waitKey();
	return 0;


}