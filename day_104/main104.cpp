/*
对于得到的结构化HOG特征数据，我们就可以通过初始化SVM进行回归分类训练，这里采用的训练器是SVM线性分类器，SVM还有另外一个分类器就是对于线性不可分数据的径向分类器。
OpenCV中使用径向分类器SVM有时候会训练很长时间，而且结果很糟糕，甚至会报一些莫名其妙的错误，感觉不是特别好。所以推荐大家真对线性不可分的问题可以选择神经网络ANN模块。

在训练之前，首先简单的认识一下SVM，我们这边是通过二分类来完成，是很典型的线性可分离的SVM。


对线性可分的选择用SVM，通过很少的样本学习就会取得很好的效果。OpenCV中SVM训练的API如下：
virtual bool cv::ml::StatModel::train(
	InputArray 	samples,
	int layout,
	InputArray 	responses
)
Sample表示训练样本数据/HOG特征数据
Layout 有两种组织方式ROW_SAMPLE与COL_SAMPLE
Responses 每个输入样本的标签

对于训练好的数据我们可以通过save方法进行保存，只要提供一个保存路径即可。
相关数据文件：
GitHub - gloomyfish1998/opencv_tutorial: 基于OpenCV3...
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace cv::ml;
using namespace std;

string positive_dir = "../dataset/elec_watch/elec_watch/positive/";
string negative_dir = "../dataset/elec_watch/elec_watch/negative/";
void get_hog_descripor(Mat &image, vector<float> &desc);
void generate_dataset(Mat &trainData, Mat &labels);
void svm_train(Mat &trainData, Mat &labels);

int main(int argc, char** argv) {
	Mat trainData = Mat::zeros(Size(3780, 26), CV_32FC1);
	Mat labels = Mat::zeros(Size(1, 26), CV_32SC1);
	generate_dataset(trainData, labels);
	svm_train(trainData, labels);
	Ptr<SVM> svm = SVM::load("./hog_elec.yml");
	Mat test_img = imread("../dataset/elec_watch/elec_watch/test/box_04.bmp");
	// Mat test_img = imread("D:/images/train_data/elec_watch/positive/box_01.bmp");
	imshow("test image", test_img);

	vector<float> fv;
	get_hog_descripor(test_img, fv);
	Mat one_row = Mat::zeros(Size(fv.size(), 1), CV_32FC1);
	for (int i = 0; i < fv.size(); i++) {
		one_row.at<float>(0, i) = fv[i];
	}
	float result = svm->predict(one_row);
	printf("\n prediction result : %.2f \n", result);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

void svm_train(Mat &trainData, Mat &labels) {
	printf("\n start SVM training... \n");
	Ptr< SVM > svm = SVM::create();
	/* Default values to train SVM */
	svm->setGamma(5.383);
	svm->setKernel(SVM::LINEAR);
	svm->setC(2.67);
	svm->setType(SVM::C_SVC);
	svm->train(trainData, ROW_SAMPLE, labels);
	clog << "...[done]" << endl;

	// save xml
	svm->save("./hog_elec.yml");
}

void get_hog_descripor(Mat &image, vector<float> &desc) {
	HOGDescriptor hog;
	int h = image.rows;
	int w = image.cols;
	float rate = 64.0 / w;
	Mat img, gray;
	resize(image, img, Size(64, int(rate*h)));
	cvtColor(img, gray, COLOR_BGR2GRAY);
	Mat result = Mat::zeros(Size(64, 128), CV_8UC1);
	result = Scalar(127);
	Rect roi;
	roi.x = 0;
	roi.width = 64;
	roi.y = (128 - gray.rows) / 2;
	roi.height = gray.rows;
	gray.copyTo(result(roi));
	hog.compute(result, desc, Size(8, 8), Size(0, 0));
}

void generate_dataset(Mat &trainData, Mat &labels) {
	vector<string> images;
	glob(positive_dir, images);
	int pos_num = images.size();
	for (int i = 0; i < images.size(); i++) {
		Mat image = imread(images[i].c_str());
		vector<float> fv;
		get_hog_descripor(image, fv);
		printf("image path : %s, feature data length: %d \n", images[i].c_str(), fv.size());
		for (int j = 0; j < fv.size(); j++) {
			trainData.at<float>(i, j) = fv[j];
		}
		labels.at<int>(i, 0) = 1;
	}

	images.clear();
	glob(negative_dir, images);
	for (int i = 0; i < images.size(); i++) {
		Mat image = imread(images[i].c_str());
		vector<float> fv;
		get_hog_descripor(image, fv);
		printf("image path : %s, feature data length: %d \n", images[i].c_str(), fv.size());
		for (int j = 0; j < fv.size(); j++) {
			trainData.at<float>(i + pos_num, j) = fv[j];
		}
		labels.at<int>(i + pos_num, 0) = -1;
	}
}