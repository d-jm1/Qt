#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QRandomGenerator>
#include <QDate>
#include <QIcon>

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
     * @brief createItemsARow 为某行创建item
     * @param rowNo
     * @param name
     * @param sex
     * @param birth
     * @param nation
     * @param isPM
     * @param score
     */
    void createItemsARow(int row_no, QString name, QString sex, QDate birth, QString nation, bool isPM, int score);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_table_set_header_clicked();

    void on_btn_table_init_clicked();

    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_btn_table_insert_row_clicked();

    void on_btn_table_add_row_clicked();

    void on_btn_table_delete_cur_row_clicked();

    void on_btn_table_fit_height_clicked();

    void on_btn_table_fit_width_clicked();

    void on_chk_table_editable_clicked(bool checked);

    void on_chk_table_show_header_h_clicked(bool checked);

    void on_chk_table_show_header_v_clicked(bool checked);

    void on_chk_table_spaceed_row_bg_clicked(bool checked);

    void on_rbtn_select_cell_clicked();

    void on_rbtn_select_row_clicked();

    void on_btn_table_read_content_to_plt_clicked();

private:
    Ui::MainWindow *ui;
    enum CellType{ctName, ctSex, ctBirth, ctNation, ctPartyM, ctScore};
    enum FileColNum{colName = 0, colSex, colBirth, colNation, colScore, colPartyM};
    QLabel *lab_status_cell_index;
    QLabel *lab_status_cell_type;
    QLabel *lab_status_stud_id;
};
#endif // MAINWINDOW_H
