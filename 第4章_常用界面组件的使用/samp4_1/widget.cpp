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

void Widget::on_btn_tr_uni_clicked()
{
    auto str = ui->ltxt_str->text();
    if(str.isEmpty())
        return;
    ui->plainTextEdit->clear();
    for(qint16 i = 0; i < str.size(); i++)
    {
        auto ch = str.at(i);
        auto uniCode = ch.unicode();
        QString chStr(ch);
        auto info = chStr + QString::asprintf("\t, Unicode 编码 = 0x%X", uniCode);
        ui->plainTextEdit->appendPlainText(info);
    }
}


void Widget::on_btn_char_clicked()
{
    auto str = ui->ltxt_char->text();
    if (str.isEmpty())
        return;
    auto ch = str[0];
    auto uniCode = ch.unicode();
    QString chStr(ch);
    auto info = chStr + QString::asprintf("\t, Unicode 编码 = 0x%X", uniCode);
    ui->plainTextEdit->appendPlainText(info);

    ui->chk_digit->setChecked(ch.isDigit());
    ui->chk_letter->setChecked(ch.isLetter());
    ui->chk_letter_num->setChecked(ch.isLetterOrNumber());
    ui->chk_upper->setChecked(ch.isUpper());
    ui->chk_lower->setChecked(ch.isLower());
    ui->chk_mark->setChecked(ch.isMark());
    ui->chk_space->setChecked(ch.isSpace());
    ui->chk_symbol->setChecked(ch.isSymbol());
    ui->chk_punct->setChecked(ch.isPunct());
}

