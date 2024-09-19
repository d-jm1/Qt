#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    auto palette = ui->pushButton->palette();
    palette.setColor(QPalette::ButtonText, Qt::white);
    ui->pushButton->setPalette(palette);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        auto pos = event->pos();                    // 窗口相对坐标
        auto relate_pos = event->position();        // 相对坐标
        auto win_pos = event->scenePosition();      // 相对坐标
        auto global_pos = event->globalPosition();  // 基于当前显示器的绝对坐标

        auto str = QString::asprintf("pos() = (%d, %d)", pos.x(), pos.y());
        str += QString::asprintf("\nposition() = (%.0f, %.0f)", relate_pos.x(), relate_pos.y());
        str += QString::asprintf("\nscene position() = (%.0f, %.0f)", win_pos.x(), win_pos.y());
        str += QString::asprintf("\nglobal_position() = (%.0f, %.0f)", global_pos.x(), global_pos.y());
        ui->label->setText(str);
        ui->label->adjustSize();
        auto palette = ui->label->palette();
        QColor color = QColor::fromHsl(rand()%360,rand()%156 + 100,rand()%150 + 50);
        palette.setColor(QPalette::WindowText, color);
        ui->label->setPalette(palette);
        ui->label->move(event->pos());
    }
    QWidget::mousePressEvent(event);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    auto pos = ui->pushButton->pos();
    switch(event->key())
    {
    // case Qt::Key_A:
    case Qt::Key_Left:
        if (pos.x() <= 0)
        {
            return; event->ignore();
        }
        pos += QPoint(-20,0); break;
    // case Qt::Key_W:
    case Qt::Key_Up:
        if (pos.y() <= 0)
        {
            return; event->ignore();
        }
        pos += QPoint(0, -20); break;
    // case Qt::Key_D:
    case Qt::Key_Right:
        if(pos.x() >= this->frameGeometry().width())
        {
            return; event->ignore();
        }
        pos += QPoint(20, 0); break;
    // case Qt::Key_S:
    case Qt::Key_Down:
        if(pos.y() >= this->geometry().height())
        {
            return; event->ignore();
        }
        pos += QPoint(0, 20); break;
    default:
        return;
    }
    ui->pushButton->move(pos);
    event->accept();
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/pic/images/独显默认.png"));
    // QWidget::paintEvent(event);
}

void Widget::closeEvent(QCloseEvent *event)
{
    QString dlg_title = "消息框";
    QString str_info = "确定要退出吗? ";
    auto result = QMessageBox::question(this, dlg_title, str_info, QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if(result == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

void Widget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "showEvent() 函数被触发";
}

void Widget::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "hideEvent() 函数被触发";
}
