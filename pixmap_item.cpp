#include "pixmap_item.h"

#include <QPainter>
#include <QRectF>

PixmapItem::PixmapItem(const QString &fileName,QGraphicsItem*parent)
    :QGraphicsObject (parent)
{
    QString fullPath=":images/"+fileName;

    pix=QPixmap(fullPath);
}

QSize PixmapItem::size(){return  pix.size();}
QRectF PixmapItem::boundingRect() const
{
    return  QRectF(QPointF(0,0),pix.size());
}

void PixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(0,0,pix);
//    painter->rotate(90);
}
