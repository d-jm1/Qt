#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <typeinfo>
#include <QFontDialog>
#include <QColorDialog>
#include <QMessageBox>
#include <string>
#include <QString>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_31_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_17_clicked();

    void on_act_write_file_continuous_triggered();

    void on_act_read_file__continuous_triggered();

private:
    bool iniWrite();

    bool iniRead();

    void delFileStream();

    template<class T>
    void writeByStream(T value);

    void writeByStream(QByteArray& byte_array);

    template<class T>
    void readByStream(T& value);

    void readByStream(char** byte_array, uint& len);

    // void readByStream(qint64& value);

private:
    Ui::MainWindow *ui;
    QString file_name;
    QFile* file_device;
    QDataStream* file_stream;
};

#endif // MAINWINDOW_H
