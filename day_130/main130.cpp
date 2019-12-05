/*
OpenCV DNN 支持YOLO对象检测网络运行

OpenCV DNN模块支持YOLO对象检测网络，最新的OpenCV4.0支持YOLOv3版本的对象检测网络，YOLOv3版本同时还发布了移动端支持的网络模型YOLOv3-tiny版本，速度可以在CPU端实时运行的对象检测网络，OpenCV中通过对DarkNet框架集成支持实现YOLO网络加载与检测。因为YOLOv3对象检测网络是多个层的合并输出，所以在OpenCV中调用时候必须显示声明那些是输出层，这个对于对象检测网络，OpenCV提供了一个API来获取所有的输出层名称，该API为：
std::vector<String> cv::dnn::Net::getUnconnectedOutLayersNames()const
该函数返回所有非连接的输出层。

调用时候，必须显式通过输入参数完成推断，相关API如下：
void cv::dnn::Net::forward(
	OutputArrayOfArrays outputBlobs,
	const std::vector< String > & outBlobNames
)
outputBlobs是调用之后的输出
outBlobNames是所有输出层的名称

跟SSD/Faster-RCNN出来的结构不一样，YOLO的输出前四个为
# [center_x, center_y, width, height]
后面的是所有类别的得分，这个时候只要根据score大小就可以得到score最大的对应对象类别，解析检测结果。相关模型下载到YOLO作者的官方网站：
YOLO: Real-Time Object Detection

推荐阅读：
对象检测网络中的NMS算法详解
OpenCV中使用YOLO对象检测
*/

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;
using namespace cv;
using namespace cv::dnn;
String yolo_cfg = "D:/projects/pose_body/hand/yolov3.cfg";
String yolo_model = "D:/projects/pose_body/hand/yolov3.weights";
int main(int argc, char** argv)
{
	Net net = readNetFromDarknet(yolo_cfg, yolo_model);
	net.setPreferableBackend(DNN_BACKEND_INFERENCE_ENGINE);
	net.setPreferableTarget(DNN_TARGET_CPU);
	std::vector<String> outNames = net.getUnconnectedOutLayersNames();
	for (int i = 0; i < outNames.size(); i++) {
		printf("output layer name : %s\n", outNames[i].c_str());
	}

	// 加载COCO数据集标签
	vector<string> classNamesVec;
	ifstream classNamesFile("D:/projects/opencv_tutorial/data/models/object_detection_classes_yolov3.txt");
	if (classNamesFile.is_open())
	{
		string className = "";
		while (std::getline(classNamesFile, className))
			classNamesVec.push_back(className);
	}

	// 加载图像 
	Mat frame = imread("D:/images/pedestrian.png");
	Mat inputBlob = blobFromImage(frame, 1 / 255.F, Size(416, 416), Scalar(), true, false);
	net.setInput(inputBlob);

	// 检测
	std::vector<Mat> outs;
	net.forward(outs, outNames);
	vector<double> layersTimings;
	double freq = getTickFrequency() / 1000;
	double time = net.getPerfProfile(layersTimings) / freq;
	ostringstream ss;
	ss << "detection time: " << time << " ms";
	putText(frame, ss.str(), Point(20, 20), 0, 0.5, Scalar(0, 0, 255));
	vector<Rect> boxes;
	vector<int> classIds;
	vector<float> confidences;
	for (size_t i = 0; i < outs.size(); ++i)
	{
		// Network produces output blob with a shape NxC where N is a number of
		// detected objects and C is a number of classes + 4 where the first 4
		// numbers are [center_x, center_y, width, height]
		float* data = (float*)outs[i].data;
		for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
		{
			Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
			Point classIdPoint;
			double confidence;
			minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
			if (confidence > 0.5)
			{
				int centerX = (int)(data[0] * frame.cols);
				int centerY = (int)(data[1] * frame.rows);
				int width = (int)(data[2] * frame.cols);
				int height = (int)(data[3] * frame.rows);
				int left = centerX - width / 2;
				int top = centerY - height / 2;

				classIds.push_back(classIdPoint.x);
				confidences.push_back((float)confidence);
				boxes.push_back(Rect(left, top, width, height));
			}
		}
	}

	// 非最大抑制操作
	vector<int> indices;
	NMSBoxes(boxes, confidences, 0.5, 0.2, indices);
	for (size_t i = 0; i < indices.size(); ++i)
	{
		int idx = indices[i];
		Rect box = boxes[idx];
		String className = classNamesVec[classIds[idx]];
		putText(frame, className.c_str(), box.tl(), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 0, 0), 2, 8);
		rectangle(frame, box, Scalar(0, 0, 255), 2, 8, 0);
	}

	imshow("YOLOv3-Detections", frame);
	waitKey(0);
	destroyAllWindows();

	return;
}