/*
图像模板匹配

模板匹配被称为最简单的模式识别方法、同时也被很多人认为是最没有用的模式识别方法。这里里面有很大的误区，就是模板匹配是工作条件限制比较严格，只有满足理论设置的条件以后，模板匹配才会比较好的开始工作，而且它不是基于特征的匹配，所以有很多弊端，但是不妨碍它成为入门级别模式识别的方法，通过它可以学习到很多相关的原理性内容，为后续学习打下良好的基础。

OpenCV中模板匹配的API为
void cv::matchTemplate (
InputArray image,
InputArray templ,
OutputArray result,
int method,
InputArray mask = noArray()
)
Python:
result = cv.matchTemplate(	image, templ, method[, result[, mask]] )

其中method表示模板匹配时候采用的计算像素相似程度的方法，常见有如下
TM_SQDIFF = 0
TM_SQDIFF_NORMED = 1
平方不同与平方不同的归一化版本

TM_CCORR = 2
TM_CCORR_NORMED = 3
相关性，值越大相关性越强，表示匹配程度越高。
归一化版本值在0～1之间，1表示高度匹配，0表示完全不匹配

TM_CCOEFF = 4
TM_CCOEFF_NORMED = 5
相关因子，值越大相关性越强，表示匹配程度越高。
归一化版本值在0～1之间，1表示高度匹配，0表示完全不匹配
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
const float t = 0.95;
int main(int artc, char** argv) {
	Mat src = imread("../images/llk.jpg");
	Mat tpl = imread("../images/llk_tpl.png");
	if (src.empty() || tpl.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	imshow("input", src);
	imshow("tpl", tpl);

	int result_h = src.rows - tpl.rows + 1;
	int result_w = src.cols - tpl.cols + 1;
	Mat result = Mat::zeros(Size(result_w, result_h), CV_32FC1);
	matchTemplate(src, tpl, result, TM_CCOEFF_NORMED);
	imshow("result image", result);
	int h = result.rows;
	int w = result.cols;
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			float v = result.at<float>(row, col);
			// printf("v = %.2f\n", v);
			if (v > t) {
				rectangle(src, Point(col, row), Point(col + tpl.cols, row + tpl.rows), Scalar(255, 0, 0), 1, 8, 0);
			}
		}
	}
	imshow("template matched result", src);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
