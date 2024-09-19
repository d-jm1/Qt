#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileSystemWatcher>
#include <QFile>
#include <QFileInfo>
QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
public slots:
    void do_dir_changed(const QString& path);
    void do_file_changed(const QString& path);
private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

private:
    void showBtnInfo(QObject* btn);         // 显示按钮标题&toptips提示信息

private:
    Ui::Dialog *ui;
    QFileSystemWatcher file_watcher;        // 文件和目录监视
};
#endif // DIALOG_H
