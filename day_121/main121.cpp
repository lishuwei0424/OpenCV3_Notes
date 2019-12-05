/*
OpenCV DNN 获取导入模型各层信息

模型下载地址：
opencv_tutorial/data/models/googlenet at master · ...

模型支持1000个类别的图像分类，OpenCV DNN模块支持下面框架的预训练模型的前馈网络(预测图)使用
-	Caffe
-	Tensorflow
-	Torch
-	DLDT
-	Darknet

同时还支持自定义层解析、非最大抑制操作、获取各层的信息等。OpenCV加载模型的通用API为
Net cv::dnn::readNet(
	const String & 	model,
	const String & 	config = "",
	const String & 	framework = ""
)
model二进制训练好的网络权重文件，可能来自支持的网络框架，扩展名为如下：
*.caffemodel (Caffe, http://caffe.berkeleyvision.org/)
*.pb (TensorFlow, https://www.tensorflow.org/)
*.t7 | *.net (Torch, http://torch.ch/)
*.weights (Darknet, https://pjreddie.com/darknet/)
*.bin (DLDT, https://software.intel.com/openvino-toolkit)

config针对模型二进制的描述文件，不同的框架配置文件有不同扩展名
*.prototxt (Caffe, http://caffe.berkeleyvision.org/)
*.pbtxt (TensorFlow, https://www.tensorflow.org/)
*.cfg (Darknet, https://pjreddie.com/darknet/)
*.xml (DLDT, https://software.intel.com/openvino-toolkit)

framework显示声明参数，说明模型使用哪个框架训练出来的

PS:恢复更新！
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

	// 获取各层信息
	vector<String> layer_names = net.getLayerNames();
	for (int i = 0; i < layer_names.size(); i++) {
		int id = net.getLayerId(layer_names[i]);
		auto layer = net.getLayer(id);
		printf("layer id:%d, type: %s, name:%s \n", id, layer->type.c_str(), layer->name.c_str());
	}
	return 0;
}


