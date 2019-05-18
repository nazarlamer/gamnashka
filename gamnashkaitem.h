#ifndef GAMNASHKAITEM_H
#define GAMNASHKAITEM_H

#include <QGraphicsObject>
#include <QObject>

class GamnashkaItem : public QGraphicsObject
{
    Q_OBJECT

    // QGraphicsItem interface
protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* pe) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* pe) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

signals:
    void itemWasPressed();

private:
    bool wasPressed{ false };
};

#endif // GAMNASHKAITEM_H
