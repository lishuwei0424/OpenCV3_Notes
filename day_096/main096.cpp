/*
描述子匹配

图像特征检测首先会获取关键点，然后根据关键点周围像素ROI区域的大小，生成描述子，完整的描述子向量就表示了一张图像的特征，
是图像特征数据，这种方式也被称为图像特征工程，即通过先验模型与合理计算得到图像特征数据的过程，有了特征数据我们就可以利
用特征数据实现对象检测与对象识别，这个最简单一个方法就是特征匹配，OPenCV提供了两种图像特征匹配的算法
-	暴力匹配
-	FLANN匹配
其中FLANN是一种高效的数值或者字符串匹配算法，SIFT/SURF是基于浮点数的匹配，ORB是二值匹配，速度更快。对于FLANN匹配算法，
当使用ORB匹配算法的时候，需要重新构造HASH。这个在C++的代码种做了演示。暴力匹配在Python代码种做了演示。对匹配之后的输出
结果，根据距离进行排序，就会得到距离比较的匹配点，这个才是好的特征匹配。
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#define RATIO    0.4
using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat box = imread("../data/box.png");
	Mat scene = imread("../data/box_in_scene.png");
	if (scene.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	imshow("input image", scene);
	vector<KeyPoint> keypoints_obj, keypoints_sence;
	Mat descriptors_box, descriptors_sence;
	Ptr<ORB> detector = ORB::create();
	detector->detectAndCompute(scene, Mat(), keypoints_sence, descriptors_sence);
	detector->detectAndCompute(box, Mat(), keypoints_obj, descriptors_box);

	vector<DMatch> matches;
	// ³õÊ¼»¯flannÆ¥Åä
	// Ptr<FlannBasedMatcher> matcher = FlannBasedMatcher::create(); // default is bad, using local sensitive hash(LSH)
	Ptr<DescriptorMatcher> matcher = makePtr<FlannBasedMatcher>(makePtr<flann::LshIndexParams>(12, 20, 2));
	matcher->match(descriptors_box, descriptors_sence, matches);

	// ·¢ÏÖÆ¥Åä
	vector<DMatch> goodMatches;
	printf("total match points : %d\n", matches.size());
	float maxdist = 0;
	for (unsigned int i = 0; i < matches.size(); ++i) {
		printf("dist : %.2f \n", matches[i].distance);
		maxdist = max(maxdist, matches[i].distance);
	}
	for (unsigned int i = 0; i < matches.size(); ++i) {
		if (matches[i].distance < maxdist*RATIO)
			goodMatches.push_back(matches[i]);
	}

	Mat dst;
	drawMatches(box, keypoints_obj, scene, keypoints_sence, goodMatches, dst);
	imshow("output", dst);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
