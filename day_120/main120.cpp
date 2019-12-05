/*
��ά������ʶ��

OpenCV3.4.4���ϰ汾��OpenCV4.0�汾֧�ָù��ܣ�
OpenCV�ڶ�����ģ����QRCodeDetector���������API�ֱ�ʵ�ֶ�ά�������ά�����
bool cv::QRCodeDetector::detect(
	InputArray img,
	OutputArray points
)const
img����ͼ�񣬻ҶȻ��߲�ɫͼ��
points �õ��Ķ�ά���ĸ����������Ϣ

������ά�룡
std::string cv::QRCodeDetector::decode(
	InputArray img,
	InputArray points,
	OutputArray straight_qrcode = noArray()
)
img����ͼ�񣬻ҶȻ��߲�ɫͼ��
points ��ά��ROI��С��Ӿ��ζ�������
qrcode ������Ƕ�ά������ROIͼ����Ϣ
���صĶ�ά��utf-8�ַ���
��������API���ܣ�����ͨ��һ��API����ʵ�֣���API���£�
std::string cv::QRCodeDetector::detectAndDecode(
	InputArray img,
	OutputArray points = noArray(),
	OutputArray straight_qrcode = noArray()
)

PS: �ǲ��Ǹø������ޣ��Ѿ��������120����ʱ
����֮��������£����Ҷ��֧�֣�
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