#ifndef TOWER_H
#define TOWER_H

#include "myobject.h"
#include <QObject>
#include <QPoint>
#include <QPixmap>

class tower : public QObject
{
    Q_OBJECT
public:
    tower(QPoint pos,QString towerpixfileName,QString _bulletpixfileName);//参数为位置与图像文件名
    void draw(QPainter *painter);
    QPoint pos;
    QPixmap towerpixmap;
    QString bulletpixfileName;
    myobject *target;
    float angle;//tower旋转角度
    int size;
    int level;//记录等级

signals:

};

#endif // TOWER_H
