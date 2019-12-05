/*
BRIEF特征描述子 匹配
得到特征点数据之后，根据BRIEF算法就可以建立描述子。选择候选特征点周围SxS大小的像素块、随机选择n对像素点。
其中P(x)是图像模糊处理之后的像素值，原因在于高斯模糊可以抑制噪声影响、提供特征点稳定性，在实际代码实现中
通常用均值滤波替代高斯滤波以便利用积分图方式加速计算获得更好的性能表现。常见滤波时候使用3x3~9x9之间的卷积核。
滤波之后，根据上述描述子的生成条件，得到描述子。

作者论文提到n的取值通常为128、256或者512。得到二进制方式的字符串描述子之后，匹配就可以通过XOR方式矩形，计
算汉明距离。ORB特征提取跟纯BRIEF特征提取相比较，BRIEF方式采用随机点方式得最终描述子、而ORB通过FAST得到特征点然后得到描述子。

*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat box = imread("../data/box.png");
	Mat box_in_sence = imread("../data/box_in_scene.png");

	// 创建ORB
	auto orb_detector = ORB::create();
	vector<KeyPoint> kpts_01, kpts_02;
	Mat descriptors1, descriptors2;
	orb_detector->detectAndCompute(box, Mat(), kpts_01, descriptors1);
	orb_detector->detectAndCompute(box_in_sence, Mat(), kpts_02, descriptors2);

	// 定义描述子匹配 - 暴力匹配
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
	std::vector< DMatch > matches;
	matcher->match(descriptors1, descriptors2, matches);

	// 绘制匹配
	Mat img_matches;
	drawMatches(box, kpts_01, box_in_sence, kpts_02, matches, img_matches);
	imshow("ORB-Matches", img_matches);
	imwrite("D:/result.png", img_matches);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
