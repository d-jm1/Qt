#ifndef DIALOGHEADERS_H
#define DIALOGHEADERS_H

#include <QDialog>
#include <QStringList>
#include <QStringListModel>
#include <QMessageBox>

namespace Ui {
class DialogHeaders;
}

class DialogHeaders : public QDialog
{
    Q_OBJECT

public:
    explicit DialogHeaders(QWidget *parent = nullptr);
    QStringList header();
    void setHeader(QStringList& header);
    ~DialogHeaders();

private:
    Ui::DialogHeaders *ui;
    QStringListModel *m_model;
};

#endif // DIALOGHEADERS_H
