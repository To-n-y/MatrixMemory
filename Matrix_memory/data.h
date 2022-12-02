#ifndef DATA_H
#define DATA_H

#include <QWidget>
#include<QMessageBox>
#include<fstream>
#include<QDebug>

namespace Ui {
class Data;
}

class Data : public QWidget
{
    Q_OBJECT

public:
    explicit Data(bool reg, QWidget *parent = nullptr);
    QString func(const QString&);
    size_t getUser() const {return user;}
    ~Data();

private slots:
    void on_pushButton_clicked();

private:
    bool reg;//0 если решистрация
    size_t user;
    Ui::Data *ui;
};

#endif // DATA_H
