#ifndef MOVEITEM_H
#define MOVEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

enum item_state {
    IDRAW, IMOVE
};

class MoveItem : public QObject, public QGraphicsItem {
public:
    explicit MoveItem(QObject *parent = 0);

    ~MoveItem() override;

signals:

public:
    QColor item_color;

    item_state state = IDRAW;

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

public slots:
};

#endif // MOVEITEM_H
