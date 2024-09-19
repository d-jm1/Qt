#include "tcomboboxdelegate.h"

TComboBoxDelegate::TComboBoxDelegate(QObject *parent): QStyledItemDelegate(parent) {}

void TComboBoxDelegate::setItems(QStringList items, bool editable)
{
    m_item_list = items;
    m_editable = editable;
}

QWidget *TComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    auto editor = new QComboBox(parent);
    editor->setEditable(m_editable);
    for(auto item: m_item_list)
        editor->addItem(item);
    return editor;
}

void TComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto str = index.model()->data(index, Qt::EditRole).toString();
    auto combo_box = static_cast<QComboBox*>(editor);
    combo_box->setCurrentText(str);
}

void TComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto combo_box = static_cast<QComboBox*>(editor);
    auto str = combo_box->currentText();
    model->setData(index, str);
}

void TComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
