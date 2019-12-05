/*
形态学应用 – 使用基本梯度实现轮廓分析

基于形态学梯度实现图像二值化，进行文本结构分析是OCR识别中常用的处理手段之一，这种好处比简单的二值化对图像有更好的分割效果，主要步骤如下：
1.	图像形态学梯度
2.	灰度
3.	全局阈值二值化
4.	轮廓分析
*/

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat src = imread("../images/digit-02.png");
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// 形态学梯度 - 基本梯度
	Mat basic, gray, binary;
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(src, basic, MORPH_GRADIENT, se);
	imshow("basic gradient", basic);

	cvtColor(basic, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary", binary);

	se = getStructuringElement(MORPH_RECT, Size(1, 5), Point(-1, -1));
	morphologyEx(binary, binary, MORPH_DILATE, se);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	for (size_t c = 0; c < contours.size(); c++) {
		Rect rect = boundingRect(contours[c]);
		double area = contourArea(contours[c]);
		if (area < 200)
			continue;
		int h = rect.height;
		int w = rect.width;
		if (h > (3 * w) || h < 20)
			continue;
		rectangle(src, rect, Scalar(0, 0, 255), 1, 8, 0);
	}
	imshow("result", src);
	waitKey(0);
	destroyAllWindows();

	return 0;
}