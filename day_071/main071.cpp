/*
形态学操作 – 击中击不中

形态学的击中击不中操作，根据结构元素不同，可以提取二值图像中的一些特殊区域，得到我们想要的结果。击中击不中操作的API也是我们前面一直用的API，只是对OP参数的修改
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
其中op指定为MORPH_HITMISS即表示使用击中击不中
*/

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat dresult, eresult;
	Mat src = imread("../images/cross.png");

	// 二值图像
	Mat gray, binary, result;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	imshow("binary", binary);

	// 定义结构元素
	Mat se = getStructuringElement(MORPH_CROSS, Size(11, 11), Point(-1, -1));
	// 击中击不中
	morphologyEx(binary, result, MORPH_HITMISS, se);

	// 显示
	imshow("hit-and-miss demo", result);
	waitKey(0);
	destroyAllWindows();

	return 0;
}