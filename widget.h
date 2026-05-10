#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <com_control.h>
#include <opencv_data.h>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void onStartAction1();
    void onStartAction2();
    void onStartAction3();

    // 获取视频帧传输到 label
    void updateAllVideo();

private:
    Ui::Widget *ui;
    com_control *mycom;
    opencv_data *cvData;
    QTimer *timer;

    void showMatToLabel(cv::Mat &mat, QLabel *label);
};
#endif // WIDGET_H
