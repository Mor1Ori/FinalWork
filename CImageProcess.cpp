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
