/*
SIFT������ȡ �C ����������

SIFT������ȡ��ͼ��������ȡ������һ���㷨����������SIFT������ȡ��Ҫ�����¼�����
-	������˹��߶Ƚ�����
-	�ؼ������/�����뾫׼��λ
-	��������Ƕȷ���ֱ��ͼ
-	����������
ǰ�������Ѿ���ϸ������SIFT�������������ȡ�ģ�����������֮�����Ƕ���������Χ�����ؿ����Ƕȷ���ֱ��ͼ���ڼ���ֱ��ͼ֮ǰ������Ҫ��ͼ������ݶȼ��㣬�������ʹ��SOBEL���ӣ�Ȼ�����dx��dy�����ݶȺ���Ƕ�

PS: SIFT�������������
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
