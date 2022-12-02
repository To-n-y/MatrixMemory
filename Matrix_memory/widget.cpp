#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    resize(550, 550);
    setWindowTitle("Matrix_memory");
    Del = 400;
    size_t *a = &Del;
    user = 0;
    data = nullptr;
    timer = new QTimer();
    timer->setInterval(500);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerAlarm()));
    par = new Parameters(a);
    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);
    ui->pushButton_6->hide();
    ui->lineEdit->hide();
    a = nullptr;
    delete a;


}

Widget::~Widget()
{
    delete ui;
    delete mtr;
    delete par;
    delete data;
    delete timer;
}


void Widget::on_pushButton_clicked()
{
    if (data == nullptr) mtr = new Matrix(par->getDel());
    else mtr = new Matrix(par->getDel(), data->getUser());
    this->hide();//
    mtr->show();
}


void Widget::on_pushButton_2_clicked()
{
    //this->~Widget();
    this->close();
}


void Widget::on_pushButton_3_clicked()
{
    par->show();
}


void Widget::on_pushButton_5_clicked()
{
    data = new Data(1);//вхoд
    data->show();
    timer->start();

}


void Widget::on_pushButton_4_clicked()
{
    data = new Data(0);//регистрация
    data->show();
    timer->start();
}

void Widget::timerAlarm()
{
    user = data->getUser();
    if (user != 0){

        std::ifstream fin("data.txt");
        std::string name;
        for (size_t i = 0; i < user*3-1; i++){

            fin >> name;
        }
        ui->lineEdit->show();
        ui->lineEdit->setText(QString::fromStdString(name));
        ui->pushButton_6->show();
        ui->pushButton_6->setStyleSheet("border: none; border-radius: 7px;");
        ui->pushButton_6->setIcon(QIcon("C:\\Qt_apps\\build-Matrix_memory-Desktop_Qt_5_15_2_MinGW_64_bit-Debug\\account.png"));
        timer->stop();
    }
}


void Widget::on_pushButton_6_clicked()
{
    user = 0;
    ui->pushButton_6->hide();
    ui->lineEdit->hide();
}

