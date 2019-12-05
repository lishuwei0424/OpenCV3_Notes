/*
图像形态学 – 顶帽操作
形态学的顶帽操作是图像输入与开操作之间的差异，顶帽操作有时候对于我们提取图像中微小部分特别有用，顶帽操作：
顶帽 = 原图 – 开操作
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
其中op指定为MORPH_TOPHAT 即表示使用顶帽操作
*/

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat dresult, eresult;
	Mat src = imread("../images/cells.png");

	// 二值图像
	Mat gray, binary, result;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary", binary);

	// 定义结构元素
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(binary, result, MORPH_TOPHAT, se);

	// 显示
	imshow("tophat demo", result);
	waitKey(0);
	destroyAllWindows();

	return 0;
}