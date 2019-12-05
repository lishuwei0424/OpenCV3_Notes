/*
ORB FAST特征关键点检测

ORB - (Oriented Fast and Rotated BRIEF)算法是基于FAST特征检测与BRIEF特征描述子匹配实现，相比BRIEF算法中依靠随机方式获取而值点对，ORB通过FAST方法，FAST方式寻找候选特征点方式是假设灰度图像像素点A周围的像素存在连续大于或者小于A的灰度值，选择任意一个像素点P，假设半径为3，周围16个像素表示
见图一！

则像素点P被标记为候选特征点、通常N取值为9、12，上图N=9。
为了简化计算，我们可以只计算1、9、5、13四个点，至少其中三个点满足上述不等式条件，即可将P视为候选点。然后通过阈值进行最终的筛选即可得到ORB特征点

static Ptr&lt;ORB&gt; cv::ORB::create	(
	int nfeatures = 500,
	float scaleFactor = 1.2f,
	int nlevels = 8,
	int edgeThreshold = 31,
	int firstLevel = 0,
	int WTA_K = 2,
	ORB::ScoreType 	scoreType = ORB::HARRIS_SCORE,
	int patchSize = 31,
	int fastThreshold = 20
)
nfeatures 最终输出最大特征点数目
scaleFactor 金字塔上采样比率
nlevels 金字塔层数
edgeThreshold 边缘阈值
firstLevel= 0
WTA_K这个是跟BRIEF描述子用的
scoreType 对所有的特征点进行排名用的方法
*/


#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("../images/blob.png");
	auto orb_detector = ORB::create(1000);
	vector<KeyPoint> kpts;
	orb_detector->detect(src, kpts);
	Mat result = src.clone();
	drawKeypoints(src, kpts, result, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	imshow("ORB-detector", result);
	imwrite("../result.png", result);
	waitKey(0);
	destroyAllWindows();

	return 0;
}
