#ifndef TDIALOG_H
#define TDIALOG_H

#include <QDialog>
#include <QSqlRecord>
#include <QFileDialog>

namespace Ui {
class TDialog;
}

class TDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TDialog(QWidget *parent = nullptr);
    ~TDialog();

public:
    void setUpdateRecord(QSqlRecord &record);
    void setInsertRecord(QSqlRecord &record);
    QSqlRecord getRecord();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


private:
    Ui::TDialog *ui;
    QSqlRecord record;
};

#endif // TDIALOG_H
