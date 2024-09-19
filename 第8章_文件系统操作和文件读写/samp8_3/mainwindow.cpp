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
    file_name = QFileDialog::getOpenFileName(this, "选择一个文件", cur_path, "流数据文件(*.stream)");
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
    QFile file_device(file_name);
    if(!file_device.open(QIODevice::WriteOnly))
        return;

    QDataStream file_stream(&file_device);
    file_stream.setVersion(QDataStream::Qt_6_2);
    if ( ui->rbt_byt_order_bigEndian->isChecked())
        file_stream.setByteOrder(QDataStream::BigEndian);
    else
        file_stream.setByteOrder(QDataStream::LittleEndian);
    if ( ui->rbt_float_precision->isChecked())
        file_stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    else
        file_stream.setFloatingPointPrecision(QDataStream::DoublePrecision);
    file_stream << value;
    file_device.close();
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
    QString str = ui->lineEdit_14->text();
    writeByStream(str.toLatin1().data());
}


void MainWindow::on_pushButton_18_clicked()
{
    auto value = ui->lineEdit_15->text();
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
    if (!QFile::exists(file_name))
    {
        QMessageBox::critical(this, "错误", "文件不存在, 文件名: \n" + file_name);
        return;
    }
    QFile file_device(file_name);
    if(!file_device.open(QIODevice::ReadOnly))
        return;
    QDataStream file_stream(&file_device);
    file_stream.setVersion(QDataStream::Qt_6_2);
    if(ui->rbt_byt_order_bigEndian->isChecked())
        file_stream.setByteOrder(QDataStream::BigEndian);
    else
        file_stream.setByteOrder(QDataStream::LittleEndian);
    if ( ui->rbt_float_precision->isChecked())
        file_stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    else
        file_stream.setFloatingPointPrecision(QDataStream::DoublePrecision);
    file_stream >> value;
    file_device.close();
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
    readByStream(value);
    ui->lineEdit_10->setText(QString(value));
}


void MainWindow::on_pushButton_23_clicked()
{
    QString value;
    readByStream(value);
    ui->lineEdit_13->setText(value);
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
    qDebug() << "QColor 类型为: " << typeid(color).name();
    readByStream(color);
    auto plet = ui->lineEdit_16->palette();
    plet.setColor(QPalette::Text, color);
    ui->lineEdit_16->setPalette(plet);
}


void MainWindow::on_act_write_file_continuous_triggered()
{
    QFile file_device(file_name);
    if(!file_device.open(QIODevice::WriteOnly))
        return;
    QDataStream file_stream(&file_device);
    file_stream.setVersion(QDataStream::Qt_6_2);
    if(ui->rbt_byt_order_bigEndian->isChecked())
        file_stream.setByteOrder(QDataStream::BigEndian);
    else
        file_stream.setByteOrder(QDataStream::LittleEndian);
    if ( ui->rbt_float_precision->isChecked())
        file_stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    else
        file_stream.setFloatingPointPrecision(QDataStream::DoublePrecision);

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
    // auto c_str = str.toLatin1().data(); // 这种方式不能正确运行
    // 方式1
    auto str_data = str.toLatin1();
    auto c_str = str_data.data();
    // 方式2
    // char c_str[10];
    // std::strcpy(c_str, str.toLatin1().data());

    auto str_v = ui->lineEdit_15->text();

    auto font = ui->pushButton_29->font();

    auto plet = ui->pushButton_30->palette();
    auto color = plet.buttonText().color();

    file_stream << q8 << qu8 << q16 << qu16 << q32 << q64 << bool_v << qf16 << float_v << double_v << /* str.toLatin1().data() /* 方式3 **/ c_str << str_v << font << color;
    file_device.close();
    QMessageBox::information(this, "消息", "数据连续写入文件完成");
}


void MainWindow::on_act_read_file__continuous_triggered()
{
    if(!QFile::exists(file_name))
    {
        QMessageBox::critical(this, "错误", "文件不存在, 文件名: \n" + file_name);
        return;
    }
    QFile file_device(file_name);
    if(!file_device.open(QIODevice::ReadOnly))
        return;
    QDataStream file_stream(&file_device);
    file_stream.setVersion(QDataStream::Qt_6_2);
    if(ui->rbt_byt_order_bigEndian->isChecked())
        file_stream.setByteOrder(QDataStream::BigEndian);
    else
        file_stream.setByteOrder(QDataStream::LittleEndian);
    if ( ui->rbt_float_precision->isChecked())
        file_stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    else
        file_stream.setFloatingPointPrecision(QDataStream::DoublePrecision);

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
    char* c_str;
    QString qstr_v;
    QFont font;
    QColor color;

    file_stream.startTransaction();
    file_stream >> q8 >> qu8 >> q16 >> qu16 >> q32 >> q64 >> bool_v >> qf16 >> float_v >> double_v >> c_str >> qstr_v >> font >> color;

    file_device.close();

    if(!file_stream.commitTransaction())
    {
        QMessageBox::critical(this, "错误", "文件读取过程出错, 请检查文件格式");
        return;
    }

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
    ui->lineEdit_10->setText(QString(c_str));
    ui->lineEdit_13->setText(qstr_v);
    ui->lineEdit_11->setFont(font);
    auto plet = ui->lineEdit_16->palette();
    plet.setColor(QPalette::Text, color);
    ui->lineEdit_16->setPalette(plet);

    QMessageBox::information(this,"消息", "从文件连续读取数据完成.");
}

