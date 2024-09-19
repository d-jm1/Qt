#include "widget.h"
#include "./ui_widget.h"

int Widget::getDropActionIndex(Qt::DropAction actionType)
{
    switch (actionType)
    {
    case Qt::CopyAction:
        return 0;
    case Qt::MoveAction:
        return 1;
    case Qt::LinkAction:
        return 2;
    case Qt::IgnoreAction:
        return 3;
    default:
        return 0;
    }
}

Qt::DropAction Widget::getDropActionType(int index)
{
    switch (index)
    {
    case 0:
        return Qt::CopyAction;
    case 1:
        return Qt::MoveAction;
    case 2:
        return Qt::LinkAction;
    case 3:
        return Qt::IgnoreAction;
    default:
        return Qt::CopyAction;
    }
}

void Widget::refreshToUI(QGroupBox *cur_group_box)
{
    ui->chk_accept_drops->setChecked(m_item_view->acceptDrops());
    ui->chk_drag_enable->setChecked(m_item_view->dragEnabled());
    ui->comboBox_drag_drop_mode->setCurrentIndex((int)m_item_view->dragDropMode());
    auto index = getDropActionIndex(m_item_view->defaultDropAction());
    ui->comboBox_default_drop_act->setCurrentIndex(index);
    auto font = ui->groupBox_list_source->font();
    font.setBold(false);
    ui->groupBox_list_source->setFont(font);
    ui->groupBox_list_widget->setFont(font);
    ui->groupBox_tree_widget->setFont(font);
    ui->groupBox_table_widget->setFont(font);
    font.setBold(true);
    cur_group_box->setFont(font);
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() != QEvent::KeyPress)
        return QWidget::eventFilter(watched, event);
    auto key = static_cast<QKeyEvent*>(event);
    if (key->key() != Qt::Key_Delete)
        return QWidget::eventFilter(watched, event);

    if (watched == ui->listWidget_source)
    {
        auto item = ui->listWidget_source->takeItem(ui->listWidget_source->currentRow());
        delete item;
    }
    else if (watched == ui->listWidget)
    {
        auto item = ui->listWidget->takeItem(ui->listWidget->currentRow());
        delete item;
    }
    else if (watched == ui->treeWidget)
    {
        auto cur_item = ui->treeWidget->currentItem();
        if (cur_item->parent() != nullptr)
        {
            auto par_item = cur_item->parent();
            par_item->removeChild(cur_item);
        }
        else
        {
            auto index = ui->treeWidget->indexOfTopLevelItem(cur_item);
            ui->treeWidget->takeTopLevelItem(index);
        }
        delete cur_item;
    }
    else if (watched == ui->tableWidget)
    {
        auto item = ui->tableWidget->takeItem(ui->tableWidget->currentRow(), ui->tableWidget->currentColumn());
        delete item;
    }
    return true;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->listWidget_source->installEventFilter(this);
    ui->listWidget->installEventFilter(this);
    ui->treeWidget->installEventFilter(this);
    ui->tableWidget->installEventFilter(this);

    ui->listWidget_source->setAcceptDrops(true);
    ui->listWidget_source->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listWidget_source->setDragEnabled(true);
    ui->listWidget_source->setDefaultDropAction(Qt::CopyAction);

    ui->listWidget->setAcceptDrops(true);
    ui->listWidget->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listWidget->setDragEnabled(true);
    ui->listWidget->setDefaultDropAction(Qt::CopyAction);

    ui->treeWidget->setAcceptDrops(true);
    ui->treeWidget->setDragDropMode(QAbstractItemView::DragDrop);
    ui->treeWidget->setDragEnabled(true);
    ui->treeWidget->setDefaultDropAction(Qt::CopyAction);

    ui->tableWidget->setAcceptDrops(true);
    ui->tableWidget->setDragDropMode(QAbstractItemView::DragDrop);
    ui->tableWidget->setDragEnabled(true);
    ui->tableWidget->setDefaultDropAction(Qt::MoveAction);

    emit ui->rbt_list_source->click();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_rbt_list_source_clicked()
{
    m_item_view = ui->listWidget_source;
    refreshToUI(ui->groupBox_list_source);
}


void Widget::on_rbt_list_widget_clicked()
{
    m_item_view = ui->listWidget;
    refreshToUI(ui->groupBox_list_widget);
}


void Widget::on_tbt_tree_widget_clicked()
{
    m_item_view = ui->treeWidget;
    refreshToUI(ui->groupBox_tree_widget);
}


void Widget::on_rbt_table_widget_clicked()
{
    m_item_view = ui->tableWidget;
    refreshToUI(ui->groupBox_table_widget);
}


void Widget::on_chk_accept_drops_clicked(bool checked)
{
    m_item_view->setAcceptDrops(checked);
}


void Widget::on_chk_drag_enable_clicked(bool checked)
{
    m_item_view->setDragEnabled(checked);
}


void Widget::on_comboBox_drag_drop_mode_currentIndexChanged(int index)
{
    auto mode = (QAbstractItemView::DragDropMode) index;
    m_item_view->setDragDropMode(mode);
}


void Widget::on_comboBox_default_drop_act_currentIndexChanged(int index)
{
    auto act_type = getDropActionType(index);
    m_item_view->setDefaultDropAction(act_type);
}

