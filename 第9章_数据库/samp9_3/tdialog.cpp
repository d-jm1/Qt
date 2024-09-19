#include "tdialog.h"
#include "ui_tdialog.h"

TDialog::TDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TDialog)
{
    ui->setupUi(this);
}

TDialog::~TDialog()
{
    delete ui;
}

void TDialog::setUpdateRecord(QSqlRecord &record)
{
    this->record = record;
    ui->spinBox->setEnabled(false);
    setWindowTitle("更新记录");

    ui->spinBox->setValue(record.value("empNo").toInt());
    ui->lineEdit->setText(record.value("Name").toString());
    ui->comboBox_2->setCurrentText(record.value("Gender").toString());
    ui->dateEdit->setDate(record.value("Birthday").toDate());
    ui->comboBox_4->setCurrentText(record.value("Province").toString());
    ui->comboBox_5->setCurrentText(record.value("Department").toString());
    ui->spinBox_2->setValue(record.value("Salary").toFloat());
    ui->plainTextEdit->setPlainText(record.value("Memo").toString());

    QVariant photo_data = record.value("Photo");
    if(!photo_data.isValid())
        ui->label_2->clear();
    else
    {
        auto photo_byte = photo_data.toByteArray();
        QPixmap photo;
        photo.loadFromData(photo_byte);
        ui->label_2->setPixmap(photo.scaledToWidth(ui->label_2->size().width()));
    }
}

void TDialog::setInsertRecord(QSqlRecord &record)
{
    this->record = record;
    ui->spinBox->setEnabled(true);
    setWindowTitle("插入新纪录");
    ui->spinBox->setValue(record.value("empNo").toInt());
}

QSqlRecord TDialog::getRecord()
{
    record.setValue("empNo", ui->spinBox->value());
    record.setValue("Name", ui->lineEdit->text());
    record.setValue("Gender", ui->comboBox_2->currentText());
    record.setValue("Birthday", ui->dateEdit->date());
    record.setValue("Province", ui->comboBox_4->currentText());
    record.setValue("Department", ui->comboBox_5->currentText());
    record.setValue("Salary", ui->spinBox_2->value());
    record.setValue("Memo", ui->plainTextEdit->toPlainText());
    return record;
}

void TDialog::on_pushButton_clicked()
{
    auto file_name = QFileDialog::getOpenFileName(this, "选择图片文件", "", "照片(*.jpg)");
    if(file_name.isEmpty())
        return;
    QByteArray photo_byte;
    auto file = new QFile(file_name);
    file->open(QIODevice::ReadOnly);
    photo_byte = file->readAll();
    file->close();
    record.setValue("Photo", photo_byte);
    QPixmap pic;
    pic.loadFromData(photo_byte);
    ui->label_2->setPixmap(pic.scaledToWidth(ui->label_2->size().width()));
}


void TDialog::on_pushButton_2_clicked()
{
    ui->label_2->clear();
    record.setNull("Photo");
}
