/*
图像形态学 – 图像梯度
图像形态学的梯度跟我们前面介绍的图像卷积计算出来的梯度有本质不同，形态学梯度可以帮助我们获得连通组件的边缘与轮廓，实现图像轮廓或者边缘提取。根据使用的形态学操作不同，形态学梯度又分为
-	基本梯度
-	内梯度
-	外梯度
基本梯度是图像膨胀与腐蚀操作之间的差值
内梯度是输入图像与腐蚀之间的差值
外梯度是膨胀与输入图像之间的差值
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
其中op指定为MORPH_GRADIEN即表示使用基本梯度操作
*/

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat basic, exter, inter;
	Mat src = imread("../images/cells.png");
	imshow("input", src);

	// 定义结构元素
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));

	// 基本梯度
	morphologyEx(src, basic, MORPH_GRADIENT, se);
	imshow("basic gradient", basic);

	// 外梯度
	morphologyEx(src, exter, MORPH_DILATE, se);
	subtract(exter, src, exter);
	imshow("external gradient", exter);

	// 内梯度
	morphologyEx(src, inter, MORPH_ERODE, se);
	subtract(src, inter, inter);
	imshow("internal gradient", inter);

	waitKey(0);
	destroyAllWindows();

	return 0;
}