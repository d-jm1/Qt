#ifndef DIALOGSIZE_H
#define DIALOGSIZE_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class DialogSize;
}

class DialogSize : public QDialog
{
    Q_OBJECT
public:
    int row();
    int col();
    void setRowCol(int row, int col);
public:
    explicit DialogSize(QWidget *parent = nullptr);
    ~DialogSize();

private:
    Ui::DialogSize *ui;
};

#endif // DIALOGSIZE_H
