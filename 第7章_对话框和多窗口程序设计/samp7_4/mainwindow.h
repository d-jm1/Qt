#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include "tformdoc.h"

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
    void on_act_doc_new_triggered();

    void on_act_doc_open_triggered();

    void on_act_mdi_model_triggered(bool checked);

    void on_act_font_triggered();

    void on_act_cut_triggered();

    void on_act_copy_triggered();

    void on_act_paste_triggered();

    void on_act_doc_save_triggered();

    void on_mdiArea_subWindowActivated(QMdiSubWindow *arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
