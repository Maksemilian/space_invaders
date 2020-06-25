#ifndef PIXMAPITEM_H
#define PIXMAPITEM_H

#include <QGraphicsObject>

class PixmapItem:public QGraphicsObject
{
public:
    PixmapItem(const QString &fileName,QGraphicsItem*parent=nullptr);
    QRectF boundingRect()const override;
    void paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget);
    QSize size();
private:
    QPixmap pix;
};

#endif // PIXMAPITEM_H
