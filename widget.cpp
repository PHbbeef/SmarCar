#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("主程序");

    // OpenCV 初始化
    cvData = new opencv_data(this);


    // 定时器：只需要一个，统一刷新
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::updateAllVideo);
    timer->start(30);


    mycom = new com_control(this);

    // 自动控制逻辑
    connect(cvData, &opencv_data::signalRequestForward, mycom, &com_control::onStartAction1);
    connect(cvData, &opencv_data::signalRequestLeft,    mycom, &com_control::onStartAction2);
    connect(cvData, &opencv_data::signalRequestRight,   mycom, &com_control::onStartAction3);

    // 手动控制
    connect(ui->pushButton, &QPushButton::pressed, this, &Widget::onStartAction1);
    connect(ui->pushButton_2, &QPushButton::pressed, this, &Widget::onStartAction2);
    connect(ui->pushButton_3, &QPushButton::pressed, this, &Widget::onStartAction3);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onStartAction1() {
    mycom->onStartAction1();
}

void Widget::onStartAction2() {
    mycom->onStartAction2();
}

void Widget::onStartAction3() {
    mycom->onStartAction3();
}


void Widget::updateAllVideo()
{
    // 1. 只读取一帧（所有画面共用这一帧，解决黑屏）
    cvData->getFrame();

    // 2. 获取5种图像
    cv::Mat mat_original = cvData->getLastFrame();          // 原图
    cv::Mat mat_red      = cvData->getFrameMaskRed();       // 红掩码
    cv::Mat mat_blue     = cvData->getFrameMaskBlue();      // 蓝掩码
    cv::Mat mat_green    = cvData->getFrameMaskGreen();     // 绿掩码
    cv::Mat mat_yellow   = cvData->getFrameMaskYellow();    // 黄掩码

    // 3. 分别显示到 5 个 Label（一一对应）
    showMatToLabel(mat_original, ui->label);
    // showMatToLabel(mat_red,      ui->label_2);
    // showMatToLabel(mat_blue,     ui->label_3);
    // showMatToLabel(mat_green,    ui->label_4);
    showMatToLabel(mat_yellow,   ui->label_2);
}


void Widget::showMatToLabel(cv::Mat &mat, QLabel *label)
{
    if (mat.empty()) return;

    cv::Mat temp;
    if (mat.channels() == 1) {
        // 掩码是灰度图 → 直接转彩色显示
        cv::cvtColor(mat, temp, cv::COLOR_GRAY2RGB);
    } else {
        // 原图 BGR → RGB
        cv::cvtColor(mat, temp, cv::COLOR_BGR2RGB);
    }

    QImage img(temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    label->setPixmap(
        QPixmap::fromImage(img).scaled(label->size(),
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation)
        );
}
