#include "gamnashkaitem.h"
#include <QPainter>
#include <QApplication>
#include <QPixmap>
#include <QDebug>

QRectF GamnashkaItem::boundingRect() const
{
    const QPointF ptPosition(0, 0);
    const QSizeF size(60, 60);
    return QRectF(ptPosition, size);
}

void GamnashkaItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->save();
    const QPixmap pixmap(":/gamnashka");
    painter->drawPixmap(0, 0, 60, 60, pixmap);
    const QColor color = wasPressed ? QColor{Qt::red} : QColor{Qt::white};
    painter->setPen(QPen{color, 3});
    painter->drawRect(boundingRect());
    painter->restore();
}

void GamnashkaItem::mousePressEvent(QGraphicsSceneMouseEvent *pe)
{
    QApplication::setOverrideCursor(Qt::PointingHandCursor);
    QGraphicsItem::mousePressEvent(pe);
    wasPressed = !wasPressed;
    emit itemWasPressed();
}

void GamnashkaItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *pe)
{
    QApplication::restoreOverrideCursor();
    QGraphicsItem::mouseReleaseEvent(pe);
}

QVariant GamnashkaItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange )
    {
        QPointF newPos = value.toPointF();
        qDebug() << "pos: " << newPos;
    }
    return QGraphicsItem::itemChange(change, value);
}
