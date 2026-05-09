#ifndef COM_CONTROL_H
#define COM_CONTROL_H

#include <QWidget>
#include <QSerialPort>
#include <QMessageBox>
#include <QDebug>

class com_control : public QWidget
{
    Q_OBJECT
public:
    explicit com_control(QWidget *parent = nullptr);

    void openCom(); // 打开串口
    void receive(); // 接收串口信息

    // 串口发送
    QString msgCom(const QString &str);

    // 单片机控制方向函数
    void onStartAction1();
    void onStartAction2();
    void onStartAction3();

private:
    QSerialPort::BaudRate baudRate; // 波特率
    QSerialPort::DataBits dataBits; // 数据位
    QSerialPort::StopBits stopBits;  // 停止位
    QSerialPort::Parity   checkBits;    // 奇偶校验位

    QSerialPort *com;

signals:

};

#endif // COM_CONTROL_H
