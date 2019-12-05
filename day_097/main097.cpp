/*
基于描述子匹配的已知对象定位

图像特征点检测、描述子生成以后，就可以通过OpenCV提供的描述子匹配算法，得到描述子直接的距离，距离越小的说明是匹配越好的，
设定一个距离阈值，一般是最大匹配距离的1/5～1/4左右作为阈值，得到所有小于阈值的匹配点，作为输入，通过单应性矩阵，获得这两
个点所在平面的变换关系H，根据H使用透视变换就可以根据输入的对象图像获得场景图像中对象位置，最终绘制位置即可。

PS: 祝大家元旦快乐，欢迎分享！
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
	// 初始化flann匹配
	// Ptr<FlannBasedMatcher> matcher = FlannBasedMatcher::create(); // default is bad, using local sensitive hash(LSH)
	Ptr<DescriptorMatcher> matcher = makePtr<FlannBasedMatcher>(makePtr<flann::LshIndexParams>(12, 20, 2));
	matcher->match(descriptors_box, descriptors_sence, matches);

	// 发现匹配
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

	//-- Localize the object
	std::vector<Point2f> obj_pts;
	std::vector<Point2f> scene_pts;
	for (size_t i = 0; i < goodMatches.size(); i++)
	{
		//-- Get the keypoints from the good matches
		obj_pts.push_back(keypoints_obj[goodMatches[i].queryIdx].pt);
		scene_pts.push_back(keypoints_sence[goodMatches[i].trainIdx].pt);
	}
	Mat H = findHomography(obj_pts, scene_pts, RHO);
	// 无法配准
	// Mat H = findHomography(obj, scene, RANSAC);

	//-- Get the corners from the image_1 ( the object to be "detected" )
	std::vector<Point2f> obj_corners(4);
	obj_corners[0] = Point(0, 0); obj_corners[1] = Point(box.cols, 0);
	obj_corners[2] = Point(box.cols, box.rows); obj_corners[3] = Point(0, box.rows);
	std::vector<Point2f> scene_corners(4);
	perspectiveTransform(obj_corners, scene_corners, H);

	//-- Draw lines between the corners (the mapped object in the scene - image_2 )
	line(dst, scene_corners[0] + Point2f(box.cols, 0), scene_corners[1] + Point2f(box.cols, 0), Scalar(0, 255, 0), 4);
	line(dst, scene_corners[1] + Point2f(box.cols, 0), scene_corners[2] + Point2f(box.cols, 0), Scalar(0, 255, 0), 4);
	line(dst, scene_corners[2] + Point2f(box.cols, 0), scene_corners[3] + Point2f(box.cols, 0), Scalar(0, 255, 0), 4);
	line(dst, scene_corners[3] + Point2f(box.cols, 0), scene_corners[0] + Point2f(box.cols, 0), Scalar(0, 255, 0), 4);

	//-- Show detected matches
	imshow("Good Matches & Object detection", dst);
	imwrite("D:/result.png", dst);
	waitKey(0);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
