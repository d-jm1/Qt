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
#include <QSqlQuery>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void selectData();                      // 查询数据
    void refreshTableView();                // 移动记录后刷星 tableView 的选择行

private slots:
    void do_currentRowChanged(const QModelIndex& current, const QModelIndex& previous);
    void on_act_open_db_triggered();       // TODO remove

    void on_act_front_record_triggered();

    void on_act_previous_record_triggered();

    void on_act_next_record_triggered();

    void on_act_back_record_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase DB;
    QSqlQueryModel *query_model;            // 数据模型
    QItemSelectionModel *select_model;      // 选择模型
    QDataWidgetMapper *data_mapper;         // 数据映射
};
#endif // MAINWINDOW_H
