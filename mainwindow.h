#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartAction1();
    void onFinishAction1();
    void onStartAction2();
    void onFinishAction2();
    void onStartAction3();
    void onFinishAction3();

private:
    Ui::MainWindow *ui;
    client *myClient; // 声明一个唯一的成员变量
};
#endif
