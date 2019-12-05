/*
��Ƶ���� �C ����֡�ʵ���ƶ��������

���������뱳���������ǻ��ڽ�ģ��ʽ����Ƶ������������ʵ���෽����ԭʼ��һ�����Ӿ��Ƕ���Ƶ�ƶ������֡����٣��������Ƶ�����봦����Ҳ��һ�ֺܳ������ֶΣ���ʱ���ȡ�����벻���ĺ�Ч����֡���һ�������п��Է�Ϊ
-	��֡��
-	��֡��
�����е�ǰ֡frame�� ǰһ֡prev1����ǰһ֡prev2
��֡���ֱ��ʹ��ǰһ֡ ��ȥ��ǰ֡ diff = frame �C prev1
��֡����������£�
diff1 = prev2 �C prev1
diff2 = frame �C prev1
diff = diff1 & diff2
֡�����ȡ֡��֮ǰһ�����и�˹ģ�������Լ��͸��ţ�ͨ���õ���diffͼ�������̬ѧ���������Ժϲ����ѡ��������Ч�ʡ�֡���ȱ�������£�
1.	��˹ģ���Ǹߺ�ʱ����
2.	�����ܵ���������߸���

PS:����е����˵�ɹ������ش˸�����
ף����µ�һ�ܹ�����죡õ��
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


		// �������������
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
		for (size_t t = 0; t < contours.size(); t++) {
			// ����������
			cv::Rect rect = boundingRect(contours[t]);
			rectangle(src, rect, Scalar(0, 0, 255), 1, 8, 0);

			// ��С�������
			RotatedRect rrt = minAreaRect(contours[t]);
			Point2f pts[4];
			rrt.points(pts);

			// ������ת����������λ��
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
