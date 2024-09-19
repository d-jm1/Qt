#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;   // 命名空间 Ui, 包含一个类 Widget(事先声明, 具体定义根据 widget.ui 生成)
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT                                // 宏, 使用 Qt 元对象系统是必须使用的宏, 借此可以使用信号与槽,以及数据等功能

public:
    Widget(QWidget *parent = nullptr);      // 构造函数
    ~Widget();                              // 析构函数

private:
    Ui::Widget *ui;                         // 使用 Ui::Widget 类定义的对象指针
};
#endif // WIDGET_H
