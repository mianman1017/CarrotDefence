#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>
#include <QPoint>
#include <QVector2D>
#include <QPixmap>
#include <QPainter>

class myobject : public QObject
{
    Q_OBJECT
public:
    myobject(QPoint startpos,QPoint targetpos,QString fileName);
    void draw(QPainter *painter);
    void move();
    QPoint startpos;
    QPoint currentpos;
    QPoint targetpos;
    QPixmap pixmap;
    qreal speed=1.0;
    myobject *lock;//进行子弹与怪物之间的锁定
    int hp;
    int now_hp;
    int size;
    int ifmonster;//判断是否为monster
    int bullet_effect;//0代表没有，1代表减速
    int monster_effect;

signals:

};

#endif // MYOBJECT_H
