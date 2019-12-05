/*
视频分析 – 基于连续自适应均值迁移（CAM）的对象移动分析
CAM是连续自适应的均值迁移跟踪算法，它跟均值迁移相比较有两个改进
-	会根据跟踪对象大小变化自动调整搜索窗口大小
-	返回位置信息更加完整，包含了位置与角度信息
OpenCV中CAMShift的API函数如下：
RotatedRect cv::CamShift(
	InputArray probImage,
	Rect & 	window,
	TermCriteria criteria
)
probImage输入图像，是直方图反向投影的结果
window 搜索窗口，ROI对象区域
criteria 均值迁移停止条件

特别需要注意的是：
C++版本中会自动更新搜索窗口，
Python语言版本中必须每次从返回信息中手动更新
*/

#include <opencv2/opencv.hpp>"
#include <iostream>
#include <ctype.h>

using namespace cv;
using namespace std;

Mat image;
bool selectObject = false;
int trackObject = 0;
bool showHist = true;
Point origin;
Rect selection;
int vmin = 10, vmax = 256, smin = 30;

int main(int argc, const char** argv)
{
	// VideoCapture cap(0);
	VideoCapture cap("../images/balltest.mp4");
	Rect trackWindow;
	int hsize = 16;
	float hranges[] = { 0,180 };
	const float* phranges = hranges;

	if (!cap.isOpened())
	{
		printf("could not open camera...\n");
		return -1;
	}

	namedWindow("Histogram", WINDOW_AUTOSIZE);
	namedWindow("CamShift Demo", WINDOW_AUTOSIZE);

	Mat frame, hsv, hue, mask, hist, histimg = Mat::zeros(200, 320, CV_8UC3), backproj;
	bool paused = false;
	cap.read(frame);
	Rect selection = selectROI("CamShift Demo", frame, true, false);

	while (true)
	{
		bool ret = cap.read(frame);
		if (!ret) break;
		frame.copyTo(image);

		cvtColor(image, hsv, COLOR_BGR2HSV);

		int _vmin = vmin, _vmax = vmax;
		inRange(hsv, Scalar(26, 43, 46), Scalar(34, 255, 255), mask);
		int ch[] = { 0, 0 };
		hue.create(hsv.size(), hsv.depth());
		mixChannels(&hsv, 1, &hue, 1, ch, 1);

		if (trackObject <= 0)
		{
			// Object has been selected by user, set up CAMShift search properties once
			Mat roi(hue, selection), maskroi(mask, selection);
			calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
			normalize(hist, hist, 0, 255, NORM_MINMAX);

			trackWindow = selection;
			trackObject = 1; // Don't set up again, unless user selects new ROI

			histimg = Scalar::all(0);
			int binW = histimg.cols / hsize;
			Mat buf(1, hsize, CV_8UC3);
			for (int i = 0; i < hsize; i++)
				buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180. / hsize), 255, 255);
			cvtColor(buf, buf, COLOR_HSV2BGR);

			for (int i = 0; i < hsize; i++)
			{
				int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows / 255);
				rectangle(histimg, Point(i*binW, histimg.rows),
					Point((i + 1)*binW, histimg.rows - val),
					Scalar(buf.at<Vec3b>(i)), -1, 8);
			}
		}

		// Perform CA-MeanShift
		calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
		backproj &= mask;
		RotatedRect trackBox = CamShift(backproj, trackWindow,
			TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 10, 1));

		ellipse(image, trackBox, Scalar(0, 0, 255), 3, LINE_AA);

		imshow("CamShift Demo", image);
		imshow("Histogram", histimg);
		char c = (char)waitKey(50);
		if (c == 27)
			break;
	}

	destroyAllWindows();
	return 0;
}
