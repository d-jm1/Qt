#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QLabel>
#include <QActionGroup>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QFileDialog>
#include <QTextStream>
#include <iostream>
#include <string>
#include <QMessageBox>
#include "tcomboboxdelegate.h"
#include "tspindelegate.h"
#include "tfloatspindelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

#define FixedColumnCount 6

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void initModelData(QStringList &a_file_content);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void do_currentChanged(const QModelIndex& current, const QModelIndex& previous);

    void on_act_open_file_triggered();

    void on_act_add_row_triggered();

    void on_act_insert_row_triggered();

    void on_act_remove_row_triggered();

    void on_act_ali_left_triggered();

    void on_act_ali_right_triggered();

    void on_act_ali_center_triggered();

    void on_act_font_bold_triggered(bool checked);

    void on_act_preview_data_triggered();

    void on_act_save_file_triggered();

private:
    Ui::MainWindow *ui;
    QLabel *lab_cur_file;
    QLabel *lab_cell_pos;
    QLabel *lab_cell_text;
    QStandardItemModel *m_model;
    QItemSelectionModel *m_selection;
    QActionGroup *group_act_ali;
    QString a_file_name;
    TComboBoxDelegate *combo_delegate;
    TFloatSpinDelegate *float_spin_delegate;
    TSpinDelegate *int_spin_delegate;

};
#endif // MAINWINDOW_H
