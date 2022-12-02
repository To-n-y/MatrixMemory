#include "matrix.h"
#include "ui_matrix.h"


Matrix::Matrix(size_t _Del, size_t _user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Matrix)
{
    ui->setupUi(this);
    resize(550, 550);
    setWindowTitle("Matrix_memory");
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
    Del = _Del;
    Delay = &Del;
    user = _user;
    timer = new QTimer();
    timer->setInterval(Del);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerAlarm()));

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    level = 1;
    currentBtn = 0;

    if (user == 0){
        ui->label_2->hide();
        ui->lineEdit_2->hide();
    }
    else{
        std::ifstream fin("data.txt");
        if (!fin.is_open()){
            QMessageBox msb;
            msb.setText("Error!");
            this->close();
        }
        std::string temp;
        for (size_t i = 0; i < user*3-1; i++) fin >> temp;
        ui->label_3->setText(QString::fromStdString(temp));
        fin >> temp;
        ui->lineEdit_2->setText(QString::fromStdString(temp));
    }
    initGame();
}

Matrix::~Matrix()
{
    delete ui;
    delete par;
    delete timer;
    delete Delay;
}

void Matrix::on_pushButton_clicked()
{
    QVector<QPushButton*> buttons = {ui->pushButton_0, ui->pushButton_1, ui->pushButton_2,
                                    ui->pushButton_3, ui->pushButton_4, ui->pushButton_5,
                                    ui->pushButton_6, ui->pushButton_7, ui->pushButton_8};
    if (activeGame == false) return;
    QPushButton *btn = (QPushButton*) sender();
    QString str = btn->objectName();
    if (str[11] == QString::number(memory[currentMem].first)){
        DrawBtn(btn, memory[currentMem].second);
        if (currentMem > 0) buttons[memory[currentMem-1].first]->setStyleSheet("QPushButton {background-color: rgb(89, 89, 89)}");
        currentMem++;

        if (currentMem == level+1){
            if (level > ui->lineEdit_2->text().toInt()){
                ui->lineEdit_2->setText(QString::number(level));
                setRecord(level);
            }
            Del -= 10;
            if (Del <= 300) Del = 300;
            level++;
            delay(500);
            buttons[currentMem-1]->setStyleSheet("QPushButton {background-color: rgb(89, 89, 89)}");
            currentMem = 0;
            buildMemory(level);
        }
    }
    else{
        QMessageBox msgb;
        msgb.setText("Lose!");
        msgb.exec();
        if (level > 1) level--;
        currentMem = 0;
        initGame();
    }
}
void Matrix::timerAlarm()
{
    QVector<QPushButton*> buttons = {ui->pushButton_0, ui->pushButton_1, ui->pushButton_2,
                                      ui->pushButton_3, ui->pushButton_4, ui->pushButton_5,
                                      ui->pushButton_6, ui->pushButton_7, ui->pushButton_8};
    if (currentBtn == memory.size()){
        buttons[memory[currentBtn-1].first]->setStyleSheet("QPushButton {background-color: rgb(89, 89, 89)}");
        currentBtn = 0;
        activeGame = true;
        timer->stop();
        return;
    }

    DrawBtn(buttons[memory[currentBtn].first], memory[currentBtn].second);
    if (currentBtn > 0) buttons[memory[currentBtn-1].first]->setStyleSheet("QPushButton {background-color: rgb(89, 89, 89)}");
    currentBtn++;
}

void Matrix::initGame()
{
    activeGame = false;

    currentMem = 0;
    memory.clear();
    buildMemory(level);
}

void Matrix::buildMemory(size_t level)
{
    timer->setInterval(Del);
    activeGame = false;
    QVector<QColor> colors = {Qt::red, Qt::blue, Qt::green, Qt::black, Qt::yellow, Qt::magenta, Qt::cyan};
    QVector<QPushButton*> buttons = {ui->pushButton_0, ui->pushButton_1, ui->pushButton_2,
                                    ui->pushButton_3, ui->pushButton_4, ui->pushButton_5,
                                    ui->pushButton_6, ui->pushButton_7, ui->pushButton_8};
    for (auto i : buttons) i->setStyleSheet("QPushButton {background-color: rgb(89, 89, 89)}");
    ui->lineEdit->setText(QString::number(level));

    memory.clear();
    size_t temp1 = QRandomGenerator::global()->bounded(0, buttons.size());
    size_t temp2 = QRandomGenerator::global()->bounded(0, colors.size());
    memory.push_back(QPair<size_t, QColor>(temp1, colors[temp2]));

    for (size_t i = 1; i < level+1; i++){
        temp1 = QRandomGenerator::global()->bounded(0, buttons.size());
        temp2 = QRandomGenerator::global()->bounded(0, colors.size());
        if (memory[i-1].second==colors[temp2] ){
            temp2 = (temp2+1)%colors.size();
        }
        if (memory[i-1].first==temp1){
            temp1 = (temp1+1)%buttons.size();
        }
        memory.push_back(QPair<size_t, QColor>(temp1, colors[temp2]));
    }
    timer->start();

}

void Matrix::delay(int ms)
{
    QEventLoop loop;
    QTimer::singleShot(ms, &loop, SLOT(quit()));
    loop.exec();
}

void Matrix::setRecord(size_t record) const
{
    std::ifstream fin("data.txt");
    std::ofstream fout("tempdata.txt");
    if (!fout.is_open()) qDebug() << "error!";
    size_t i = 1;
    std::string temp;
    while(!fin.eof()){
        getline(fin, temp);
        if (i == user){
            temp.pop_back();
            temp += QString::number(record).toStdString();
            fout << temp << "\n";

        }
        else{
            fout << temp << "\n";
        }
        i++;
    }
    fin.close();
    fout.close();
    fout.open("data.txt");
    fin.open("tempdata.txt");
    while(!fin.eof()){
        getline(fin, temp);
        fout << temp << "\n";
    }
    fin.close();
    fout.close();
}

void Matrix::DrawBtn(QPushButton *btn, QColor color)
{
     QString str = "QPushButton {background-color: " + color.name() + "}";
     btn->setStyleSheet(str);
}

void Matrix::on_pushButtonExit_clicked()
{
    this->~Matrix();
    this->close();
}


void Matrix::on_pushButtonPar_clicked()
{
    par = new Parameters(Delay);
    par->show();
}

