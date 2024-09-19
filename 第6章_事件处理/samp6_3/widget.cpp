#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->lab_hover->installEventFilter(this);
    ui->lab_dclick->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->lab_hover){
        switch(event->type())
        {
        case QEvent::Enter:
            ui->lab_hover->setStyleSheet("background-color: rgb(170, 255, 255);");
            break;
        case QEvent::Leave:
            ui->lab_hover->setStyleSheet("");
            ui->lab_hover->setText("靠近我, 点击我");
            break;
        default:
            break;

        }
        ui->lab_hover->adjustSize();
    }
    else if(watched == ui->lab_dclick)
    {
        switch(event->type())
        {
        case QEvent::Enter:
            ui->lab_dclick->setStyleSheet("background-color: rgb(170, 255, 255);");
            break;
        case QEvent::Leave:
            ui->lab_dclick->setStyleSheet("");
            ui->lab_dclick->setText("可点击的标签");
            break;
        case QEvent::MouseButtonDblClick:
            ui->lab_dclick->setText("double clicked");
            break;
        default:
            break;
        }
        ui->lab_dclick->adjustSize();
    }
    return QWidget::eventFilter(watched, event);
}
