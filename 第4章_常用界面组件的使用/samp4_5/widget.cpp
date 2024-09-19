#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignLeft);
}


void Widget::on_pushButton_2_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignCenter);
}


void Widget::on_pushButton_3_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignRight);
}


void Widget::on_pushButton_6_clicked(bool checked)
{
    auto font = ui->textEdit->font();
    font.setItalic(checked);
    ui->textEdit->setFont(font);
}


void Widget::on_pushButton_4_clicked(bool checked)
{
    auto font = ui->textEdit->font();
    font.setBold(checked);
    ui->textEdit->setFont(font);
}


void Widget::on_pushButton_5_clicked(bool checked)
{
    auto font = ui->textEdit->font();
    font.setUnderline(checked);
    ui->textEdit->setFont(font);
}


void Widget::on_checkBox_clicked(bool checked)
{
    ui->textEdit->setReadOnly(checked);
}


void Widget::on_checkBox_2_clicked(bool checked)
{
    ui->textEdit->setEnabled(checked);
}


void Widget::on_checkBox_3_clicked(bool checked)
{
    ui->textEdit->setClearButtonEnabled(checked);
}

