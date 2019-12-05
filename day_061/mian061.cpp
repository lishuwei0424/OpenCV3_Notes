/*
二值图像分析 – 霍夫圆检测
根据极坐标,圆上任意一点的坐标可以表示为如上形式, 所以对于任意一个圆, 假设中心像素点p(x0, y0)像素点已知, 圆半径已知,则旋转360由极坐标方程可以得到每个点上得坐标同样,如果只是知道图像上像素点, 圆半径,旋转360°则中心点处的坐标值必定最强.这正是霍夫变换检测圆的数学原理
X = x0+rcos(theta)
Y = y0+rsin(theta)

OpenCV中霍夫圆检测的API与参数解释如下：
void cv::HoughCircles(
	InputArray image,
	OutputArray circles,
	int method,
	double dp,
	double minDist,
	double param1 = 100,
	double param2 = 100,
	int minRadius = 0,
	int maxRadius = 0
)
image表示输入单通道的灰度图像
circles 表示检测的圆信息（圆心+半径）
method 圆检测的方法
dp表示图像分辨率是否有变化，默认1表示保持跟原图大小一致
minDist表示检测到的圆，两个圆心之间的最小距离
param1 表示边缘提取的高阈值
param2表示霍夫空间的累加阈值
minRadius 表示可以检测圆的最小半径
maxRadius 表示可以检测圆的最大
*/

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat gray;
	int dp = 2; // 在其它参数保持不变的情况下。dp的取值越高，越容易检测到圆，
	int min_radius = 20;
	int max_radius = 100;
	int minDist = 10;
	Mat src = imread("../images/coins.jpg");
	imshow("input", src);
	cvtColor(src, gray, COLOR_BGR2GRAY);
	GaussianBlur(gray, gray, Size(9, 9), 2, 2);
	vector<Vec3f> circles;
	HoughCircles(gray, circles, HOUGH_GRADIENT, dp, minDist, 100, 100, min_radius, max_radius);
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// 绘制圆
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		circle(src, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	}
	namedWindow("circles", 1);
	imshow("circles", src);
	waitKey(0);

	destroyAllWindows();
	return 0;
}