#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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

private slots:
    void on_chk_under_stateChanged(int arg1);

    void on_chk_ita_stateChanged(int arg1);

    void on_chk_bold_stateChanged(int arg1);
    void on_color_changed();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
