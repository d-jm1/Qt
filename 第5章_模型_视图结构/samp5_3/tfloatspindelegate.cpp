#include "tfloatspindelegate.h"

TFloatSpinDelegate::TFloatSpinDelegate(QObject *parent): QStyledItemDelegate(parent){}

QWidget *TFloatSpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    auto editor = new QDoubleSpinBox(parent);
    editor->setFrame(false);
    editor->setMinimum(0);
    editor->setMaximum(20000);
    editor->setDecimals(2);
    return editor;
}

void TFloatSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto value = index.model()->data(index, Qt::EditRole).toFloat();
    auto spin_box = static_cast<QDoubleSpinBox*>(editor);
    spin_box->setValue(value);
}

void TFloatSpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto spin_box = static_cast<QDoubleSpinBox*>(editor);
    model->setData(index, QString::number(spin_box->value(), 'f', 2));
}

void TFloatSpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
