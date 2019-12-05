/*
ͼ��ģ��ƥ��

ģ��ƥ�䱻��Ϊ��򵥵�ģʽʶ�𷽷���ͬʱҲ���ܶ�����Ϊ����û���õ�ģʽʶ�𷽷������������кܴ������������ģ��ƥ���ǹ����������ƱȽ��ϸ�ֻ�������������õ������Ժ�ģ��ƥ��Ż�ȽϺõĿ�ʼ���������������ǻ���������ƥ�䣬�����кܶ�׶ˣ����ǲ���������Ϊ���ż���ģʽʶ��ķ�����ͨ��������ѧϰ���ܶ���ص�ԭ�������ݣ�Ϊ����ѧϰ�������õĻ�����

OpenCV��ģ��ƥ���APIΪ
void cv::matchTemplate (
InputArray image,
InputArray templ,
OutputArray result,
int method,
InputArray mask = noArray()
)
Python:
result = cv.matchTemplate(	image, templ, method[, result[, mask]] )

����method��ʾģ��ƥ��ʱ����õļ����������Ƴ̶ȵķ���������������
TM_SQDIFF = 0
TM_SQDIFF_NORMED = 1
ƽ����ͬ��ƽ����ͬ�Ĺ�һ���汾

TM_CCORR = 2
TM_CCORR_NORMED = 3
����ԣ�ֵԽ�������Խǿ����ʾƥ��̶�Խ�ߡ�
��һ���汾ֵ��0��1֮�䣬1��ʾ�߶�ƥ�䣬0��ʾ��ȫ��ƥ��

TM_CCOEFF = 4
TM_CCOEFF_NORMED = 5
������ӣ�ֵԽ�������Խǿ����ʾƥ��̶�Խ�ߡ�
��һ���汾ֵ��0��1֮�䣬1��ʾ�߶�ƥ�䣬0��ʾ��ȫ��ƥ��
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
