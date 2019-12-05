/*
图像形态学 - 膨胀与腐蚀
膨胀与腐蚀操作不仅可以对二值图像有效操作，对彩色与灰度图像也有作用，对于二值图像的腐蚀与膨胀来说，选择一个好的结构元素至关重要，OpenCV中获取结构元素的API与参数解释如下：
Mat cv::getStructuringElement(
	int shape,
	Size ksize,
	Point anchor = Point(-1,-1)
)
shape是指结构元素的类型，常见的有矩形、圆形、十字交叉
ksize 是指结构元素大小
anchor 中心锚点的位置
*/

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat dresult, eresult;
	Mat src = imread("../images/coins.jpg");

	// 二值图像
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary", binary);

	// 定义结构元素 3x3大小矩形
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	// 膨胀
	dilate(binary, dresult, se, Point(-1, -1), 1, 0);
	// 腐蚀
	erode(binary, eresult, se, Point(-1, -1), 1, 0);

	// 显示
	imshow("dilate", dresult);
	imshow("erode", eresult);
	waitKey(0);
	return 0;
}