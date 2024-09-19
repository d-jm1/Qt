#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QTreeView>
#include <QTableView>
#include <QListView>
#include <QFileDialog>
#include <QDebug>

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
    void on_treeView_clicked(const QModelIndex &index);

    void on_act_set_root_floder_triggered();

    void on_rbt_show_folder_files_clicked();

    void on_rbt_show_only_files_clicked();

    void on_chk_file_filt_clicked(bool checked);

    void on_btn_do_filt_clicked();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *m_model;
};
#endif // MAINWINDOW_H
