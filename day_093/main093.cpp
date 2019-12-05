/*
对象检测-LBP特征介绍
局部二值模式(Local Binary Pattern)主要用来实现2D图像纹理分析。其基本思想是用每个像素跟它周围的像素相比较得到局部图像结构，假设中心像素值大于相邻像素值则则相邻像素点赋值为1，否则赋值为0，最终对每个像素点都会得到一个二进制八位的表示，比如11100111。假设3x3的窗口大小，这样对每个像素点来说组合得到的像素值的空间为[0~2^8]。这种结果称为图像的局部二值模式或者简写为了LBP。

PS: 仔细看第一张图就明白LBP是如何计算！
另外推荐看一下我以前的文章：
详解LBP特征与应用(人脸识别)
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
