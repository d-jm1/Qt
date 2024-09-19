#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include "tformdoc.h"
#include "tformtable.h"

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

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;

private slots:
    void do_changeTabTitle(QString title);
    void on_act_embedded_w_triggered();

    void on_act_indepent_w_triggered();

    void on_act_embedded_mw_triggered();

    void on_act_indepent_mw_triggered();

    void on_tabWidget_tabCloseRequested(int index);

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
