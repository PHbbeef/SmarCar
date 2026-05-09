#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("主程序");

    mycom = new com_control(this);
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

