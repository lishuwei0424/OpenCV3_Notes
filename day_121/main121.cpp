/*
OpenCV DNN ��ȡ����ģ�͸�����Ϣ

ģ�����ص�ַ��
opencv_tutorial/data/models/googlenet at master �� ...

ģ��֧��1000������ͼ����࣬OpenCV DNNģ��֧�������ܵ�Ԥѵ��ģ�͵�ǰ������(Ԥ��ͼ)ʹ��
-	Caffe
-	Tensorflow
-	Torch
-	DLDT
-	Darknet

ͬʱ��֧���Զ�����������������Ʋ�������ȡ�������Ϣ�ȡ�OpenCV����ģ�͵�ͨ��APIΪ
Net cv::dnn::readNet(
	const String & 	model,
	const String & 	config = "",
	const String & 	framework = ""
)
model������ѵ���õ�����Ȩ���ļ�����������֧�ֵ������ܣ���չ��Ϊ���£�
*.caffemodel (Caffe, http://caffe.berkeleyvision.org/)
*.pb (TensorFlow, https://www.tensorflow.org/)
*.t7 | *.net (Torch, http://torch.ch/)
*.weights (Darknet, https://pjreddie.com/darknet/)
*.bin (DLDT, https://software.intel.com/openvino-toolkit)

config���ģ�Ͷ����Ƶ������ļ�����ͬ�Ŀ�������ļ��в�ͬ��չ��
*.prototxt (Caffe, http://caffe.berkeleyvision.org/)
*.pbtxt (TensorFlow, https://www.tensorflow.org/)
*.cfg (Darknet, https://pjreddie.com/darknet/)
*.xml (DLDT, https://software.intel.com/openvino-toolkit)

framework��ʾ����������˵��ģ��ʹ���ĸ����ѵ��������

PS:�ָ����£�
*/

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>

using namespace cv;
using namespace cv::dnn;
using namespace std;

int main(int argc, char** argv) {
	string bin_model = "../models/googlenet/bvlc_googlenet.caffemodel";
	string protxt = "../models/googlenet/bvlc_googlenet.prototxt";

	// load CNN model
	Net net = dnn::readNet(bin_model, protxt);

	// ��ȡ������Ϣ
	vector<String> layer_names = net.getLayerNames();
	for (int i = 0; i < layer_names.size(); i++) {
		int id = net.getLayerId(layer_names[i]);
		auto layer = net.getLayer(id);
		printf("layer id:%d, type: %s, name:%s \n", id, layer->type.c_str(), layer->name.c_str());
	}
	return 0;
}


