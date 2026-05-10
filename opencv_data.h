/*
对图片处理
*/

#ifndef OPENCV_DATA_H
#define OPENCV_DATA_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <QString>
#include <QDir>
#include <com_control.h>
#include <math.h>

class opencv_data : public QWidget
{
    Q_OBJECT
public:
    explicit opencv_data(QWidget *parent = nullptr);
    ~opencv_data();

    // 读取帧
    cv::Mat getFrame();
    cv::Mat getLastFrame();
    cv::Mat getFrameMaskRed();  // 红色掩码
    cv::Mat getFrameMaskBlue(); // 蓝色掩码
    cv::Mat getFrameMaskGreen();    // 绿色掩码
    cv::Mat getFrameMaskYellow();   // 黄色掩码

private:
    cv::VideoCapture capture;
    cv::VideoWriter videoSave;
    cv::Mat frame;
    cv::Mat conversion;

    // 颜色掩码变量
    cv::Mat mask_red, mask_blue, mask_green, mask_yellow;

    // 颜色阈值
    cv::Scalar lower_red, upper_red;
    cv::Scalar lower_light_red, upper_light_red;
    cv::Scalar lower_blue, upper_blue;
    cv::Scalar lower_green, upper_green;
    cv::Scalar lower_yellow, upper_yellow;
    cv::Scalar lower_black, upper_black;

    void saveFrame();// 视频保存
    void image_Conversion();
    void detectColor();
    void findDrawMaxContour(cv::Mat &mask, cv::Mat &src);


signals:
    void signalRequestForward(); // 前进
    void signalRequestLeft();    // 左转
    void signalRequestRight();   // 右转
};

#endif // OPENCV_DATA_H
