/*
HOG���������� �C ��߶ȼ��

HOG(Histogram of Oriented Gradient)��������֧����ת�����ԣ�ͨ������������֧�ֶ�߶ȼ��ʵ�ֳ߶ȿռ䲻���ԣ�OpenCV��֧��HOG�����Ӷ�߶ȼ������API���£�
virtual void cv::HOGDescriptor::detectMultiScale(
	InputArray 	img,
	std::vector&lt; Rect &gt; &foundLocations,
	double 	hitThreshold = 0,
	Size 	winStride = Size(),
	Size 	padding = Size(),
	double 	scale = 1.05,
	double 	finalThreshold = 2.0,
	bool 	useMeanshiftGrouping = false
)
Img��ʾ����ͼ��
foundLocations��ʾ���ֶ�����ο�
hitThreshold��ʾSVM���������Ĭ��0��ʾ����ʾ������SVM���೬ƽ��֮��
winStride��ʾ���ڲ���
padding��ʾ���
scale��ʾ�߶ȿռ�
finalThreshold ������ֵ��Ĭ��Ϊ2.0
useMeanshiftGrouping ������ʹ�ã��ٶ�̫����

������д��ڲ�����Scale�Խ��Ӱ������ر���Scale��С�ĳ߶ȱ仯�����ڼ���ͷֱ��ʶ���ͬ��Ҳ�ᵼ��FP�������ߵĿ��Ա���FP���ǻ����FN���ж���©�죩�����ڲ�����һ�����߶��block���򣬹���Block������Կ���һ��ͼ��


PS : ����ο���100��ʱ��
*/