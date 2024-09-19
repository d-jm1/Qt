#include "mainwindow.h"
#include "dialoglogin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto dlg_login = new DialogLogin;
    if(dlg_login->exec() == QDialog::Accepted)
    {
        MainWindow w;
        w.show();
        return a.exec();}
    else
        return 0;
}
