#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDataBase>
#include <QSqlRelationalTableModel>
#include <QItemSelectionModel>
#include <QSqlRelationalDelegate>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlRecord>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
void do_currentChanged(const QModelIndex &, const QModelIndex&);
void on_act_open_db_triggered();

void on_act_column_list_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlRelationalTableModel *table_model;
    QItemSelectionModel *select_model;
    void openTable();
};
#endif // MAINWINDOW_H
