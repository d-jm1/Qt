#ifndef TMYLABEL_H
#define TMYLABEL_H

#include <QLabel>
#include <QEvent>

class TMyLabel : public QLabel
{
    Q_OBJECT
public:
    TMyLabel(QWidget* parent);

    // QObject interface
public:
    virtual bool event(QEvent *event) override;

    // QWidget interface
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
signals:
    void doubleClicked();
};

#endif // TMYLABEL_H
