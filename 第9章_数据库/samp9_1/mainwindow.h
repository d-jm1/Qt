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
#include "tcomboboxdelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class TComboBoxDelegate;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void openTable();
    void getFieldNames();
    void showRecordCount();

private slots:
    void do_currentChanged(const QModelIndex& current, const QModelIndex& previous);
    void do_currentRowChanged(const QModelIndex& current, const QModelIndex& previous);
    void on_act_open_db_triggered();

    void on_act_add_triggered();

    void on_act_insert_triggered();

    void on_act_remove_triggered();

    void on_act_submit_triggered();

    void on_act_revert_triggered();

    void on_act_set_photo_triggered();

    void on_act_remove_photo_triggered();

    void on_act_salary_up_triggered();

    void on_comboBox_currentIndexChanged(int index);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase DB;
    QSqlTableModel *table_model;
    QItemSelectionModel *select_model;
    QDataWidgetMapper *data_mapper;
    TComboBoxDelegate delegateSex;
    TComboBoxDelegate delegateDepart;
};
#endif // MAINWINDOW_H
