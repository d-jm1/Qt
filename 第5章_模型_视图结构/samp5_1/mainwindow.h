#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

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
    void on_btn_list_recv_clicked();

    void on_btn_list_clear_clicked();

    void on_btn_item_add_clicked();

    void on_btn_item_insert_clicked();

    void on_btn_item_rm_clicked();

    void on_btn_item_up_clicked();

    void on_btn_item_down_clicked();

    void on_btn_list_sort_clicked(bool checked);

    void on_chk_list_editable_clicked(bool checked);

    void on_listView_clicked(const QModelIndex &index);

    void on_btn_plt_show_clicked();

private:
    Ui::MainWindow *ui;
    QStringList m_str_list;         // 保存初始字符串列表内容
    QStringListModel *m_model;      // 模型数据
};
#endif // MAINWINDOW_H
