#ifndef MATRIX_H
#define MATRIX_H

#include<QWidget>
#include<QDebug>
#include<QPaintEvent>
#include<QVector>
#include<QColor>
#include<QMessageBox>
#include<QRandomGenerator>
#include<QThread>
#include<QTimer>
#include<QPair>
#include<fstream>
#include"parameters.h"

namespace Ui {
class Matrix;
}

class Matrix : public QWidget
{
    Q_OBJECT

public:
    explicit Matrix(size_t _Del = 400, size_t _user = 0, QWidget *parent = nullptr);
    void setDel(size_t _Del) {Del = _Del;}
    size_t* getDel() const {return Delay;}
    ~Matrix();

private slots:
    void on_pushButton_clicked();

    void timerAlarm();


    void on_pushButtonExit_clicked();

    void on_pushButtonPar_clicked();

private:
    void initGame();
    void buildMemory(size_t level);
    void delay(int ms);
    void setRecord(size_t record) const;
    void DrawBtn(QPushButton*, QColor);

    size_t user;
    size_t Del;
    size_t *Delay;
    int currentBtn;
    QTimer *timer;
    Parameters *par;
    bool activeGame;
    size_t level;
    size_t currentMem;
    QVector<QPair<size_t, QColor>> memory;
    Ui::Matrix *ui;
};

#endif // MATRIX_H
