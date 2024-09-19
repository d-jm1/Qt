#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSpinBox>
#include <QPixmap>
#include <QTreeWidgetItem>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    /**
     * @brief buildTreeHeader 初始化 dockwidget中的 treewidget 的 表头
     */
    void buildTreeHeader();
    /**
     * @brief iniTree 初始化目录树
     */
    void iniTree();
    /**
     * @brief addFolderItem
     * @param par_item
     * @param dir_name
     * @details 添加分组节点
     */
    void addFolderItem(QTreeWidgetItem *par_item, QString dir_name);
    /**
     * @brief getFinalFolderName
     * @param full_path_name
     * @return 文件名
     */
    QString getFinalFolderName(const QString& full_path_name);
    /**
     * @brief addImageItem
     * @param par_item
     * @param a_file_name
     */
    void addImageItem(QTreeWidgetItem *par_item, QString a_file_name);
    /**
     * @brief displayImage
     * @param item
     */
    void displayImage(QTreeWidgetItem *item);
    /**
     * @brief changeItemCaption
     * @param item
     */
    void changeItemCaption(QTreeWidgetItem *item);
    /**
     * @brief deleteItem
     * @param par_item
     * @param item
     */
    void deleteItem(QTreeWidgetItem *par_item, QTreeWidgetItem *item);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_act_add_fold_triggered();

    void on_act_add_file_triggered();

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_act_delete_node_triggered();

    void on_act_traversal_node_triggered();

    void on_act_zoom_in_triggered();

    void on_act_zoom_fit_height_triggered();

    void on_act_zoom_real_triggered();

    void on_act_zoom_out_triggered();

    void on_act_window_float_triggered(bool checked);

    void on_act_window_visiable_triggered(bool checked);

    void on_dockWidget_topLevelChanged(bool topLevel);

private:
    Ui::MainWindow *ui;
    enum TreeItemType{itTopItem = 1001, itGroupItem, itImageItem};
    enum TreeColNum{colItem = 0, colItemType, colDate};

    QLabel *lab_status_file_name;
    QLabel *lab_status_node_text;
    QSpinBox *spin_status_ratio;
    QPixmap m_pixmap;
    float m_ratio;
};
#endif // MAINWINDOW_H
