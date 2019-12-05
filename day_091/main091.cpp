/*
������ �C HAAR���������ʹ��

HAAR�����������OpenCV�е�HAAR���������֧��������⡢΢Ц���۾�����ͼ��ȣ�ͨ��������ЩԤ��ѵ����HAARģ�����ݿ���ʵ����صĶ����⣬

void cv::CascadeClassifier::detectMultiScale(
	InputArray 	image,
	std::vector&lt; Rect &gt; & objects,
	double scaleFactor = 1.1,
	int minNeighbors = 3,
	int flags = 0,
	Size minSize = Size(),
	Size maxSize = Size()
)
����������������:
Image:����ͼ��
Objects ������
ScaleFactor ��������
minNeighbors ��ʾ������ھ��ο�
flags ��־��OpenCV3.x�Ժ�������
minSize ���Լ�����С����
maxSize ���Լ����������
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
