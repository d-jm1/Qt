#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QItemSelectionModel>
#include <QDataWidgetMapper>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlError>
#include <QDataWidgetMapper>
#include <QSqlRecord>
#include <QPixmap>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include "tdialog.h"

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

private:
    void selectData();
    void updateRecord(int record_no);
    void showRecordCount();

private slots:
    void on_act_open_db_triggered();

    void on_act_edit_record_triggered();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_act_insert_triggered();

    void on_act_remove_triggered();

    void on_act_salary_up_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase DB;
    QSqlQueryModel *query_model;
    QItemSelectionModel *select_model;
};
#endif // MAINWINDOW_H
