#include "pch.h"
#include "CImageProcess.h"

Mat CImageProcess::RGB_To_Gray(Mat src)
{
    Mat result;
    cvtColor(src, result, cv::COLOR_BGR2GRAY);
    return result;
}

Mat CImageProcess::Resize_To_200(Mat src)
{
    Mat result;
    resize(src, result, Size(0, 0), 2, 2);
    return result;
}

Mat CImageProcess::Resize_To_50(Mat src)
{
    Mat result;
    resize(src, result, Size(0, 0), 0.5, 0.5);
    return result;
}

Mat CImageProcess::Rotate_Clockwise_90(Mat src)
{
    Mat result;
    double alpha = 90 * CV_PI / 180.0;
    Point2f srcP[3], rstP[3];
    srcP[0] = Point2f(0, src.rows);
    srcP[1] = Point2f(src.cols, 0);
    srcP[2] = Point2f(src.cols, src.rows);
    for (int i = 0; i < 3; i++)
        rstP[i] = Point2f(srcP[i].x * cos(alpha) - srcP[i].y * sin(alpha),
                          srcP[i].y * cos(alpha) + srcP[i].x * sin(alpha));
    double minx, miny, maxx, maxy;
    minx = min(min(min(rstP[0].x, rstP[1].x), rstP[2].x), float(0.0));
    miny = min(min(min(rstP[0].y, rstP[1].y), rstP[2].y), float(0.0));
    maxx = max(max(max(rstP[0].x, rstP[1].x), rstP[2].x), float(0.0));
    maxy = max(max(max(rstP[0].y, rstP[1].y), rstP[2].y), float(0.0));
    
    int w = maxx - minx;
    int h = maxy - miny;

    for (int i = 0; i < 3; i++)
    {
        if (minx < 0)
            rstP[i].x -= minx;
        if (miny < 0)
            rstP[i].y -= miny;
    }

    Mat rotationMat = getAffineTransform(srcP, rstP);
    warpAffine(src, result, rotationMat, Size(w, h));

    return result;
}

Mat CImageProcess::Rotate_Counterclockwise_90(Mat src)
{
    Mat result;
    double alpha = -90 * CV_PI / 180.0;
    Point2f srcP[3], rstP[3];
    srcP[0] = Point2f(0, src.rows);
    srcP[1] = Point2f(src.cols, 0);
    srcP[2] = Point2f(src.cols, src.rows);
    for (int i = 0; i < 3; i++)
        rstP[i] = Point2f(srcP[i].x * cos(alpha) - srcP[i].y * sin(alpha),
            srcP[i].y * cos(alpha) + srcP[i].x * sin(alpha));
    double minx, miny, maxx, maxy;
    minx = min(min(min(rstP[0].x, rstP[1].x), rstP[2].x), float(0.0));
    miny = min(min(min(rstP[0].y, rstP[1].y), rstP[2].y), float(0.0));
    maxx = max(max(max(rstP[0].x, rstP[1].x), rstP[2].x), float(0.0));
    maxy = max(max(max(rstP[0].y, rstP[1].y), rstP[2].y), float(0.0));

    int w = maxx - minx;
    int h = maxy - miny;

    for (int i = 0; i < 3; i++)
    {
        if (minx < 0)
            rstP[i].x -= minx;
        if (miny < 0)
            rstP[i].y -= miny;
    }

    Mat rotationMat = getAffineTransform(srcP, rstP);
    warpAffine(src, result, rotationMat, Size(w, h));

    return result;
}

Mat CImageProcess::Detect_Face(Mat src)
{
    // 建立级联分类器
    CascadeClassifier cascade;
    // 加载训练好的 人脸检测器（.xml）
    //注意路径问题，当前目录的上一个目录中的xml文件夹下
    const string path = "C:\\Users\\16252\\Desktop\\Windows\\FinalWork\\xml\\haarcascade_frontalface_alt.xml";
    if (!cascade.load(path))
    {
        AfxMessageBox(TEXT("图像加载错误！"));
    }

    //计时
    double t = 0;
    t = (double)getTickCount();
   
    vector<Rect> faces(0);
    cascade.detectMultiScale(src, faces, 1.1, 2, 0, Size(30, 30));


    if (faces.size() > 0)
    {
        for (size_t i = 0; i < faces.size(); i++)
        {
            rectangle(src, faces[i], Scalar(150, 0, 0), 3, 8, 0);

        }
    }
    else AfxMessageBox(TEXT("未检测到人脸"));
    return src;
}

Mat CImageProcess::Edge_Detect(Mat src)
{
    Mat result;
    // 转换为灰度图像（如果输入是彩色图像）
    if (src.channels() == 3) {
        cvtColor(src, result, COLOR_BGR2GRAY);
    }
    else {
        result = src.clone();
    }

    // 定义Sobel的卷积核参数，分别计算水平和垂直方向的梯度
    Mat gradX, gradY;
    Mat absGradX, absGradY;

    // 计算X方向的梯度（Sobel算子的1阶导数）
    Sobel(result, gradX, CV_16S, 1, 0, 3);
    // 计算Y方向的梯度
    Sobel(result, gradY, CV_16S, 0, 1, 3);

    // 计算梯度的绝对值
    convertScaleAbs(gradX, absGradX);
    convertScaleAbs(gradY, absGradY);

    // 合并X和Y方向的梯度
    addWeighted(absGradX, 0.5, absGradY, 0.5, 0, result);
    return result;
}

Mat CImageProcess::Gaussian_Blur(Mat src)
{
    Mat result;
    int kernelSize = 5;    // 高斯核的大小
    double sigmaX = 1.5;   // X方向的标准差
    GaussianBlur(src, result, cv::Size(kernelSize, kernelSize), sigmaX);
    return result;
}
