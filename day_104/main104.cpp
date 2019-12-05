/*
���ڵõ��Ľṹ��HOG�������ݣ����ǾͿ���ͨ����ʼ��SVM���лع����ѵ����������õ�ѵ������SVM���Է�������SVM��������һ�����������Ƕ������Բ��ɷ����ݵľ����������
OpenCV��ʹ�þ��������SVM��ʱ���ѵ���ܳ�ʱ�䣬���ҽ������⣬�����ᱨһЩĪ������Ĵ��󣬸о������ر�á������Ƽ����������Բ��ɷֵ��������ѡ��������ANNģ�顣

��ѵ��֮ǰ�����ȼ򵥵���ʶһ��SVM�����������ͨ������������ɣ��Ǻܵ��͵����Կɷ����SVM��


�����Կɷֵ�ѡ����SVM��ͨ�����ٵ�����ѧϰ�ͻ�ȡ�úܺõ�Ч����OpenCV��SVMѵ����API���£�
virtual bool cv::ml::StatModel::train(
	InputArray 	samples,
	int layout,
	InputArray 	responses
)
Sample��ʾѵ����������/HOG��������
Layout ��������֯��ʽROW_SAMPLE��COL_SAMPLE
Responses ÿ�����������ı�ǩ

����ѵ���õ��������ǿ���ͨ��save�������б��棬ֻҪ�ṩһ������·�����ɡ�
��������ļ���
GitHub - gloomyfish1998/opencv_tutorial: ����OpenCV3...
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