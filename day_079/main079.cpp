/*
��Ƶ���� - ����/ǰ�� ��ȡ
��Ƶ������������õļ���֮һ����ͨ��������������ȡǰ���ƶ����󣬵õ�ǰ���Ķ���maskͼ����õı���������������ͨ��֡�������
��ǰ��һ֡��Ϊ����ͼ���뵱ǰ֡����������������ַ����Թ���������Ӱ��ǳ����У����кõİ취��ͨ����ǰ��һϵ��֡��ȡ����ģ�ͽ���
�����OpenCV��ʵ�ֵı���ģ����ȡ�㷨�����֣�һ���ǻ��ڸ�˹���ģ��GMMʵ�ֵı�����ȡ������һ���ǻ��������KNNʵ�ֵġ�������ص�AP
I���Թ�������ʹ�á�
���API
Ptr<BackgroundSubtractorMOG2> cv::createBackgroundSubtractorMOG2(
int  history = 500,
double 	varThreshold = 16,
bool  detectShadows = true
)
�����������£�
history��ʾ����֡����500֡��ѡ��history = 1�ͱ����֡��
varThreshold��ʾ������ģ��֮������Ͼ��룬ֵԽ��ֻ����Щ���µ����ػᱻ�鵽ǰ����ֵԽСǰ���Թ���Խ���С�
detectShadows �Ƿ�����Ӱ��⣬��ѡ��False�����ٶȿ�㡣

����
Ptr<BackgroundSubtractor> pBackSub = createBackgroundSubtractorMOG2();
Ptr<BackgroundSubtractor> pBackSub = createBackgroundSubtractorKNN();

���������Ļ���ԭ���ͼһ��
*/

#include <opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {

	VideoCapture capture("../images/video.avi");

	if (!capture.isOpened()) {
		printf("could not open camera...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	namedWindow("mask", WINDOW_AUTOSIZE);

	int fps = capture.get(CAP_PROP_FPS);
	int width = capture.get(CAP_PROP_FRAME_WIDTH);
	int height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int num_of_frames = capture.get(CAP_PROP_FRAME_COUNT);
	printf("frame width: %d, frame height: %d, FPS : %d \n", width, height, fps);
	Ptr<BackgroundSubtractor> pMOG2 = createBackgroundSubtractorMOG2(500, 1000, false);
	Mat frame, mask, back_img;
	while (true) {
		bool ret = capture.read(frame);
		if (!ret) break;
		pMOG2->apply(frame, mask);
		pMOG2->getBackgroundImage(back_img);
		imshow("input", frame);
		imshow("mask", mask);
		imshow("back ground image", back_img);
		char c = waitKey(5);
		if (c == 27) {
			break;
		}
	}

	waitKey(0);
	destroyAllWindows();

	return 0;
}