#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <com_control.h>

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


private:
    Ui::Widget *ui;
    com_control *mycom;
};
#endif // WIDGET_H
