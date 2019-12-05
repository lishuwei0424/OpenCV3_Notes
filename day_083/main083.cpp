/*
角点检测 – 亚像素级别角点检测
OpenCV中角点检测的结果实际不够精准，因为真实的计算中有些位置可能是在浮点数的空间内才最大值，这样就需要我们通过给定的响应值，在像素邻域空间进行拟合，实现亚像素级别的角点检测。OpenCV中相关API与解释如下：
void cv::cornerSubPix(
	InputArray image,
	InputOutputArray corners,
	Size winSize,
	Size zeroZone,
	TermCriteria criteria
)
image单通道输入图像，八位或者浮点数
corners是输入输出的关键点坐标集合
winSize表示插值计算时候窗口大小
zeroZone表示搜索区域中间的dead region边长的一半，有时用于避免自相关矩阵的奇异性。如果值设为(-1,-1)则表示没有这个区域。
criteria角点精准化迭代过程的终止条件
*/

#include <opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;
void process_frame(Mat &image, int opts);
RNG rng(12345);
int main(int argc, char** argv) {
	VideoCapture capture("../images/video.avi");

	if (!capture.isOpened()) {
		printf("could not open camera...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	namedWindow("result", WINDOW_AUTOSIZE);

	int fps = capture.get(CAP_PROP_FPS);
	int width = capture.get(CAP_PROP_FRAME_WIDTH);
	int height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int num_of_frames = capture.get(CAP_PROP_FRAME_COUNT);
	printf("frame width: %d, frame height: %d, FPS : %d \n", width, height, fps);

	Mat frame;
	while (true) {
		bool ret = capture.read(frame);
		imshow("input", frame);
		if (!ret) break;

		process_frame(frame, 0);
		imshow("result", frame);
		char c = waitKey(5);
		if (c == 27) {
			break;
		}
	}

	waitKey(0);
	destroyAllWindows();

	return 0;
}


void process_frame(Mat &image, int opts) {
	// Detector parameters
	int maxCorners = 100;
	double quality_level = 0.01;
	double minDistance = 10;

	// Detecting corners
	Mat gray, dst;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	vector<Point2f> corners;
	goodFeaturesToTrack(gray, corners, maxCorners, quality_level, minDistance, Mat(), 3, false);
	for (int i = 0; i < corners.size(); i++) {
		int b = rng.uniform(0, 256);
		int g = rng.uniform(0, 256);
		int r = rng.uniform(0, 256);
		circle(image, corners[i], 5, Scalar(b, g, r), 3, 8, 0);
	}

	// ÑÇÏñËØ¼¶±ð¼ì²â
	Size winSize = Size(5, 5);
	Size zeroZone = Size(-1, -1);
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 40, 0.001);
	cornerSubPix(gray, corners, winSize, zeroZone, criteria);
	for (size_t i = 0; i < corners.size(); i++)
	{
		cout << " -- Refined Corner [" << i << "]  (" << corners[i].x << "," << corners[i].y << ")" << endl;
	}
}
