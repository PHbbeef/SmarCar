#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

class client : public QMainWindow
{
    Q_OBJECT

public:
    explicit client(QWidget *parent = nullptr);

    void onStartAction1();
    void onFinishAction1();
    void onStartAction2();
    void onFinishAction2();
    void onStartAction3();
    void onFinishAction3();

private:
    QTcpSocket *tcpSocketClient;
};

#endif
