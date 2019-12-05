/*
������-LBP��������
�ֲ���ֵģʽ(Local Binary Pattern)��Ҫ����ʵ��2Dͼ����������������˼������ÿ�����ظ�����Χ��������Ƚϵõ��ֲ�ͼ��ṹ��������������ֵ������������ֵ�����������ص㸳ֵΪ1������ֵΪ0�����ն�ÿ�����ص㶼��õ�һ�������ư�λ�ı�ʾ������11100111������3x3�Ĵ��ڴ�С��������ÿ�����ص���˵��ϵõ�������ֵ�Ŀռ�Ϊ[0~2^8]�����ֽ����Ϊͼ��ľֲ���ֵģʽ���߼�дΪ��LBP��

PS: ��ϸ����һ��ͼ������LBP����μ��㣡
�����Ƽ���һ������ǰ�����£�
���LBP������Ӧ��(����ʶ��)
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
CascadeClassifier faceDetector;
String haar_data_file = "E:/opencv4.01/build/etc/lbpcascades/lbpcascade_frontalface_improved.xml";
int main(int artc, char** argv) {
	Mat frame, gray;
	vector<Rect> faces;
	VideoCapture capture(0);
	faceDetector.load(haar_data_file);
	namedWindow("frame", WINDOW_AUTOSIZE);
	while (true) {
		capture.read(frame);
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		equalizeHist(gray, gray);
		faceDetector.detectMultiScale(gray, faces, 1.2, 1, 0, Size(30, 30), Size(400, 400));
		for (size_t t = 0; t < faces.size(); t++) {
			rectangle(frame, faces[t], Scalar(0, 0, 255), 2, 8, 0);
		}
		char c = waitKey(10);
		if (c == 27) {
			break;
		}
		imshow("frame", frame);
	}

	waitKey(0);
	destroyAllWindows();

	return 0;
}
