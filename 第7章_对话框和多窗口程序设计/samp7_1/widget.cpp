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

void Widget::on_btn_std_open_file_clicked()
{
    auto cur_path = QDir::currentPath();
    auto dlg_title = "选择一个文件";
    auto filter = "文本文件(*.txt);;图片文件(*.jpg, *.gif, *.png);;所有文件(*.*)";
    auto file_name = QFileDialog::getOpenFileName(this, dlg_title, cur_path, filter);
    if(!file_name.isEmpty())
        ui->plainTextEdit->appendPlainText(file_name);
}


void Widget::on_btn_std_open_files_clicked()
{
    auto cur_path = QDir::currentPath();
    auto dlg_title = "选择多个文件";
    auto filter = "文本文件(*.txt);;图片文件(*.jpg, *.gif, *.png);;所有文件(*.*)";
    auto file_name_list = QFileDialog::getOpenFileNames(this, dlg_title, cur_path, filter);
    if(!file_name_list.isEmpty())
        for(const auto& file_name : file_name_list)
            ui->plainTextEdit->appendPlainText(file_name);
}


void Widget::on_btn_std_save_file_clicked()
{
    auto cur_path = QCoreApplication::applicationDirPath();
    auto dlg_title = "保存文件";
    auto filter = "文本文件(*.txt);;h文件(*.h);;c++文件( *.cpp);;所有文件(*.*)";
    auto file_name = QFileDialog::getSaveFileName(this, dlg_title, cur_path, filter);
    if(!file_name.isEmpty())
            ui->plainTextEdit->appendPlainText(file_name);
}


void Widget::on_btn_std_chose_folder_clicked()
{
    auto cur_path = QCoreApplication::applicationDirPath();
    auto dlg_title = "选择一个目录";
    auto exist_dir_path = QFileDialog::getExistingDirectory(this, dlg_title, cur_path);
    if(!exist_dir_path.isEmpty())
            ui->plainTextEdit->appendPlainText(exist_dir_path);
}


void Widget::on_btn_std_select_color_clicked()
{
    auto palette = ui->plainTextEdit->palette();
    auto init_color = palette.color(QPalette::Text);
    auto color = QColorDialog::getColor(init_color,this,"选择颜色");
    if(color.isValid())
        palette.setColor(QPalette::Text,color);
    ui->plainTextEdit->setPalette(palette);
}


void Widget::on_btn_std_select_font_clicked()
{
    auto font = ui->plainTextEdit->font();
    bool ok = false;
    font = QFontDialog::getFont(&ok, font,this,"选择字体");
    if(ok)
        ui->plainTextEdit->setFont(font);
}


void Widget::on_btn_std_progress_clicked()
{
    auto lab_text = "正在复制文件...";
    auto btn_text = "取消";
    auto min_value = 0, max_value = 200;
    QProgressDialog dlg_progress(lab_text,btn_text,min_value, max_value, this);
    connect(&dlg_progress, &QProgressDialog::canceled, this, &Widget::do_progress_canceled);
    dlg_progress.setWindowTitle("复制文件");
    dlg_progress.setWindowModality(Qt::WindowModal);
    dlg_progress.setAutoReset(true);
    dlg_progress.setAutoClose(true);
    QElapsedTimer ms_counter;
    for(unsigned int i = min_value; i < max_value; i++)
    {
        dlg_progress.setValue(i);
        dlg_progress.setLabelText(QString::asprintf("正在复制文件, 第 %d 个", i));
        ms_counter.start();
        while(true)
            if (ms_counter.elapsed() > 30)
                break;
        if (dlg_progress.wasCanceled())
            break;
    }
}

void Widget::do_progress_canceled()
{
    ui->plainTextEdit->appendPlainText("**进度条对话框被取消了**");
}


void Widget::on_btn_in_chars_clicked()
{
    auto dlg_title = "输入文字对话框";
    auto lab_text = "输入文件名";
    auto ini_text = "新建文件.txt";
    auto echo_mode = QLineEdit::Normal;
    bool ok = false;
    auto text = QInputDialog::getText(this, dlg_title, lab_text, echo_mode, ini_text, &ok);
    if (ok && !text.isEmpty())
        ui->plainTextEdit->appendPlainText(text);
}


void Widget::on_btn_in_int_clicked()
{
    QString dlg_title = "输入整数对话框";
    auto lab_text = "设置文本框字体大小";
    auto default_value = ui->plainTextEdit->font().pointSize();
    auto min_value = 6, max_value = 50, step_value = 1;
    bool ok = false;
    auto font_size = QInputDialog::getInt(this, dlg_title, lab_text, default_value, min_value, max_value, step_value, &ok);
    if (ok)
    {
        dlg_title = "文本框字体大小被设置为: " + QString::number(font_size);
        ui->plainTextEdit->appendPlainText(dlg_title);
        auto font = ui->plainTextEdit->font();
        font.setPointSize(font_size);
        ui->plainTextEdit->setFont(font);
    }
}


void Widget::on_btn_in_float_clicked()
{
    QString dlg_title = "输入浮点数对话框";
    auto lab_text = "输入一个浮点数";
    auto default_value = 3.3;
    auto min_value = 0, max_value = 10000;
    auto decimals = 2;
    bool ok = false;
    auto value = QInputDialog::getDouble(this, dlg_title, lab_text, default_value, min_value, max_value, decimals , &ok);
    if (ok)
    {
        dlg_title = "输入了一个浮点数 " + QString::number(value, 'f', 2);
        ui->plainTextEdit->appendPlainText(dlg_title);
    }
}


void Widget::on_btn_in_combo_clicked()
{
    QStringList items;
    items << "优秀" << "良好" << "合格" << "不合格";
    auto dlg_title = "条目选择框";
    auto lab_text = "请选择级别";
    auto cur_index = 0;
    bool ok = false;
    auto text = QInputDialog::getItem(this, dlg_title, lab_text, items, cur_index, true, &ok);
    if (ok)
        ui->plainTextEdit->appendPlainText(text);
}


void Widget::on_btn_info_q_clicked()
{
    auto dlg_title = "Question 消息框";
    auto lab_text = "文件已被修改, 是否保存修改?";
    auto default_btn = QMessageBox::NoButton;
    auto result = QMessageBox::question(this, dlg_title, lab_text, QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, default_btn);
    switch (result) {
    case QMessageBox::Yes:
        ui->plainTextEdit->appendPlainText("Question 消息框: Yes 被选择");
        break;
    case QMessageBox::No:
        ui->plainTextEdit->appendPlainText("Question 消息框: No 被选择");
        break;
    case QMessageBox::Cancel:
        ui->plainTextEdit->appendPlainText("Question 消息框: Cancel 被选择");
        break;
    default:
        ui->plainTextEdit->appendPlainText("Question 消息框: 无选择");
        break;
    }
}


void Widget::on_btn_info_info_clicked()
{
    auto dlg_title = "information 消息框";
    auto lab_test = "文件已经打开, 请检查";
    QMessageBox::information(this, dlg_title, lab_test, QMessageBox::Ok, QMessageBox::NoButton);
}


void Widget::on_btn_info_w_clicked()
{
    auto dlg_title = "waring 消息框";
    auto lab_test = "文件内容已经被修改";
    QMessageBox::warning(this, dlg_title, lab_test, QMessageBox::Ok, QMessageBox::NoButton);
}


void Widget::on_btn_info_critical_clicked()
{
    auto dlg_title = "critical 消息框";
    auto lab_test = "不明程序访问网络";
    QMessageBox::critical(this, dlg_title, lab_test, QMessageBox::Ok, QMessageBox::NoButton);
}


void Widget::on_btn_info_about_clicked()
{
    auto dlg_title = "about 消息框";
    auto lab_test = "SEGY 文件查看软件 V1.0 \nDesigned by wwb";
    QMessageBox::about(this, dlg_title, lab_test);
}


void Widget::on_btn_info_aboutQt_clicked()
{
    auto dlg_title = "aboutQt 消息框";
    QMessageBox::aboutQt(this, dlg_title);
}

