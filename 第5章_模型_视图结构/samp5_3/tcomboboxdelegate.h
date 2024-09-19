#ifndef TCOMBOBOXDELEGATE_H
#define TCOMBOBOXDELEGATE_H

#include <QStyledItemDelegate>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>
#include <QStringList>

class TComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TComboBoxDelegate(QObject *parent = nullptr);


    // QAbstractItemDelegate interface
public:
    void setItems(QStringList items, bool editable);
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
    QStringList m_item_list;
    bool m_editable;
};

#endif // TFLOATSPINDELEGATE_H
