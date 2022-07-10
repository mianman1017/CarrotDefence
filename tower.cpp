#include "tower.h"
#include <QPainter>
#include <QDebug>

tower::tower(QPoint _pos,QString pixfileName,QString _bulletpixfileName)
    : QObject{0},towerpixmap(pixfileName)
{
    bulletpixfileName=_bulletpixfileName;
    pos=_pos;
    angle=0;
    target=NULL;
    size=30;
    level=1;
}

void tower::draw(QPainter *painter)
{
    painter->translate(pos.x()+20,pos.y()+20);
    painter->rotate(angle);
    painter->translate(-(pos.x()+20),-(pos.y()+20));
    painter->drawPixmap(pos.x(),pos.y(),size,size,towerpixmap);
}//tower旋转
