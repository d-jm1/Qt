#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>
#include <QSettings>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
namespace Ui {
class DialogLogin;
}

class DialogLogin : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLogin(QWidget *parent = nullptr);
    ~DialogLogin();

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void on_btn_ok_clicked();

    void on_btn_cancel_clicked();

private:
    void readSettings();
    void writeSettings();
    QString encrypt(const QString& str);

private:
    Ui::DialogLogin *ui;
    bool moving = false;
    QPoint last_pos;
    QString user = "user";
    QString pwd = "12345";
    int try_count = 0;
};

#endif // DIALOGLOGIN_H
