#include "dialogheaders.h"
#include "ui_dialogheaders.h"

DialogHeaders::DialogHeaders(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogHeaders)
{
    ui->setupUi(this);
    m_model = new QStringListModel(this);
    ui->listView->setModel(m_model);
}

QStringList DialogHeaders::header()
{
    return m_model->stringList();
}

void DialogHeaders::setHeader(QStringList &headers)
{
    m_model->setStringList(headers);
}

DialogHeaders::~DialogHeaders()
{
    QMessageBox::information(this, "提示", "DialogHeaders 对话框被删除");
    delete ui;
}
