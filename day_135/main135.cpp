/*
OpenCV DNN 实时快速的图像风格迁移

OpenCV DNN模块现在还支持图像风格迁移网络模型的加载与使用，支持的模型是基于李飞飞等人在论文《Perceptual Losses for Real-Time Style Transfer and Super-Resolution》中提到的快速图像风格迁移网络，基于感知损失来提取特征，生成图像特征与高分辨率图像。整个网络模型是基于DCGAN + 5个残差层构成，是一个典型的全卷积网络，关于DCGAN可以看这里有详细介绍与代码实现：
使用DCGAN实现图像生成

模型下载地址
GitHub - jcjohnson/fast-neural-style: Feedforward ...

这个网络可以支持任意尺寸的图像输入，作者提供了很多种预训练的风格迁移模型提供使用，我下载了下面的预训练模型。：
composition_vii.t7
starry_night.t7
la_muse.t7
the_wave.t7
mosaic.t7
the_scream.t7
feathers.t7
candy.t7
udnie.t7
这些模型都是torch框架支持的二进制权重文件，加载模型之后，就可以调用forward得到结果，通过对输出结果反向加上均值，rescale到0~255的RGB色彩空间，即可显示。
*/

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>

using namespace cv;
using namespace cv::dnn;
using namespace std;

const size_t width = 256;
const size_t height = 256;
String base_dir = "../models/fast_style/";
String styles[9] = { "composition_vii.t7", "starry_night.t7", "la_muse.t7", "the_wave.t7",
"mosaic.t7", "the_scream.t7", "feathers.t7", "candy.t7", "udnie.t7" };

int main(int argc, char** argv) {
	int index = 0;
	VideoCapture capture = VideoCapture(0);
	Net net = readNetFromTorch(format("%s%s", base_dir.c_str(), styles[index].c_str()));
	net.setPreferableBackend(DNN_BACKEND_INFERENCE_ENGINE);
	net.setPreferableTarget(DNN_TARGET_CPU);
	Mat frame;
	while (true) {
		capture.read(frame);
		imshow("input", frame);
		Mat blobImage = blobFromImage(frame, 1.0,
			Size(width, height),
			Scalar(103.939, 116.779, 123.68), false, false);

		net.setInput(blobImage);
		Mat out = net.forward();
		vector<double> layersTimings;
		double freq = getTickFrequency() / 1000;
		double time = net.getPerfProfile(layersTimings) / freq;
		printf("execute time : %.2f ms\n", time);
		int ch = out.size[1];
		int h = out.size[2];
		int w = out.size[3];
		Mat result = Mat::zeros(Size(w, h), CV_32FC3);
		float* data = out.ptr<float>();

		// decode 4-d Mat object
		for (int c = 0; c < ch; c++) {
			for (int row = 0; row < h; row++) {
				for (int col = 0; col < w; col++) {
					result.at<Vec3f>(row, col)[c] = *data++;
				}
			}
		}

		// 整合结果输出
		printf("channels : %d, height: %d, width: %d \n", ch, h, w);
		add(result, Scalar(103.939, 116.779, 123.68), result);
		result /= 255.0;

		// 中值滤波
		medianBlur(result, result, 5);
		Mat dst;
		resize(result, dst, frame.size());
		imshow("styled-video", dst);

		// ESC means exit
		char c = waitKey(1);
		if (c == 27) {
			break;
		}
	}

	waitKey(0);
	destroyAllWindows();

	return 0;
}