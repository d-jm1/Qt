#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
public:
    QCheckBox *chk_under;
    QCheckBox *chk_ita;
    QCheckBox *chk_bold;
    QRadioButton *radio_black;
    QRadioButton *radio_blue;
    QRadioButton *radio_red;
    QPushButton *btn_clear;
    QPushButton *btn_OK;
    QPushButton *btn_quit;
    QPlainTextEdit *plt;
    void init_ui();
    void init_signal_slots();
private slots:
    void do_chk_under(bool flag);
    void do_chk_ita(bool flag);
    void do_chk_bold(bool flag);
    void do_radio_color();
};
#endif // DIALOG_H
