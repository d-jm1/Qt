#include "tmylabel.h"



TMyLabel::TMyLabel(QWidget *parent):QLabel(parent)
{
    this->setAttribute(Qt::WA_Hover, true);
}

bool TMyLabel::event(QEvent *event)
{
    auto palette = this->palette();
    if(event->type() == QEvent::HoverEnter)
        palette.setColor(QPalette::WindowText, Qt::red);
    else if(event->type() == QEvent::HoverLeave)
        palette.setColor(QPalette::WindowText, Qt::black);
    this->setPalette(palette);
    return QLabel::event(event);
}

void TMyLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit doubleClicked();
}
