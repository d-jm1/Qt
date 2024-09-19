#ifndef TFORMDOC_H
#define TFORMDOC_H

#include <QWidget>
#include <QToolBar>
#include <QBoxLayout>
#include <QFileDialog>
#include <QFontDialog>

namespace Ui {
class TFormDoc;
}

class TFormDoc : public QWidget
{
    Q_OBJECT

public:
    explicit TFormDoc(QWidget *parent = nullptr);
    void loadFromFile(QString& file_name);
    ~TFormDoc();
signals:
    void titleChanged(const QString &title);
private slots:
    void on_act_open_triggered();

    void on_act_font_triggered();

private:
    Ui::TFormDoc *ui;
};

#endif // TFORMDOC_H
