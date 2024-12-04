#include "icon_item_delegate.h"

#include <QIcon>
#include <QFont>
#include <QPainter>
#include <QModelIndex>
#include <QStyleOptionViewItem>



IconItemDelegate::IconItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void IconItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    painter->save();


    QString text = index.data(Qt::DisplayRole).toString();
    QIcon icon = index.data(Qt::DecorationRole).value<QIcon>();


    QFont font = option.font;


    if (index.parent() == QModelIndex()) {
        font.setBold(true);
    }
    painter->setFont(font);


    QRect rect = option.rect;




    if (!icon.isNull()) {
        QRect iconRect = rect;
        iconRect.setWidth(20);
        iconRect.moveLeft(rect.left() + 5);
        icon.paint(painter, iconRect, Qt::AlignCenter);
        rect.setLeft(iconRect.right() + 5);
    }


    painter->drawText(rect, Qt::AlignVCenter | Qt::AlignLeft, text);


    painter->setPen(QPen(Qt::lightGray));
    painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());

    painter->restore();
}
