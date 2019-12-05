#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main(int argc,char** argv)
{
	//读文件
	//VideoCapture capture;
	//capture.open("../data/vtest.avi");

	VideoCapture capture(1);

	if (!capture.isOpened())
	{
		printf("视频无法打开\n");
		return -1;
	}

	Size S = Size((int)capture.get(CAP_PROP_FRAME_WIDTH),
		(int)capture.get(CAP_PROP_FRAME_HEIGHT));

	int fps = capture.get(CAP_PROP_FPS);

	printf("current fps : %d \n", fps);
	VideoWriter writer("../test.mp4",-1, fps, S, true);
	Mat frame;
	while (capture.read(frame)) {
		imshow("current", frame);
		writer.write(frame);
		char ch =waitKey();
		if (ch == 'q')
		{
			break;
		}	
	}

	capture.release();
	writer.release();
	waitKey();
	destroyAllWindows();
	return 1;
}