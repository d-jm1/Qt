#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // 定义 并创建应用程序
    Widget w;                   // 定义并创建窗口对象
    w.show();                   // 显示窗口
    return a.exec();            // 运行应用程序, 开始进入应用的消息循环和事件处理
}
