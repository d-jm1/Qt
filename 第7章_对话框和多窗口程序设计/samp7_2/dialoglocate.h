#ifndef DIALOGLOCATE_H
#define DIALOGLOCATE_H

#include <QDialog>
#include <QEvent>
#include <QCloseEvent>

namespace Ui {
class DialogLocate;
}

class DialogLocate : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLocate(QWidget *parent = nullptr);
    void setSpinRange(int cols, int rows);
    ~DialogLocate();

public slots:
    void setSpinValue(int col, int row);
    // QWidget interface
protected:
    virtual void closeEvent(QCloseEvent *event) override;
    virtual void showEvent(QShowEvent *event) override;

signals:
    void changeCellText(int col, int row, QString &text);
    void changeActEnable(bool en);
private slots:
    void on_btn_font_clicked();

private:
    Ui::DialogLocate *ui;

};

#endif // DIALOGLOCATE_H
