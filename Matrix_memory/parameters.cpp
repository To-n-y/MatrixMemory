#include "parameters.h"
#include <QDebug>
#include "ui_parameters.h"

Parameters::Parameters(size_t *_Del, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Parameters)
{
    setWindowTitle("Parameters");
    Del = _Del;
    ui->setupUi(this);

}

Parameters::~Parameters()
{
    delete Del;
    delete ui;
}

void Parameters::on_pushButton_clicked()
{
    *Del = 600;

    this->close();
}


void Parameters::on_pushButton_3_clicked()
{
    *Del = 400;

    this->close();
}


void Parameters::on_pushButton_2_clicked()
{
    *Del = 300;

    this->close();
}

