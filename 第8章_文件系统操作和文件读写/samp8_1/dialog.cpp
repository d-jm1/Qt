#include "dialog.h"
#include "./ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::do_dir_changed(const QString &path)
{

}

void Dialog::do_file_changed(const QString &path)
{

}

void Dialog::showBtnInfo(QObject *btn)
{
    auto * the_btn = static_cast<QPushButton*>(btn);
    ui->plainTextEdit->appendPlainText(the_btn->text());
    ui->plainTextEdit->appendPlainText(the_btn->toolTip() + "\n");
}

void Dialog::on_pushButton_4_clicked()
{
    showBtnInfo(sender());
    QCoreApplication::setApplicationName("MyApp");
    auto str = QCoreApplication::applicationName();
    ui->plainTextEdit->appendPlainText(str + "\n");
}


void Dialog::on_pushButton_5_clicked()
{
    showBtnInfo(sender());
    QCoreApplication::setOrganizationName("UPC");
    auto str = QCoreApplication::organizationName();
    ui->plainTextEdit->appendPlainText(str + "\n");
}


void Dialog::on_pushButton_6_clicked()
{
    showBtnInfo(sender());
    auto sous = ui->lineEdit->text();
    if(QFile::exists(sous))
    {
        QFile::moveToTrash(sous);
        ui->plainTextEdit->appendPlainText("文件移除到回收站: " + sous + "\n");
    }
    else
        ui->plainTextEdit->appendPlainText("文件不存在\n");
}


void Dialog::on_pushButton_7_clicked()
{
    showBtnInfo(sender());
    auto sous = ui->lineEdit->text();
    QFile file;
    file.setFileName(sous);
    if(file.exists())
        ui->plainTextEdit->appendPlainText(true + "\n");
    else
        ui->plainTextEdit->appendPlainText(false + "\n");
}


void Dialog::on_pushButton_8_clicked()
{
    showBtnInfo(sender());
    auto sous = ui->lineEdit->text();
    QFile file(sous);
    file.remove();
    ui->plainTextEdit->appendPlainText("删除文件: " + sous + "\n");
}


void Dialog::on_pushButton_10_clicked()
{
    showBtnInfo(sender());
    auto sous = ui->lineEdit->text();
    QFileInfo file_info(sous);
    auto new_file = file_info.path() + "/" + file_info.baseName() + ".XYZ";
    QFile::rename(sous, new_file);
    ui->plainTextEdit->appendPlainText("源文件: " + sous);
    ui->plainTextEdit->appendPlainText("重命名为: " + new_file + "\n");
}

