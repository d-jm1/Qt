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

void Widget::showBoolInfo(QString str, bool CheckValue)
{
    if(CheckValue)
        ui->plainTextEdit->appendPlainText(str + " = true");
    else
        ui->plainTextEdit->appendPlainText(str + " = false");
}

void Widget::on_btn_isnull_isempty_clicked()
{
    ui->plainTextEdit->appendPlainText("\n == isNull()函数测试");
    auto str1 = ui->comboBox_path->currentText();
    auto str2 = ui->comboBox_spacer->currentText();
    ui->plainTextEdit->appendPlainText("QString str1, str2 = """);
    showBoolInfo("str1.isNull()", str1.isNull());
    showBoolInfo("str1.isEmpty()", str1.isEmpty());
    showBoolInfo("/nstr2.isNull()", str2.isNull());
    showBoolInfo("str2.isNull()", str2.isNull());
    str2.clear();
    ui->plainTextEdit->appendPlainText("\nstr2.clear() 后");
    showBoolInfo("/nstr2.isNull()", str2.isNull());
    showBoolInfo("str2.isNull()", str2.isNull());
}

