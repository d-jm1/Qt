#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox_3->setEnabled(false);
    ui->act_write_file_continuous->setEnabled(false);
    ui->act_read_file__continuous->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_31_clicked()
{
    auto cur_path = QDir::currentPath();
    file_name = QFileDialog::getOpenFileName(this, "选择一个文件", cur_path, "流数据文件(*.raw)");
    if (!file_name.isEmpty())
    {
        ui->lineEdit->setText(file_name);
        ui->groupBox_3->setEnabled(true);
        ui->act_write_file_continuous->setEnabled(true);
        ui->act_read_file__continuous->setEnabled(true);
    }
}


template<class T>
void MainWindow::writeByStream(T value)
{
    qDebug() << "写文件函数被调用 --> " << "元素类型为: " << typeid(value).name() << "\t元素类型大小: " << sizeof(T) << "bytes" << "\t 值为: " << value;
    if(iniWrite())
    {
        file_stream->writeRawData((char*)& value, sizeof(T));
        delFileStream();
    }
}

void MainWindow::writeByStream(QByteArray &byte_array)
{
    qDebug() << "<-- 写文件函数(QByteArray 特化)被调用 --> ";
    if(iniWrite())
    {
        file_stream->writeBytes(byte_array, byte_array.length());
        delFileStream();
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    quint16 value = ui->spinBox_3->value();
    writeByStream(value);
}


void MainWindow::on_pushButton_14_clicked()
{
    bool value = ui->checkBox->isChecked();
    writeByStream(value);
}


void MainWindow::on_pushButton_20_clicked()
{
    qfloat16 value = ui->doubleSpinBox_9->value();
    writeByStream(value);
}


void MainWindow::on_pushButton_21_clicked()
{
    float value = ui->doubleSpinBox_12->value();
    writeByStream(value);
}


void MainWindow::on_pushButton_22_clicked()
{
    double value = ui->doubleSpinBox_11->value();
    writeByStream(value);
}


void MainWindow::on_pushButton_25_clicked()
{
    auto str = ui->lineEdit_14->text().toUtf8();
    writeByStream(str);
}


void MainWindow::on_pushButton_18_clicked()
{
    auto value = ui->lineEdit_15->text().toLatin1();
    writeByStream(value);
}


void MainWindow::on_pushButton_29_clicked()
{
    auto font = ui->pushButton_29->font();
    auto ok = false;
    font = QFontDialog::getFont(&ok, font, this);
    if(ok)
        ui->pushButton_29->setFont(font);
}


void MainWindow::on_pushButton_26_clicked()
{
    auto font = ui->pushButton_29->font();
    writeByStream(font);
}


void MainWindow::on_pushButton_30_clicked()
{
    auto plet = ui->pushButton_30->palette();
    auto color = plet.buttonText().color();
    color = QColorDialog::getColor(color);
    if(color.isValid())
    {
        plet.setColor(QPalette::ButtonText, color);
        ui->pushButton_30->setPalette(plet);
    }
}


void MainWindow::on_pushButton_16_clicked()
{
    auto plet = ui->pushButton_30->palette();
    auto color = plet.buttonText().color();
    writeByStream(color);
}

void MainWindow::on_pushButton_11_clicked()
{
    qint64 value = ui->spinBox_6->value();
    writeByStream(value);
}


template<class T>
void MainWindow::readByStream(T &value)
{
    if (!iniRead())
        return;
    file_stream->readRawData((char*)&value, sizeof(T));
    delFileStream();
}

void MainWindow::readByStream(char** byte_array, uint& len)
{
    qDebug() << "<-- 读文件函数(QByteArray 特化)被调用 --> ";
    if (!iniRead())
        return;
    file_stream->readBytes(*byte_array, len);
    delFileStream();
    return;
}

void MainWindow::on_pushButton_12_clicked()
{
    qint64 value;
    readByStream(value);
    ui->lineEdit_7->setText(QString("%1").arg(value));
}


void MainWindow::on_pushButton_13_clicked()
{
    bool value;
    readByStream(value);
    ui->checkBox_2->setChecked(value);
}


void MainWindow::on_pushButton_19_clicked()
{
    qfloat16 value;
    readByStream(value);
    ui->lineEdit_12->setText(QString::asprintf("%.2f", float(value)));
}


void MainWindow::on_pushButton_24_clicked()
{
    float value;
    readByStream(value);
    ui->lineEdit_9->setText(QString::asprintf("%.4f", value));
}


void MainWindow::on_pushButton_15_clicked()
{
    double value;
    readByStream(value);
    ui->lineEdit_8->setText(QString::asprintf("%.4f", value));
}

void MainWindow::on_pushButton_27_clicked()
{
    char* value;
    uint len = 0LL;
    readByStream(&value, len);
    auto str = QString::fromUtf8(value, len);
    delete[] value;
    ui->lineEdit_10->setText(str);
}


void MainWindow::on_pushButton_23_clicked()
{
    char* value;
    uint len = 0LL;
    readByStream(&value, len);
    if(value == nullptr)
        return;
    auto str = QString::fromLatin1(value, len);
    ui->lineEdit_13->setText(str);
    delete[] value;
    auto info = QString("读出缓冲区长度 = %1 (字节)").arg(len);
    QMessageBox::information(this, "信息提示", info);
}


void MainWindow::on_pushButton_28_clicked()
{
    QFont font;
    readByStream(font);
    ui->lineEdit_11->setFont(font);
}


void MainWindow::on_pushButton_17_clicked()
{
    QColor color = Qt::black;
    readByStream(color);
    auto plet = ui->lineEdit_16->palette();
    plet.setColor(QPalette::Text, color);
    ui->lineEdit_16->setPalette(plet);
}


void MainWindow::on_act_write_file_continuous_triggered()
{
    if(!iniWrite())
        return;

    qint8 q8 = ui->spinBox->value();
    quint8 qu8 = ui->spinBox_2->value();
    qint16 q16 = ui->spinBox_3->value();
    quint16 qu16 = ui->spinBox_4->value();
    qint32 q32 = ui->spinBox_5->value();
    qint64 q64 = ui->spinBox_6->value();
    bool bool_v = ui->checkBox->isChecked();
    qfloat16 qf16 = ui->doubleSpinBox_9->value();
    float float_v = ui->doubleSpinBox_12->value();
    double double_v = ui->doubleSpinBox_11->value();

    auto str = ui->lineEdit_14->text();
    auto byte_value = str.toUtf8();

    auto str_v = ui->lineEdit_15->text();
    auto byte_value2= str_v.toLatin1();

    file_stream->writeRawData((char*)&q8, sizeof(decltype(q8)));
    file_stream->writeRawData((char*)&qu8, sizeof(decltype(qu8)));
    file_stream->writeRawData((char*)&q16, sizeof(decltype(q16)));
    file_stream->writeRawData((char*)&qu16, sizeof(decltype(qu16)));
    file_stream->writeRawData((char*)&q32, sizeof(decltype(q32)));
    file_stream->writeRawData((char*)&q64, sizeof(decltype(q64)));
    file_stream->writeRawData((char*)&bool_v, sizeof(decltype(bool_v)));
    file_stream->writeRawData((char*)&qf16, sizeof(decltype(qf16)));
    file_stream->writeRawData((char*)&float_v, sizeof(decltype(float_v)));
    file_stream->writeRawData((char*)&double_v, sizeof(decltype(double_v)));
    file_stream->writeBytes(byte_value, byte_value.length());
    file_stream->writeBytes(byte_value2, byte_value2.length());

    delFileStream();

    QMessageBox::information(this, "消息", "数据连续写入文件完成");
}


void MainWindow::on_act_read_file__continuous_triggered()
{
    if(!iniRead())
        return;

    qint8 q8;
    quint8 qu8;
    qint16 q16;
    quint16 qu16;
    qint32 q32;
    qint64 q64;
    bool bool_v;
    qfloat16 qf16;
    float float_v;
    double double_v;

    char* buf;
    uint len;

    char* buf_v;
    uint len_v;

    file_stream->readRawData((char*)&q8, sizeof(decltype(q8)));
    file_stream->readRawData((char*)&qu8, sizeof(decltype(qu8)));
    file_stream->readRawData((char*)&q16, sizeof(decltype(q16)));
    file_stream->readRawData((char*)&qu16, sizeof(decltype(qu16)));
    file_stream->readRawData((char*)&q32, sizeof(decltype(q32)));
    file_stream->readRawData((char*)&q64, sizeof(decltype(q64)));
    file_stream->readRawData((char*)&bool_v, sizeof(decltype(bool_v)));
    file_stream->readRawData((char*)&qf16, sizeof(decltype(qf16)));
    file_stream->readRawData((char*)&float_v, sizeof(decltype(float_v)));
    file_stream->readRawData((char*)&double_v, sizeof(decltype(double_v)));
    file_stream->readBytes( buf, len);
    file_stream->readBytes( buf_v, len_v);

    delFileStream();

    ui->lineEdit_2->setText(QString("%1").arg(q8));
    ui->lineEdit_3->setText(QString("%1").arg(qu8));
    ui->lineEdit_4->setText(QString("%1").arg(q16));
    ui->lineEdit_5->setText(QString("%1").arg(qu16));
    ui->lineEdit_6->setText(QString("%1").arg(q32));
    ui->lineEdit_7->setText(QString("%1").arg(q64));
    ui->checkBox_2->setChecked(bool_v);
    ui->lineEdit_12->setText(QString::asprintf("%.2f",float(qf16)));
    ui->lineEdit_9->setText(QString::asprintf("%.4f",float_v));
    ui->lineEdit_8->setText(QString::asprintf("%.4f",double_v));

    auto str = QString::fromUtf8(buf, len);
    ui->lineEdit_10->setText(str);

    str = QString::fromLatin1(buf_v, len_v);
    ui->lineEdit_13->setText(str);

    QMessageBox::information(this,"消息", "从文件连续读取数据完成.");
}

bool MainWindow::iniWrite()
{
    file_device = new QFile(file_name);
    if(!file_device->open(QIODevice::WriteOnly))
        return false;
    file_stream = new QDataStream(file_device);
    file_stream->setVersion(QDataStream::Qt_6_2);
    if(ui->rbt_byt_order_bigEndian->isChecked())
        file_stream->setByteOrder(QDataStream::BigEndian);
    else
        file_stream->setByteOrder(QDataStream::LittleEndian);
    if ( ui->rbt_float_precision->isChecked())
        file_stream->setFloatingPointPrecision(QDataStream::SinglePrecision);
    else
        file_stream->setFloatingPointPrecision(QDataStream::DoublePrecision);
    return true;

}

bool MainWindow::iniRead()
{
    if(!QFile::exists(file_name))
    {
        QMessageBox::critical(this, "错误", "文件不存在, 文件名: \n" + file_name);
        return false;
    }
    file_device = new QFile(file_name);
    if(!file_device->open(QIODevice::ReadOnly))
        return false;
    file_stream = new QDataStream(file_device);
    file_stream->setVersion(QDataStream::Qt_6_2);
    if(ui->rbt_byt_order_bigEndian->isChecked())
        file_stream->setByteOrder(QDataStream::BigEndian);
    else
        file_stream->setByteOrder(QDataStream::LittleEndian);
    if ( ui->rbt_float_precision->isChecked())
        file_stream->setFloatingPointPrecision(QDataStream::SinglePrecision);
    else
        file_stream->setFloatingPointPrecision(QDataStream::DoublePrecision);
    return true;
}

void MainWindow::delFileStream()
{
    file_device->close();
    delete file_stream;
    delete file_device;
}


