#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <QWidget>

namespace Ui {
class Parameters;
}

class Parameters : public QWidget
{
    Q_OBJECT

public:
    explicit Parameters(size_t *_Del, QWidget *parent = nullptr);
    explicit Parameters(size_t _Del, QWidget *parent = nullptr);
    size_t getDel() const {return *Del;}
    size_t getDel2() const {return Del2;}
    void setDel(size_t *_Del) {Del = _Del;}
    ~Parameters();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    size_t *Del;
    size_t Del2;
    Ui::Parameters *ui;
};

#endif // PARAMETERS_H
