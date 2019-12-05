/*
OpenCV DNN 支持YOLOv3-tiny版本实时对象检测

YOLOv3的模型在CPU上无法做到实时运行，而YOLO作者提供了个YOLOv3版本的精简版对象检测模型，大小只有30MB左右，但是模型可以在CPU上做到实时运行，这个模型就是YOLOv3-tiny模型，其下载地址如下：
YOLO: Real-Time Object Detection

相比YOLOv3，YOLOv3-tiny只有两个输出层，而且权重参数层与参数文件大小都大大的下降，可以在嵌入式设备与前端实时运行。
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
void image_detection();
String yolo_tiny_model = "D:/projects/opencv_tutorial/data/models/yolov3-tiny-coco/yolov3-tiny.weights";
String yolo_tiny_cfg = "D:/projects/opencv_tutorial/data/models/yolov3-tiny-coco/yolov3-tiny.cfg";
int main(int argc, char** argv)
{
	image_detection();
}

void image_detection() {
	Net net = readNetFromDarknet(yolo_tiny_cfg, yolo_tiny_model);
	net.setPreferableBackend(DNN_BACKEND_INFERENCE_ENGINE);
	net.setPreferableTarget(DNN_TARGET_CPU);
	std::vector<String> outNames = net.getUnconnectedOutLayersNames();
	for (int i = 0; i < outNames.size(); i++) {
		printf("output layer name : %s\n", outNames[i].c_str());
	}

	vector<string> classNamesVec;
	ifstream classNamesFile("D:/projects/opencv_tutorial/data/models/object_detection_classes_yolov3.txt");
	if (classNamesFile.is_open())
	{
		string className = "";
		while (std::getline(classNamesFile, className))
			classNamesVec.push_back(className);
	}

	// ¼ÓÔØÍ¼Ïñ 
	Mat frame = imread("D:/images/pedestrian.png");
	Mat inputBlob = blobFromImage(frame, 1 / 255.F, Size(416, 416), Scalar(), true, false);
	net.setInput(inputBlob);

	// ¼ì²â
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