/*
图像形态学 - 膨胀与腐蚀

膨胀与腐蚀是图像形态学最基础的两个操作，形态学的其它操作都是基于这两个操作基础上得到的，图像形态学是二值图像分析的重要分支学科。在OpenCV中膨胀与腐蚀对应两个相关的API，膨胀可以看成是最大值滤波，即用最大值替换中心像素点；腐蚀可以看出是最小值滤波，即用最小值替换中心像素点。

膨胀的API如下：

void cv::dilate(
InputArray src,
OutputArray dst,
InputArray kernel,
Point anchor = Point(-1,-1),
int iterations = 1,
int borderType = BORDER_CONSTANT,
const Scalar & borderValue = morphologyDefaultBorderValue()
)

src 输入图像，任意通道的
dst 输出图像，类型与通道数目必须跟输入保持一致
kernel 结构元素
anchor 中心位置锚定
iterations 循环次数
borderType 边缘填充类型


腐蚀的API如下：

void cv::erode(
InputArray src,
OutputArray dst,
InputArray kernel,
Point anchor = Point(-1,-1),
int iterations = 1,
int borderType = BORDER_CONSTANT,
const Scalar & borderValue = morphologyDefaultBorderValue()
)
src 输入图像，任意通道的
dst 输出图像，类型与通道数目必须跟输入保持一致
kernel 结构元素
anchor 中心位置锚定
iterations 循环次数
borderType 边缘填充类型

PS: 最近提问的比较多，我每天会走一遍知识星球所有问题，保证让大家的问题不过当天得到回复！感谢大家理解！
*/

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat dresult, eresult;
	Mat src = imread("../images/coins.jpg");
	imshow("input", src);
	// 定义结构元素 3x3大小矩形
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	// 膨胀
	dilate(src, dresult, se, Point(-1, -1), 1, 0);
	// 腐蚀
	erode(src, eresult, se, Point(-1, -1), 1, 0);

	// 显示
	imshow("dilate", dresult);
	imshow("erode", eresult);
	waitKey(0);
	destroyAllWindows();

	return 0;
}