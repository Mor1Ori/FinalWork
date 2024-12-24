#pragma once
class CImageProcess
{
public:
	Mat RGB_To_Gray(Mat src);                 // �Ҷȴ���
	Mat Resize_To_200(Mat src);				  // �Ŵ���200%
	Mat Resize_To_50(Mat src);				  // ��С��50%
	Mat Rotate_Clockwise_90(Mat src);		  // ˳ʱ����ת90��
	Mat Rotate_Counterclockwise_90(Mat src);  // ��ʱ����ת90��
	Mat Detect_Face(Mat src);				  // �������
	Mat Edge_Detect(Mat src);				  // ��Ե���
	Mat Gaussian_Blur(Mat src);				  // ͼ���˲�
};

