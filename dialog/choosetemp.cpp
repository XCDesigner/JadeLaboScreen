#include "choosetemp.h"
#include "ui_choosetemp.h"

chooseTemp::chooseTemp(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::chooseTemp)
{
    ui->setupUi(this);
}

chooseTemp::~chooseTemp()
{
    delete ui;
}

void chooseTemp::init(QString str)
{
    int num = str.mid(0,3).toInt();
    switch (num) {
    case 0:
        ui->pushButton_6->setStyleSheet("QPushButton{color: rgb(255, 255, 255);font-weight: bold;\
                                        font-size: 36px;\
                text-align: center;\
        font-family: Barlow;\
        background-image: url(qrc:/image/TempofButton.png);\
border:none;\
    };");
    break;
    case 180:
        ui->pushButton->setStyleSheet("QPushButton{color: rgb(255, 255, 255);font-weight: bold;\
                                      font-size: 36px;\
                text-align: center;\
        font-family: Barlow;\
        background-image: url(qrc:/image/TemponButton.png);\
border:none;\
};");
break;
case 200:
ui->pushButton_2->setStyleSheet("QPushButton{color: rgb(255, 255, 255);font-weight: bold;\
                                font-size: 36px;\
text-align: center;\
font-family: Barlow;\
background-image: url(:/TemponButton.png);\
border:none;\
};");
break;
case 220:
ui->pushButton_3->setStyleSheet("QPushButton{color: rgb(255, 255, 255);font-weight: bold;\
                                font-size: 36px;\
text-align: center;\
font-family: Barlow;\
background-image: url(:/TemponButton.png);\
border:none;\
};");
break;
case 240:
ui->pushButton_4->setStyleSheet("QPushButton{color: rgb(255, 255, 255);font-weight: bold;\
                                font-size: 36px;\
text-align: center;\
font-family: Barlow;\
background-image: url(:/TemponButton.png);\
border:none;\
};");
break;
case 260:
ui->pushButton_5->setStyleSheet("QPushButton{color: rgb(255, 255, 255);font-weight: bold;\
                                font-size: 36px;\
text-align: center;\
font-family: Barlow;\
background-image: url(:/TemponButton.png);\
border:none;\
};");
break;
default:
break;


}
}

void chooseTemp::show()
{
    ret_value.clear();
    QWidget::show();
}

void chooseTemp::on_pushButton_clicked()
{
    emit heatT(ui->pushButton->text());
    ret_value.append("180");
    emit hideWidget();
    this->hide();
}

void chooseTemp::on_pushButton_2_clicked()
{
    emit heatT(ui->pushButton_2->text());
    ret_value.append("200");
    emit hideWidget();
    this->hide();
}

void chooseTemp::on_pushButton_3_clicked()
{
    emit heatT(ui->pushButton_3->text());
    ret_value.append("220");
    emit hideWidget();
    this->hide();
}

void chooseTemp::on_pushButton_4_clicked()
{
    emit heatT(ui->pushButton_4->text());
    ret_value.append("240");
    emit hideWidget();
    this->hide();
}

void chooseTemp::on_pushButton_5_clicked()
{
    emit heatT(ui->pushButton_5->text());
    ret_value.append("260");
    emit hideWidget();
    this->hide();
}

void chooseTemp::on_pushButton_6_clicked()
{
    emit heatT(ui->pushButton_6->text());
    ret_value.append("0");
    emit hideWidget();
    this->hide();
}
