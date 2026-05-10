/*
红色区间： 红色在 HSV 中跨越了 0 和 180，你处理了两个区间并相加，这是正确的。

环境适应性： 实验室的灯光和室外阳光会导致 HSV 值剧烈波动。

建议： 增加一个“调试模式”，用 cv::createTrackbar 或 Qt 的 QSlider 动态调节这些 Scalar 参数，否则换个环境代码就失效了。
 */


#include "opencv_data.h"
#include <QDir>
#include <QDebug>


opencv_data::opencv_data(QWidget *parent)
    : QWidget{parent}
{

    // 打开视频/摄像头
    capture.open("D:\\1.avi");
    if (!capture.isOpened()) {
        qDebug() << "摄像头/视频打开失败！";
        return;
    }

    // 颜色识别阈值初始化（必须先设置，否则 detectColor 不工作）
    lower_red        = cv::Scalar(0, 100, 100);
    upper_red        = cv::Scalar(10, 255, 255);
    lower_light_red  = cv::Scalar(170, 100, 100);
    upper_light_red  = cv::Scalar(180, 255, 255);

    lower_blue       = cv::Scalar(100, 100, 100);
    upper_blue       = cv::Scalar(124, 255, 255);

    lower_green      = cv::Scalar(40, 100, 100);
    upper_green      = cv::Scalar(77, 255, 255);

    lower_yellow     = cv::Scalar(20, 100, 100);
    upper_yellow     = cv::Scalar(34, 255, 255);

    lower_black      = cv::Scalar(0, 0, 0);
    upper_black      = cv::Scalar(180, 255, 40);


    // 获取视频信息并初始化保存
    int fps = capture.get(cv::CAP_PROP_FPS);
    int w = capture.get(cv::CAP_PROP_FRAME_WIDTH);
    int h = capture.get(cv::CAP_PROP_FRAME_HEIGHT);
    QString savePath = QDir::currentPath() + "/output.avi";
    videoSave.open(
        savePath.toStdString(),
        cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
        fps,
        cv::Size(w, h)
        );
}

opencv_data::~opencv_data()
{
    if (capture.isOpened()) capture.release();
    if (videoSave.isOpened()) videoSave.release();
    frame.release();
    conversion.release();
    mask_red.release();
    mask_blue.release();
    mask_green.release();
    mask_yellow.release();
}

cv::Mat opencv_data::getFrame()
{

    capture.read(frame);    // 读取帧

    // 保存视频
    saveFrame();

    // 转HSV
    image_Conversion();

    // 颜色识别，生成所有掩码
    detectColor();

    return frame;
}


cv::Mat opencv_data::getLastFrame()
{
    return frame;
}


cv::Mat opencv_data::getFrameMaskRed()
{
    return mask_red;
}


cv::Mat opencv_data::getFrameMaskBlue()
{
    return mask_blue;
}


cv::Mat opencv_data::getFrameMaskGreen()
{
    return mask_green;
}


cv::Mat opencv_data::getFrameMaskYellow()
{
    return mask_yellow;
}

void opencv_data::saveFrame()
{
    if (!frame.empty() && videoSave.isOpened()) {
        videoSave.write(frame);
    }
}

void opencv_data::image_Conversion()
{
    cv::cvtColor(frame, conversion, cv::COLOR_BGR2HSV);
}

void opencv_data::detectColor()
{
    if (frame.empty() || conversion.empty()) return;

    // 1. 生成初始掩码 (原有代码)
    // ---------- 红色 ----------
    cv::Mat mask_light_red;
    cv::inRange(conversion, lower_red, upper_red, mask_red);
    cv::inRange(conversion, lower_light_red, upper_light_red, mask_light_red);
    mask_red = mask_red + mask_light_red;

    // ---------- 蓝、绿、黄 ----------
    cv::inRange(conversion, lower_blue, upper_blue, mask_blue);
    cv::inRange(conversion, lower_green, upper_green, mask_green);
    cv::inRange(conversion, lower_yellow, upper_yellow, mask_yellow);

    // ================== 新增功能：形态学去噪 (源码逻辑不变，仅对掩码进行优化) ==================
    // 创建 5x5 的矩形结构元素
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));

    // 对需要识别的掩码进行优化处理
    // 开运算 (MORPH_OPEN): 移除微小噪点 (先腐蚀再膨胀)
    // 闭运算 (MORPH_CLOSE): 填充目标内部的小孔或断开的空隙 (先膨胀再腐蚀)

    auto optimizeMask = [&](cv::Mat &mask) {
        if(!mask.empty()){
            cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);
            cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, kernel);
        }
    };

    optimizeMask(mask_red);
    optimizeMask(mask_blue);
    optimizeMask(mask_green);
    optimizeMask(mask_yellow);
    // ====================================================================================

    // 2. 给原图画轮廓框并触发信号 (原有代码)
    findDrawMaxContour(mask_red, frame);
    findDrawMaxContour(mask_blue, frame);
    findDrawMaxContour(mask_green, frame);
    findDrawMaxContour(mask_yellow, frame);
}

void opencv_data::findDrawMaxContour(cv::Mat &mask, cv::Mat &src)
{
    // 判断是否为空
    if (mask.empty()) return;
    // cv::Point 一个坐标点 (x,y) ；std::vector<cv::Point> 一串点 → 连成一条轮廓线 ；std::vector<std::vector<cv::Point>> = 很多条轮廓线
    std::vector<std::vector<cv::Point>> cnts;
    // 检测出物体的轮廓
    cv::findContours(mask.clone(), cnts, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    if (cnts.empty()) return;

    int maxIdx = 0;
    double maxArea = 0;
    for (int i = 0; i < (int)cnts.size(); ++i) {
        double area = cv::contourArea(cnts[i]);
        if (area > maxArea) {
            maxArea = area;
            maxIdx = i;
        }
    }

    if (maxArea < 1000) return;

    cv::RotatedRect rect = cv::minAreaRect(cnts[maxIdx]);
    cv::Point2f box[4];
    rect.points(box);
    std::vector<cv::Point> boxPts;
    for (int i = 0; i < 4; ++i) {
        boxPts.push_back(cv::Point(box[i].x, box[i].y));
    }
    cv::drawContours(src, std::vector<std::vector<cv::Point>>{boxPts}, 0, cv::Scalar(0, 255, 255), 2);

    // ================== 左右控制逻辑 ==================
    int imgMid = src.cols / 2;
    int x = rect.center.x;
    int offset = 300;              // 这是死区范围

    if (x < (imgMid - offset)) {
        // qDebug() << "目标在左，发射左转信号";
        emit signalRequestLeft();
    }
    else if (x > (imgMid + offset)) {
        // qDebug() << "目标在右，发射右转信号";
        emit signalRequestRight();
    }
    else {
        // qDebug() << "目标在中，发射前进信号";
        emit signalRequestForward();
    }

    // 可视化调试：修正了 deadZone 为 offset
    cv::line(src, cv::Point(imgMid, 0), cv::Point(imgMid, src.rows), cv::Scalar(255, 0, 0), 1);
    cv::line(src, cv::Point(imgMid - offset, 0), cv::Point(imgMid - offset, src.rows), cv::Scalar(100, 100, 100), 1);
    cv::line(src, cv::Point(imgMid + offset, 0), cv::Point(imgMid + offset, src.rows), cv::Scalar(100, 100, 100), 1);
}
