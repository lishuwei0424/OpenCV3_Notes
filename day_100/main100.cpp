/*
HOG特征与行人检测

HOG(Histogram of Oriented Gradient)特征在对象识别与模式匹配中是一种常见的特征提取算法，是基于本地像素块进行特征直方图提取的一种算法，
对象局部的变形与光照影响有很好的稳定性，最初是用HOG特征来来识别人像，通过HOG特征提取+SVM训练，可以得到很好的效果，OpenCV已经有了。HOG
特征提取的大致流程看第一张图

PS：今天是第100课时，感谢大家支持！
坚持分享200+课时！
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("../images/pedestrian.png");
	if (src.empty()) {
		printf("could not load image..\n");
		return -1;
	}
	imshow("input", src);
	HOGDescriptor *hog = new HOGDescriptor();
	hog->setSVMDetector(hog->getDefaultPeopleDetector());
	vector<Rect> objects;
	hog->detectMultiScale(src, objects, 0.0, Size(4, 4), Size(8, 8), 1.25);
	for (int i = 0; i < objects.size(); i++) {
		rectangle(src, objects[i], Scalar(0, 0, 255), 2, 8, 0);
	}
	imshow("result", src);
	waitKey(0);
	destroyAllWindows();

	return 0;
}