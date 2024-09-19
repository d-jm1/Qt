#include "dialogsize.h"
#include "ui_dialogsize.h"

int DialogSize::row()
{
    return ui->spin_row->value();
}

int DialogSize::col()
{
    return ui->spin_col->value();
}

void DialogSize::setRowCol(int row, int col)
{
    ui->spin_col->setValue(col);
    ui->spin_row->setValue(row);
}

DialogSize::DialogSize(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogSize)
{
    ui->setupUi(this);
}

DialogSize::~DialogSize()
{
    QMessageBox::information(this, "提示", "TDialogSize 对话框被删除");
    delete ui;
}
