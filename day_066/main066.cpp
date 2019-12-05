/*
图像形态学 – 开闭操作时候结构元素应用演示
OpenCV中图像形态学开操作与闭操作，根据结构元素的不同可以实现不同的二值图像处理效果，我们可以通过下面的结构元素对图像进行开操作，提取二值图像中水平与垂直线，这个方法比霍夫直线检测要好用得多， 在一些应用场景中会特别有用，图像分析、OCR布局分析中形态学操作十分重要，我们通过两个例子来说明开闭操作的作用。
一，	开操作提取水平线，实现填空题横线位置提取
结构元素大小为20x1
第一张图与第二张图，是开操作提取填空题中水平横线的操作，其步骤分为：
1.	转灰度
2.	转二值，可选降噪
3.	形态学操作，提取水平线
4.	轮廓发现，确定位置

二，	闭操作实现不同层次的轮廓填充
结构元素分为两种：
矩形结构元素25x25大小
圆形结构元素15x15大小
第三张图、第四张图像对应闭操作的相关运行结果。
*/


#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
void open_demo();
void close_demo();
int main(int argc, char** argv)
{
	close_demo();
	destroyAllWindows();

	waitKey(0);
	return 0;
}

void open_demo() {
	Mat dresult, eresult;
	Mat src = imread("../images/fill.png");
	imshow("input", src);

	// 二值图像
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	imshow("binary", binary);

	// 定义结构元素
	Mat se = getStructuringElement(MORPH_RECT, Size(20, 1), Point(-1, -1));
	morphologyEx(binary, binary, MORPH_OPEN, se);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarhy;
	findContours(binary, contours, hierarhy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(-1, -1));
	for (size_t t = 0; t < contours.size(); t++) {
		Rect roi = boundingRect(contours[t]);
		roi.y = roi.y - 10;
		roi.height = 12;
		rectangle(src, roi, Scalar(0, 0, 255), 1, 8, 0);
	}
	// 显示
	imshow("open demo", src);
}

void close_demo() {
	Mat src = imread("../images/morph3.png");
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// 图像二值化
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

	// 闭操作
	// Mat se = getStructuringElement(MORPH_ELLIPSE, Size(15, 15), Point(-1, -1));
	Mat se = getStructuringElement(MORPH_RECT, Size(25, 25), Point(-1, -1));
	morphologyEx(binary, binary, MORPH_CLOSE, se);
	imwrite("D:/close.png", binary);
	imshow("close", binary);
}