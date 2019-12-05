/*
图像形态学 – 闭操作
形态学的闭操作跟开操作一样也是基于腐蚀与膨胀两个操作的组合实现的
闭操作 = 膨胀 + 腐蚀
闭操作的作用：
闭操作可以填充二值图像中孔洞区域，形成完整的闭合区域连通组件
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

其中op指定为MORPH_CLOSE 即表示使用闭操作
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

	// 定义结构元素 5x5大小矩形
	Mat se1 = getStructuringElement(MORPH_RECT, Size(25, 5), Point(-1, -1));
	Mat se2 = getStructuringElement(MORPH_RECT, Size(5, 25), Point(-1, -1));
	morphologyEx(binary, result, MORPH_CLOSE, se1);
	morphologyEx(result, result, MORPH_CLOSE, se2);

	// 显示
	imshow("open demo", result);
	waitKey(0);
	destroyAllWindows();

	return 0;
}