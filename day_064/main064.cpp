/*
图像形态学 – 开操作
形态学的开操作是基于腐蚀与膨胀两个操作的组合实现的
开操作 = 腐蚀 + 膨胀
开操作的作用：
开操作可以删除二值图像中小的干扰块，降低图像二值化之后噪点过多的问题，

void cv::morphologyEx(
	InputArray src,
	OutputArray dst,
	int op,
	InputArray kernel,
	Point anchor = Point(-1,-1),
	int iterations = 1,
	int borderType = BORDER_CONSTANT,
)

src 输入图像
dst 输出图像
op 形态学操作
kernel 结构元素
anchor 中心位置锚定
iterations 循环次数
borderType 边缘填充类型

其中op指定为MORPH_OPEN 即表示使用开操作
*/

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat dresult, eresult;
	Mat src = imread("../images/shuini.jpg");

	// 二值图像
	Mat gray, binary, result;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	GaussianBlur(gray, gray, Size(9, 9), 0, 0);
	adaptiveThreshold(gray, binary, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 45, 15);
	imshow("binary", binary);

	// 定义结构元素 5x5大小矩形
	Mat se = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
	morphologyEx(binary, result, MORPH_OPEN, se);

	// 显示
	imshow("open demo", result);
	waitKey(0);
	destroyAllWindows();

	return 0;
}