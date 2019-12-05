/*
对象检测 – HAAR级联检测器使用

HAAR级联检测器，OpenCV中的HAAR级联检测器支持人脸检测、微笑、眼睛与嘴巴检测等，通过加载这些预先训练的HAAR模型数据可以实现相关的对象检测，

void cv::CascadeClassifier::detectMultiScale(
	InputArray 	image,
	std::vector&lt; Rect &gt; & objects,
	double scaleFactor = 1.1,
	int minNeighbors = 3,
	int flags = 0,
	Size minSize = Size(),
	Size maxSize = Size()
)
各个参数解释如下:
Image:输入图像
Objects 人脸框
ScaleFactor 放缩比率
minNeighbors 表示最低相邻矩形框
flags 标志项OpenCV3.x以后不用啦，
minSize 可以检测的最小人脸
maxSize 可以检测的最大人脸
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
CascadeClassifier faceDetector;
String haar_data_file = "E:/opencv4.01/build/etc/haarcascades/haarcascade_frontalface_alt_tree.xml";
int main(int artc, char** argv) {
	Mat frame, gray;
	vector<Rect> faces;
	VideoCapture capture(1);
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
