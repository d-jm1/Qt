#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);
    ui->plainTextEdit->setAcceptDrops(false);
    ui->label->setAcceptDrops(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::dragEnterEvent(QDragEnterEvent *event)
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText("dragEnterEvent 事件 mimeData() -> formats()");
    for(auto format: event->mimeData()->formats())
        ui->plainTextEdit->appendPlainText(format);
    ui->plainTextEdit->appendPlainText("\n dragEnterEvent 事件 mime Data() -> urls()");
    for(auto url: event->mimeData()->urls())
        ui->plainTextEdit->appendPlainText(url.path());
    if(event->mimeData()->hasUrls())
    {
        auto file_name = event->mimeData()->urls().at(0).fileName();
        QFileInfo file_info(file_name);
        auto ext = file_info.suffix().toUpper();
        if (ext == "PNG")
            event->acceptProposedAction();
        else
            event->ignore();
    }
    else
        event->ignore();
}

void Widget::resizeEvent(QResizeEvent *event)
{
    auto size = ui->plainTextEdit->size();
    ui->plainTextEdit->resize(this->width() - 10, size.height());
    ui->label->resize(this->width() - 10, this->height() - size.height() - 20);
    event->accept();
}

void Widget::dropEvent(QDropEvent *event)
{
    auto file_name = event->mimeData()->urls().at(0).path();
    file_name = file_name.right(file_name.length() - 1);
    QPixmap pixmap(file_name);
    ui->label->setPixmap(pixmap);
    event->accept();
}
