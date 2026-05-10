#include "com_control.h"

com_control::com_control(QWidget *parent)
    : QWidget{parent}
{
    com = new QSerialPort(this);

    // 串口参数配置
    baudRate = QSerialPort::Baud115200;
    stopBits = QSerialPort::OneStop;
    dataBits = QSerialPort::Data8;
    checkBits = QSerialPort::NoParity;

    // 必须先设置参数，再设置端口，再打开
    com->setBaudRate(baudRate);
    com->setStopBits(stopBits);
    com->setDataBits(dataBits);
    com->setParity(checkBits);
    com->setFlowControl(QSerialPort::NoFlowControl);

    com->setPortName("/dev/ttyUSB0");

    // 连接接收信号
    connect(com, &QSerialPort::readyRead, this, &com_control::receive);

    openCom();
}

void com_control::openCom()
{
    // 如果已经打开，先关闭
    if (com->isOpen()) {
        com->close();
    }

    // 打开串口
    if (com->open(QIODevice::ReadWrite)) {
        qDebug() << "串口打开成功：" << com->portName();
    } else {
        QMessageBox::critical(this, "错误提示", "打开串口失败！\n" + com->errorString());
        QMessageBox::critical(this, "失败端口", com->portName());
    }
}

QString com_control::msgCom(const QString &str)
{
    if (!com->isOpen()) {
        QMessageBox::warning(this, "警告", "串口未打开，无法发送");
        return "";
    }

    com->write(str.toLatin1());
    com->flush();
    qDebug() << "发送成功：" << str;
    return str;
}


void com_control::receive()
{
    QByteArray buf = com->readAll();
    if (!buf.isEmpty()) {
        QString str = QString::fromLatin1(buf);
        qDebug() << "====================";
        qDebug() << "接收数据：" << str;
        qDebug() << "====================";
    }
}


void com_control::onStartAction1()
{
    com->write("@z\r\n");
    com->flush();
    qDebug() << "前进";
}

void com_control::onStartAction2()
{
    com->write("@1\r\n");
    com->flush();
    qDebug() << "左转";
}

void com_control::onStartAction3()
{
    com->write("@0\r\n");
    com->flush();
    qDebug() << "右转";
}
