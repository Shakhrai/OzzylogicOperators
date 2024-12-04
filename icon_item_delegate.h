#ifndef ICONITEMDELEGATE_H
#define ICONITEMDELEGATE_H

#include <QIcon>
#include <QStyledItemDelegate>

class IconItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit IconItemDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // ICONITEMDELEGATE_H
