#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include <QSpinBox>
#include <QFontComboBox>
#include <QActionGroup>
#include <QTextCharFormat>
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void buildUI();
    void buildSignalSlots();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel *status_label_file;          // 状态栏左侧文件提示
    QLabel *status_label_font_family;         // 状态栏字体提示
    QProgressBar *status_bar;           // 状态栏进度条
    QSpinBox *tool_font_size;           // 工具栏 字体大小设置
    QFontComboBox *tool_font_family;    // 工具栏 字体设置
    QActionGroup *tool_language_group;       // 实现语言的互斥选择
private slots:
    void do_font_size_changed(int font_size);
    void do_font_family_changed(const QFont &font);
};
#endif // MAINWINDOW_H
