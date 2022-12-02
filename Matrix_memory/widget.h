#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<fstream>
#include<QIcon>
#include"matrix.h"
#include"parameters.h"
#include"data.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();
    void timerAlarm();

    void on_pushButton_6_clicked();

private:
    QTimer *timer;
    size_t user;
    size_t Del;
    Data *data;
    Parameters *par;
    Matrix *mtr;
    Ui::Widget *ui;
};
#endif // WIDGET_H
