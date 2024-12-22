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
