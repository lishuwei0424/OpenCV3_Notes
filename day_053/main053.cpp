/*
二值图像分析 – 使用Hu矩实现轮廓匹配
对图像二值图像的每个轮廓，可以计算轮廓几何矩，根据几何矩可以计算图像的中心位置，估计得到中心位置可以计算中心矩、然后再根据中心矩可以计算胡矩。OpenCV中可以通过如下的API一次计算出上述三种矩，API如下：
Moments cv::moments(
	InputArray 	array,
	bool binaryImage = false
)
array是输入的图像轮廓点集合
输出的图像几何矩，根据几何矩输出结果可以计算胡矩，胡矩计算的API如下：
void cv::HuMoments(
const Moments & moments,
double 	hu[7]
)
moments参数表示输入的图像矩
hu[7]表示输出的胡矩七个值

然后我们可以使用hu矩作为输入，对轮廓进行匹配，进行轮廓外形匹配的API如下：
double cv::matchShapes(
	InputArray 	contour1,
	InputArray 	contour2,
	int method,
	double parameter
)
contour1第一个轮廓点集合，或者灰度图像
contour2第二个轮廓点集合，或者灰度图像
method表示比较方法，最常见有
CONTOURS_MATCH_I1
CONTOURS_MATCH_I2
CONTOURS_MATCH_I3
Parameter方法声明的参数，OpenCV3.x版本中已经不需要了。
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void contours_info(Mat &image, vector<vector<Point>> &pts);
int main(int argc, char** argv) {
	Mat src = imread("../images/abc.png");
	imshow("input", src);
	Mat src2 = imread("../images/a5.png");
	imshow("input2", src2);

	// ÂÖÀªÌáÈ¡
	vector<vector<Point>> contours1;
	vector<vector<Point>> contours2;
	contours_info(src, contours1);
	contours_info(src2, contours2);
	// hu¾Ø¼ÆËã
	Moments mm2 = moments(contours2[0]);
	Mat hu2;
	HuMoments(mm2, hu2);
	// ÂÖÀªÆ¥Åä
	for (size_t t = 0; t < contours1.size(); t++) {
		Moments mm = moments(contours1[t]);
		Mat hum;
		HuMoments(mm, hum);
		double dist = matchShapes(hum, hu2, CONTOURS_MATCH_I1, 0);
		printf("contour match distance : %.2f\n", dist);
		if (dist < 1) {
			printf("draw it \n");
			drawContours(src, contours1, t, Scalar(0, 0, 255), 2, 8);
		}
	}

	imshow("match result", src);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

void contours_info(Mat &image, vector<vector<Point>> &contours) {
	Mat gray, binary;
	vector<Vec4i> hierarchy;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
}