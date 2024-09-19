#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setTabsClosable(false);      // 不允许关闭分页
    ui->tabWidget->setDocumentMode(true);       // 设置为文档模式
    this->setCentralWidget(ui->tabWidget);      // 将窗口主界面设置为 ui->tabWidget
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_act_qfile_open_triggered()
{
    auto cur_path = QDir::currentPath();
    QString dlg_title = "打开一个文件";
    QString filter = "程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)";
    auto file_name = QFileDialog::getOpenFileName(this, dlg_title,cur_path, filter);
    if(file_name.isEmpty())
        return;
    QFileInfo file_info(file_name);
    QDir::setCurrent(file_info.absolutePath());
    openByIOWhole(file_name);
    // openByIOLines(file_name);
}

bool MainWindow::openByIOWhole(const QString &file_name)
{
    QFile file(file_name);
    if(!file.exists())
        return false;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    auto all_lines = file.readAll();
    QString text(all_lines);
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(text);
    file.close();
    ui->tabWidget->setCurrentIndex(0);
    return true;
}

bool MainWindow::openByIOLines(const QString &file_name)
{
    QFile file;
    file.setFileName(file_name);
    if(!file.exists())
        return false;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    ui->plainTextEdit->clear();
    while(!file.atEnd())
    {
        auto line = file.readLine();
        QString str = QString::fromUtf8(line);
        ui->plainTextEdit->appendPlainText(str);
    }
    file.close();
    ui->tabWidget->setCurrentIndex(0);
    return true;
}

bool MainWindow::saveByIO_Whole(const QString &file_name)
{
    QFile file(file_name);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
         return false;
    auto str = ui->plainTextEdit->toPlainText();
    auto str_bytes = str.toUtf8();
    file.write(str_bytes, str_bytes.length());
    file.close();
    ui->tabWidget->setCurrentIndex(0);
    return true;
}

bool MainWindow::saveByIOSafe(const QString &file_name)
{
    QSaveFile file(file_name);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    file.setDirectWriteFallback(false);             // 不直接修改文件, 使用中间文件进行缓存, 当文件正确的被写入后再将中间文件输出为目标文件
    try
    {
        auto str = ui->plainTextEdit->toPlainText();
        auto str_bytes = str.toUtf8();
        file.write(str_bytes, str_bytes.length());  // 数据读写到中间文件中
        file.commit();                              // 正确读写后 提交
        ui->tabWidget->setCurrentIndex(0);
        return true;
    }
    catch (QException &e)
    {
        qDebug("保存文件的过程中发生错误");
        file.cancelWriting();                       // 错误读写后 取消
        return false;
    }
}

bool MainWindow::openByStreamWhole(const QString &file_name)
{
    QFile file(file_name);
    if(!file.exists())
        return false;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream stream(&file);                      //使用 文本流 读取文件内容
    stream.setAutoDetectUnicode(true);              // 自动检测 编码字符集
    auto str = stream.readAll();
    ui->plainTextEdit_2->setPlainText(str);
    file.close();
    ui->tabWidget->setCurrentIndex(1);
    return true;
}

bool MainWindow::openByStreamLines(const QString &file_name)
{
    QFile file(file_name);
    if(!file.exists())
        return false;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream stream(&file);                      //使用 文本流 读取文件内容
    stream.setAutoDetectUnicode(true);              // 自动检测 编码字符集
    while(!stream.atEnd())
    {
        auto str = stream.readLine();
        ui->plainTextEdit_2->appendPlainText(str);
    }
    file.close();
    ui->tabWidget->setCurrentIndex(1);
    return true;
}

bool MainWindow::saveByStreamSafe(const QString &file_name)
{
    QSaveFile file(file_name);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    try
    {
        QTextStream stream(&file);
        stream.setAutoDetectUnicode(true);
        auto *doc = ui->plainTextEdit_2->document();        // 获取文本编辑器所有内容
        auto cnt = doc->blockCount();                       // 块的个数
        for (int i = 0; i < cnt; i++)                       // 一块一块的将内容写入
        {
            auto text_line = doc->findBlockByNumber(i);
            auto str = text_line.text();
            stream << str << "\n";
        }
        file.commit();
        return true;
    }
    catch(QException &e)
    {
        qDebug("保存文件的过程中发生错误");
        file.cancelWriting();
        return false;
    }
}

bool MainWindow::saveByStreamWhole(const QString &file_name)
{
    QFile file(file_name);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream stream(&file);
    stream.setAutoDetectUnicode(true);
    auto str = ui->plainTextEdit_2->toPlainText();
    stream << str;
    return true;
}


void MainWindow::on_act_qfile_save_as_triggered()
{
    auto cur_path = QDir::currentPath();
    QString dlg_title = "另存为一个文件";
    QString filter = "h文件(*.h);;C++文件(*.cpp);;文本文件(*.txt);;所有文件(*.*)";
    auto file_name = QFileDialog::getSaveFileName(this, dlg_title, cur_path, filter);
    if(file_name.isEmpty())
        return;
    QFileInfo file_info(file_name);
    QDir::setCurrent(file_info.absoluteFilePath());
    saveByIO_Whole(file_name);
}


void MainWindow::on_act_qsavefile_save_as_triggered()
{
    auto cur_path = QDir::currentPath();
    QString dlg_title = "另存为一个文件";
    QString filter = "h文件(*.h);;C++文件(*.cpp);;文本文件(*.txt);;所有文件(*.*)";
    auto file_name = QFileDialog::getSaveFileName(this, dlg_title, cur_path, filter);
    if(file_name.isEmpty())
        return;
    QFileInfo file_info(file_name);
    QDir::setCurrent(file_info.absolutePath());
    saveByIOSafe(file_name);
}


void MainWindow::on_act_qtextstream_open_triggered()
{
    auto cur_path = QDir::currentPath();
    QString dlg_title = "打开一个文件";
    QString filter = "程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)";
    auto file_name = QFileDialog::getOpenFileName(this, dlg_title, cur_path, filter);
    if(file_name.isEmpty())
        return;
    QFileInfo file_info(file_name);
    QDir::setCurrent(file_info.absolutePath());
    // openByStreamWhole(file_name);
    openByStreamLines(file_name);
}


void MainWindow::on_act_qtextstream_save_as_triggered()
{
    auto cur_path = QDir::currentPath();
    QString dlg_title = "另存为一个文件";
    QString filter = "h文件(*.h);;C++文件(*.cpp);;文本文件(*.txt);;所有文件(*.*)";
    auto file_name = QFileDialog::getSaveFileName(this, dlg_title, cur_path, filter);
    if(file_name.isEmpty())
        return;
    QFileInfo file_info(file_name);
    QDir::setCurrent(file_info.absolutePath());
    saveByStreamSafe(file_name);
    // saveByStreamWhole(file_name);
}

