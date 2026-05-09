#include "com_control.h"

com_control::com_control(QWidget *parent)
    : QWidget{parent}
{
    com = new QSerialPort(this);

    baudRate = QSerialPort::Baud115200;
    stopBits = QSerialPort::OneStop;
    dataBits = QSerialPort::Data8;
    checkBits = QSerialPort::NoParity;
    com->setPortName("/dev/ttyUSB0");   // 串口选择
    openCom();

}


void com_control::openCom(){
    // 判断串口是否打开
    if(com->open(QIODevice::ReadWrite)){
        return;

    }else{
        // 串口无法打开错误信息
        QMessageBox::critical(this,"错误提示","打开串口失败");
        QMessageBox::critical(this,"串口信息",com->portName());
    }

}

QString com_control::msgCom(const QString &str){
    com->write(str.toLatin1());
}

void com_control::receive(){
    QByteArray buf; // 接收缓冲区
    buf = com->readAll();

    QString str; // 定义一个字符变量

    if(!buf.isEmpty()){
        str = tr(buf);  // 将字节数字的数据转换成字符类型
        qDebug() << "接收数据：" << str;
    }
}

// 前进
void com_control::onStartAction1() {
    QString msg = "@z\r\n";
    com->write(msg.toLatin1());
}

// 左转
void com_control::onStartAction2() {
    QString msg = "@1\r\n";
    com->write(msg.toLatin1());
}

// 右转
void com_control::onStartAction3() {
    QString msg = "@0\r\n";
    com->write(msg.toLatin1());
}

