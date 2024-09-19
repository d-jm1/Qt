#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDir>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QProgressDialog>
#include <QElapsedTimer>
#include <QRgb>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btn_std_open_file_clicked();

    void on_btn_std_open_files_clicked();

    void on_btn_std_save_file_clicked();

    void on_btn_std_chose_folder_clicked();

    void on_btn_std_select_color_clicked();

    void on_btn_std_select_font_clicked();

    void on_btn_std_progress_clicked();

    void on_btn_in_chars_clicked();

    void on_btn_in_int_clicked();

    void on_btn_in_float_clicked();

    void on_btn_in_combo_clicked();

    void on_btn_info_q_clicked();

    void on_btn_info_info_clicked();

    void on_btn_info_w_clicked();

    void on_btn_info_critical_clicked();

    void on_btn_info_about_clicked();

    void on_btn_info_aboutQt_clicked();

public slots:
    void do_progress_canceled();
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
