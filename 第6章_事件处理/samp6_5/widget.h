#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QAbstractItemView>
#include <QEvent>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

private:
    int getDropActionIndex(Qt::DropAction actionType);
    Qt::DropAction getDropActionType(int index);
    void refreshToUI(QGroupBox * cur_group_box);

    // QObject interface
public:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_rbt_list_source_clicked();

    void on_rbt_list_widget_clicked();

    void on_tbt_tree_widget_clicked();

    void on_rbt_table_widget_clicked();

    void on_chk_accept_drops_clicked(bool checked);

    void on_chk_drag_enable_clicked(bool checked);

    void on_comboBox_drag_drop_mode_currentIndexChanged(int index);

    void on_comboBox_default_drop_act_currentIndexChanged(int index);

private:
    Ui::Widget *ui;
    QAbstractItemView *m_item_view = nullptr;
};
#endif // WIDGET_H
