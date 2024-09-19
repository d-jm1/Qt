#include "dialoglocate.h"
#include "ui_dialoglocate.h"

DialogLocate::DialogLocate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLocate)
{
    ui->setupUi(this);
}

void DialogLocate::setSpinRange(int cols, int rows)
{
    ui->spin_col->setMaximum(cols - 1);
    ui->spin_row->setMaximum(rows - 1);
}

DialogLocate::~DialogLocate()
{
    delete ui;
}

void DialogLocate::setSpinValue(int col, int row)
{
    ui->spin_col->setValue(col);
    ui->spin_row->setValue(row);
}

void DialogLocate::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit changeActEnable(true);
}

void DialogLocate::showEvent(QShowEvent *event)
{
    event->accept();
    emit changeActEnable(false);
}

void DialogLocate::on_btn_font_clicked()
{
    auto row = ui->spin_row->value();
    auto col = ui->spin_col->value();
    auto text = ui->lineEdit->text();
    emit changeCellText(col, row, text);
    if(ui->chk_row->isChecked())
        ui->spin_row->setValue(1 + ui->spin_row->value());
    if(ui->chk_col->isChecked())
        ui->spin_col->setValue(1 + ui->spin_col->value());
}

