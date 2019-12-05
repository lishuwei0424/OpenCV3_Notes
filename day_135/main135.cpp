/*
OpenCV DNN ʵʱ���ٵ�ͼ����Ǩ��

OpenCV DNNģ�����ڻ�֧��ͼ����Ǩ������ģ�͵ļ�����ʹ�ã�֧�ֵ�ģ���ǻ�����ɷɵ��������ġ�Perceptual Losses for Real-Time Style Transfer and Super-Resolution�����ᵽ�Ŀ���ͼ����Ǩ�����磬���ڸ�֪��ʧ����ȡ����������ͼ��������߷ֱ���ͼ����������ģ���ǻ���DCGAN + 5���в�㹹�ɣ���һ�����͵�ȫ������磬����DCGAN���Կ���������ϸ���������ʵ�֣�
ʹ��DCGANʵ��ͼ������

ģ�����ص�ַ
GitHub - jcjohnson/fast-neural-style: Feedforward ...

����������֧������ߴ��ͼ�����룬�����ṩ�˺ܶ���Ԥѵ���ķ��Ǩ��ģ���ṩʹ�ã��������������Ԥѵ��ģ�͡���
composition_vii.t7
starry_night.t7
la_muse.t7
the_wave.t7
mosaic.t7
the_scream.t7
feathers.t7
candy.t7
udnie.t7
��Щģ�Ͷ���torch���֧�ֵĶ�����Ȩ���ļ�������ģ��֮�󣬾Ϳ��Ե���forward�õ������ͨ����������������Ͼ�ֵ��rescale��0~255��RGBɫ�ʿռ䣬������ʾ��
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

		// ���Ͻ�����
		printf("channels : %d, height: %d, width: %d \n", ch, h, w);
		add(result, Scalar(103.939, 116.779, 123.68), result);
		result /= 255.0;

		// ��ֵ�˲�
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