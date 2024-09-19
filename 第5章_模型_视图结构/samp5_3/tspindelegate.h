#ifndef TSPINDELEGATE_H
#define TSPINDELEGATE_H

#include <QStyledItemDelegate>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>

class TSpinDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TSpinDelegate(QObject *parent = nullptr);


    // QAbstractItemDelegate interface
public:
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // TFLOATSPINDELEGATE_H
