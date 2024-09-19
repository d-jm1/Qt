#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QIcon>
#include <QListWidgetItem>
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
    void on_act_init_list_triggered();

    void on_act_clear_list_triggered();

    void on_act_insert_item_triggered();

    void on_act_add_item_triggered();

    void on_act_delete_item_triggered();

    void on_act_select_all_triggered();

    void on_act_select_none_triggered();

    void on_act_select_inverse_triggered();

    void on_toolButton_5_clicked();

    void on_toolButton_6_clicked();

    void on_checkBox_clicked(bool checked);

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_pushButton_2_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

    void on_listWidget_currentTextChanged(const QString &currentText);

    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_listWidget_itemSelectionChanged();

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    void setActionsForButton(); // 工具按钮绑定默认动作
    void createSelectionMenu(); // 为相应的工具按钮创建相应的下拉菜单
};
#endif // MAINWINDOW_H
