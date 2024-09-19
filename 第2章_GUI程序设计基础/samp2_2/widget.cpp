#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->radio_black->setChecked(true);
    connect(ui->radio_black,&QRadioButton::clicked, this, &Widget::on_color_changed);
    connect(ui->radio_blue,&QRadioButton::clicked, this, &Widget::on_color_changed);
    connect(ui->radio_red,&QRadioButton::clicked, this, &Widget::on_color_changed);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_chk_under_stateChanged(int arg1)
{
    auto font = ui->plainTextEdit->font();
    font.setUnderline(bool(arg1));
    ui->plainTextEdit->setFont(font);
}


void Widget::on_chk_ita_stateChanged(int arg1)
{
    auto font = ui->plainTextEdit->font();
    font.setItalic(bool(arg1));
    ui->plainTextEdit->setFont(font);
}


void Widget::on_chk_bold_stateChanged(int arg1)
{
    auto font = ui->plainTextEdit->font();
    font.setBold(bool(arg1));
    ui->plainTextEdit->setFont(font);
}

void Widget::on_color_changed()
{
    auto pattle = ui->plainTextEdit->palette();
    if(ui->radio_black->isChecked())
        pattle.setColor(QPalette::Text ,Qt::red);
    if(ui->radio_red->isChecked())
        pattle.setColor(QPalette::Text ,Qt::red);
    if(ui->radio_blue->isChecked())
        pattle.setColor(QPalette::Text ,Qt::blue);
    ui->plainTextEdit->setPalette(pattle);
}

