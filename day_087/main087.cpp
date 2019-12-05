/*
视频分析 – 基于帧差法实现移动对象分析

光流跟踪与背景消除都是基于建模方式的视频分析方法，其实这类方法最原始的一个例子就是对视频移动对象的帧差法跟踪，这个在视频分析与处理中也是一种很常见的手段，有时候会取得意想不到的好效果，帧差法进一步划分有可以分为
-	两帧差
-	三帧差
假设有当前帧frame， 前一帧prev1，更前一帧prev2
两帧差方法直接使用前一帧 减去当前帧 diff = frame – prev1
三帧差方法计算如下：
diff1 = prev2 – prev1
diff2 = frame – prev1
diff = diff1 & diff2
帧差法在求取帧差之前一般会进行高斯模糊，用以减低干扰，通过得到的diff图像进行形态学操作，用以合并与候选区域，提升效率。帧差法的缺点有如下：
1.	高斯模糊是高耗时计算
2.	容易受到噪声与光线干扰

PS:最后有点口误，说成光流，特此更正！
祝大家新的一周工作愉快！玫瑰
*/

#include <opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;
RNG rng(12345);
int main(int argc, char** argv) {
	VideoCapture capture("../images/bike.avi");

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
	Mat preFrame, preGray;
	capture.read(preFrame);
	cvtColor(preFrame, preGray, COLOR_BGR2GRAY);
	GaussianBlur(preGray, preGray, Size(0, 0), 15);
	Mat binary;
	Mat frame, gray;
	Mat k = getStructuringElement(MORPH_RECT, Size(7, 7), Point(-1, -1));
	while (true) {
		bool ret = capture.read(frame);
		if (!ret) break;
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		GaussianBlur(gray, gray, Size(0, 0), 15);
		subtract(gray, preGray, binary);
		threshold(binary, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
		morphologyEx(binary, binary, MORPH_OPEN, k);
		imshow("input", frame);


		// 轮廓发现与绘制
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
		for (size_t t = 0; t < contours.size(); t++) {
			// 最大外接轮廓
			cv::Rect rect = boundingRect(contours[t]);
			rectangle(src, rect, Scalar(0, 0, 255), 1, 8, 0);

			// 最小外接轮廓
			RotatedRect rrt = minAreaRect(contours[t]);
			Point2f pts[4];
			rrt.points(pts);

			// 绘制旋转矩形与中心位置
			for (int i = 0; i < 4; i++) {
				line(src, pts[i % 4], pts[(i + 1) % 4], Scalar(0, 255, 0), 2, 8, 0);
			}

			Point2f cpt = rrt.center;
			circle(src, cpt, 2, Scalar(255, 0, 0), 2, 8, 0);
		}

		imshow("contours", src);


		imshow("result", binary);

		gray.copyTo(preGray);
		char c = waitKey(5);
		if (c == 27) {
			break;
		}
	}

	waitKey(0);
	destroyAllWindows();

	return 0;
}
