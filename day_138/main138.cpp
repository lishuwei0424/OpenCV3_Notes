/*
OpenCV DNN 使用OpenVINO加速

OpenVINO
Intel® Distribution of OpenVINO™ Toolkit | Intel® ...

支持raspberry、widnows、linux系统的CPU加速，对OpenCV DNN模块，其它的API调用都进行了加速！其核心是DLIE(Deep Learning Inference Engine), 相关的配置与安装说明可以参考Intel官方网站，支持一键加速。
最新的在线安装web installer
w_openvino_toolkit_p_2018.5.456_online
内置已经编译好的OpenCV4.0.1版本
直接配置即可使用！其配置方式与正常的OpenCV+VS2015开发配置相同，唯一不同的是需要把
%install_dir%\inference_engine\bin\intel64\Debug
加到环境变量中去。
然后在调用的时候，直接通过下面这句话就可以使用IE作为计算后台
net.setPreferableBackend(DNN_BACKEND_INFERENCE_ENGINE);

发现对某些模型使用IE作为计算后天的时候，会报错，这个时候需要使用默认后台
net.setPreferableBackend(DNN_BACKEND_OPENCV);
即可：

相关参考
GitHub - opencv/dldt: Deep Learning Deployment Too...
Inference Engine Developer Guide | Intel® Software

同时OpenVINO还提供了一系列的API可以单独解析二进制的模型，实现调用，无须OpenCV DNN支持，安装以后可以去sample文件夹学习即可！

PS: 今天没有语音！
*/