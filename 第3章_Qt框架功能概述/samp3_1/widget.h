#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "tperson.h"
#include <QMetaProperty>
#include <QMetaClassInfo>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    TPerson *boy;
    TPerson *girl;

private slots:
    void do_ageChanged(int value);
    void do_spinChanged(int arg1);
    void on_btn_mate_info_clicked();
};
#endif // WIDGET_H
