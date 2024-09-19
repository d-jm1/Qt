#ifndef TFORMTABLE_H
#define TFORMTABLE_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QItemSelection>
#include <QEvent>
#include <QCloseEvent>
#include <QDialog>
#include <QMessageBox>
#include "dialogsize.h"
#include "dialogheaders.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class FormTable;
}
QT_END_NAMESPACE

class FormTable : public QMainWindow
{
    Q_OBJECT

public:
    FormTable(QWidget *parent = nullptr);
    ~FormTable();

    // QWidget interface
protected:
    virtual void closeEvent(QCloseEvent *event) override;
public slots:
    void do_setCellText(int row, int col, QString &text);
private slots:
    void do_model_currentChanged(const QModelIndex& current, const QModelIndex& previous);

    void on_act_set_list_rows_cols_triggered();

    void on_actionact_set_list_header_triggered();

    void on_tableView_doubleClicked(const QModelIndex &index);

signals:
    void cellIndexChanged(int rows, int cols);
private:
    Ui::FormTable *ui;
    QLabel *lab_cell_pos;
    QLabel *lab_cell_text;
    QStandardItemModel *m_model;
    QItemSelectionModel *m_selection;
    DialogHeaders *dlg_set_headers = nullptr;
};

#endif // MAINWINDOW_H
