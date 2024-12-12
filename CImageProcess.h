#pragma once
class CImageProcess
{
public:
	Mat RGB_To_Gray(Mat src);
	Mat Resize_To_200(Mat src);
	Mat Resize_To_50(Mat src);
	Mat Rotate_Clockwise_90(Mat src);
	Mat Rotate_Counterclockwise_90(Mat src);
};

