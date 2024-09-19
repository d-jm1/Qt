#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QSaveFile>
#include <QException>
#include <QDebug>
#include <QTextBlock>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_act_qfile_open_triggered();

    void on_act_qfile_save_as_triggered();

    /**
     * @brief on_act_qsavefile_save_as_triggered
     * @details Qt 中存在 和 QFile 并列的类 QSaveFile, 它专门用于保存, 当保存出现异常时, 原来的文件不会丢失, 其余和 QFile 相同
     */
    void on_act_qsavefile_save_as_triggered();
    /**
     * @brief on_act_qtextstream_open_triggered
     * @details QTextStream 有 read, readAll, readLine 等函数, 返回值均为 QString
     *      QTextStream 读写的是文本, 使用 `>>` `<<` 时 QTextStream 会自动将其他基本数据类型 转化为 字符串写入文件
     */
    void on_act_qtextstream_open_triggered();
    /**
     * @brief on_act_qtextstream_save_as_triggered
     * @details 使用 QTextStream 另存为
     */
    void on_act_qtextstream_save_as_triggered();

private:
    Ui::MainWindow *ui;
    bool openByIOWhole(const QString& file_name);
    bool openByIOLines(const QString& file_name);
    bool saveByIO_Whole(const QString& file_name);
    bool saveByIOSafe(const QString& file_name);
    bool openByStreamWhole(const QString& file_name);
    bool openByStreamLines(const QString& file_name);
    bool saveByStreamSafe(const QString& file_name);
    bool saveByStreamWhole(const QString& file_name);
};
#endif // MAINWINDOW_H
