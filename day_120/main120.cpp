/*
二维码检测与识别

OpenCV3.4.4以上版本与OpenCV4.0版本支持该功能！
OpenCV在对象检测模块中QRCodeDetector有两个相关API分别实现二维码检测与二维码解析
bool cv::QRCodeDetector::detect(
	InputArray img,
	OutputArray points
)const
img输入图像，灰度或者彩色图像
points 得到的二维码四个点的坐标信息

解析二维码！
std::string cv::QRCodeDetector::decode(
	InputArray img,
	InputArray points,
	OutputArray straight_qrcode = noArray()
)
img输入图像，灰度或者彩色图像
points 二维码ROI最小外接矩形顶点坐标
qrcode 输出的是二维码区域ROI图像信息
返回的二维码utf-8字符串
上述两个API功能，可以通过一个API调用实现，该API如下：
std::string cv::QRCodeDetector::detectAndDecode(
	InputArray img,
	OutputArray points = noArray(),
	OutputArray straight_qrcode = noArray()
)

PS: 是不是该给个点赞，已经更新完成120个课时
春节之后继续更新！请大家多多支持！
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("../data/qrcode.jpg");
	imshow("image", src);
	Mat gray, qrcode_roi;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	QRCodeDetector qrcode_detector;
	vector<Point> pts;
	string detect_info;
	bool det_result = qrcode_detector.detect(gray, pts);
	if (det_result) {
		detect_info = qrcode_detector.decode(gray, pts, qrcode_roi);
	}
	vector< vector<Point> > contours;
	contours.push_back(pts);
	drawContours(src, contours, 0, Scalar(0, 0, 255), 2);
	putText(src, detect_info.c_str(), Point(20, 200), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 0, 255), 2, 8);
	printf("qrcode info %s \n", detect_info.c_str());
	imshow("result", src);
	waitKey(0);
	destroyAllWindows();

	return 0;
}