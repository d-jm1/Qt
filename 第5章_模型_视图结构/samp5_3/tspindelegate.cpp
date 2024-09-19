#include "tspindelegate.h"

TSpinDelegate::TSpinDelegate(QObject *parent): QStyledItemDelegate(parent){}

QWidget *TSpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    auto editor = new QSpinBox(parent);
    editor->setFrame(false);
    editor->setMinimum(0);
    editor->setMaximum(20000);
    return editor;
}

void TSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto value = index.model()->data(index, Qt::EditRole).toInt();
    auto spin_box = static_cast<QSpinBox*>(editor);
    spin_box->setValue(value);
}

void TSpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto spin_box = static_cast<QSpinBox*>(editor);
    model->setData(index, QString::number(spin_box->value()));
}

void TSpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
