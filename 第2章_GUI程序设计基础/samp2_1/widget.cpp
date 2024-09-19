#include "widget.h"
#include "./ui_widget.h"        // 通过 widget.ui 生成的文件, 需要被导入来使用 widget.ui 定义的ui界面

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
