// tcpSocketClient 客户端对EPS32发送数据进行控制

#include "client.h"



client::client(QWidget *parent)
    : QMainWindow{parent}
{
    tcpSocketClient = new QTcpSocket(this);
    tcpSocketClient->abort();
    tcpSocketClient->connectToHost("10.0.0.101",6000);
}

void client::onStartAction1() {
    int cat_Status = 100;
    QString msg = QString::number(cat_Status) + "\r";
    tcpSocketClient->connectToHost("10.0.0.101",6000);
    tcpSocketClient->write(msg.toUtf8());
    tcpSocketClient->close();
}

void client::onFinishAction1() {
    int cat_Status = 000;
    QString msg = QString::number(cat_Status) + "\r";
    tcpSocketClient->connectToHost("10.0.0.101",6000);
    tcpSocketClient->write(msg.toUtf8());
    tcpSocketClient->close();
}

void client::onStartAction2() {
    int cat_Status = 010;
    QString msg = QString::number(cat_Status) + "\r";
    tcpSocketClient->connectToHost("10.0.0.101",6000);
    tcpSocketClient->write(msg.toUtf8());
    tcpSocketClient->close();
}

void client::onFinishAction2() {
    int cat_Status = 000;
    QString msg = QString::number(cat_Status) + "\r";
    tcpSocketClient->connectToHost("10.0.0.101",6000);
    tcpSocketClient->write(msg.toUtf8());
    tcpSocketClient->close();
}

void client::onStartAction3() {
    int cat_Status = 001;
    QString msg = QString::number(cat_Status) + "\r";
    tcpSocketClient->connectToHost("10.0.0.101",6000);
    tcpSocketClient->write(msg.toUtf8());
    tcpSocketClient->close();
}

void client::onFinishAction3() {
    int cat_Status = 000;
    QString msg = QString::number(cat_Status) + "\r";
    tcpSocketClient->connectToHost("10.0.0.101",6000);
    tcpSocketClient->write(msg.toUtf8());
    tcpSocketClient->close();
}


