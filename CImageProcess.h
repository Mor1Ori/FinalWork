#pragma once
class CImageProcess
{
public:
	Mat RGB_To_Gray(Mat src);                 // 灰度处理
	Mat Resize_To_200(Mat src);				  // 放大至200%
	Mat Resize_To_50(Mat src);				  // 缩小至50%
	Mat Rotate_Clockwise_90(Mat src);		  // 顺时针旋转90°
	Mat Rotate_Counterclockwise_90(Mat src);  // 逆时针旋转90°
	Mat Detect_Face(Mat src);				  // 人脸检测
	Mat Edge_Detect(Mat src);				  // 边缘检测
	Mat Gaussian_Blur(Mat src);				  // 图像滤波
};

