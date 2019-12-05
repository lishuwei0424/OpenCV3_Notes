/*
HOG特征描述子 – 使用HOG进行对象检测

对于已经训练好的HOG+SVM的模型，我们可以通过开窗实现对象检测，从而完成自定义对象检测。以电表检测为例，这样我们就实现HOG+SVM对象检测全流程。
OpenCV中实现对每个窗口像素块预测，需要首先加载SVM模型文件，然后使用predict方法实现预测。这种方法的缺点就是开窗检测是从左到右、从上到下，
是一个高耗时的操作，所以步长选择一般会选择HOG窗口默认步长的一半，这样可以减少检测框的数目，同时在predict时候会发现多个重复框，求取它们的平均值
即可得到最终的检测框。

PS：OpenCV如何识别自定义目标！
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
vector< float > get_svm_detector(const Ptr< SVM >& svm);

int main(int argc, char** argv) {
	
	Mat trainData = Mat::zeros(Size(3780, 26), CV_32FC1);
	Mat labels = Mat::zeros(Size(1, 26), CV_32SC1);
	generate_dataset(trainData, labels);
	svm_train(trainData, labels);
	
	Ptr<SVM> svm = SVM::load("./hog_elec.yml");
	Mat test = imread("../dataset/elec_watch/elec_watch/test/scene_08.jpg");
	resize(test, test, Size(0, 0), 0.20, 0.20);

	imshow("input", test);
	Rect winRect;
	winRect.width = 64;
	winRect.height = 128;
	int sum_x = 0;
	int sum_y = 0;
	int count = 0;
	for (int row = 64; row < test.rows - 64; row += 4) {
		for (int col = 32; col < test.cols - 32; col += 4) {
			winRect.x = col - 32;
			winRect.y = row - 64;
			vector<float> fv;
			Mat mat = test(winRect);
			get_hog_descripor(mat, fv);
			Mat one_row = Mat::zeros(Size(fv.size(), 1), CV_32FC1);
			for (int i = 0; i < fv.size(); i++) {
				one_row.at<float>(0, i) = fv[i];
			}
			float result = svm->predict(one_row);
			if (result > 0) {
				// rectangle(test, winRect, Scalar(0, 0, 255), 1, 8, 0);
				sum_x += winRect.x;
				sum_y += winRect.y;
				count++;
			}
		}
	}
	winRect.x = sum_x / count;
	winRect.y = sum_y / count;
	rectangle(test, winRect, Scalar(255, 0, 0), 1, 8, 0);
	imshow("result", test);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

vector< float > get_svm_detector(const Ptr< SVM >& svm)
{
	// get the support vectors
	Mat sv = svm->getSupportVectors();
	const int sv_total = sv.rows;
	// get the decision function
	Mat alpha, svidx;
	double rho = svm->getDecisionFunction(0, alpha, svidx);

	CV_Assert(alpha.total() == 1 && svidx.total() == 1 && sv_total == 1);
	CV_Assert((alpha.type() == CV_64F && alpha.at<double>(0) == 1.) ||
		(alpha.type() == CV_32F && alpha.at<float>(0) == 1.f));
	CV_Assert(sv.type() == CV_32F);

	vector< float > hog_detector(sv.cols + 1);
	memcpy(&hog_detector[0], sv.ptr(), sv.cols * sizeof(hog_detector[0]));
	hog_detector[sv.cols] = (float)-rho;
	return hog_detector;
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