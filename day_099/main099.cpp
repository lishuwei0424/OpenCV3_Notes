/*
SIFT特征提取 – 描述子生成

SIFT特征提取是图像特征提取中最经典的一个算法，归纳起来SIFT特征提取主要有如下几步：
-	构建高斯多尺度金字塔
-	关键点查找/过滤与精准定位
-	窗口区域角度方向直方图
-	描述子生成
前面我们已经详细解释了SIFT特征点是如何提取的，有了特征点之后，我们对特征点周围的像素块计算角度方向直方图，在计算直方图之前首先需要对图像进行梯度计算，这里可以使用SOBEL算子，然后根据dx与dy计算梯度和与角度

PS: SIFT特征分享结束！
*/

#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void find_known_object(Mat &box, Mat &box_scene);
int main(int argc, char** argv) {

	Mat box = imread("../data/box.bmp");
	Mat scene = imread("../data/scene.jpg");
	imshow("box image", box);
	imshow("scene image", scene);
	find_known_object(box, scene);

	//Mat gray;
	//cvtColor(src, gray, COLOR_BGR2GRAY);
	auto detector =cv::SIFT::create();
	vector<KeyPoint> keypoints_box, keypoints_scene;
	Mat descriptor_box, descriptor_scene;
	detector->detectAndCompute(box, Mat(), keypoints_box, descriptor_box);
	detector->detectAndCompute(scene, Mat(), keypoints_scene, descriptor_scene);

	Ptr<FlannBasedMatcher> matcher = FlannBasedMatcher::create();
	vector<DMatch> matches;
	matcher->match(descriptor_box, descriptor_scene, matches);
	Mat dst;
	drawMatches(box, keypoints_box, scene, keypoints_scene, matches, dst);
	imshow("match-demo", dst);


	waitKey(0);
	destroyAllWindows();

	return 0;
}
