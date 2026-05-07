#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("客户端");

    myClient = new client(this);

    connect(ui->pushButton, &QPushButton::pressed, this, &MainWindow::onStartAction1);
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::onFinishAction1);
    connect(ui->pushButton_2, &QPushButton::pressed, this, &MainWindow::onStartAction2);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::onFinishAction2);
    connect(ui->pushButton_3, &QPushButton::pressed, this, &MainWindow::onStartAction3);
    connect(ui->pushButton_3, &QPushButton::released, this, &MainWindow::onFinishAction3);
}

MainWindow::~MainWindow() {
    delete ui;
}

// 使用 MainWindow:: 作用域，并直接调用 myClient
void MainWindow::onStartAction1() {
    myClient->onStartAction1();
}

void MainWindow::onFinishAction1() {
    myClient->onFinishAction1();
}

void MainWindow::onStartAction2() {
    myClient->onStartAction2();
}

void MainWindow::onFinishAction2() {
    myClient->onFinishAction2();
}
void MainWindow::onStartAction3() {
    myClient->onStartAction3();
}

void MainWindow::onFinishAction3() {
    myClient->onFinishAction3();
}
