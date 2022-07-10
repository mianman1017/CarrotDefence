#include "myobject.h"

myobject::myobject(QPoint _startpos,QPoint _targetpos,QString fileName)
    : QObject{0},pixmap(fileName)
{
    this->currentpos=_startpos;
    this->startpos=_startpos;
    this->targetpos=_targetpos;
    size=40;
    bullet_effect=0;
    monster_effect=0;
    ifmonster=0;
}

void myobject::draw(QPainter *painter)
{
    painter->drawPixmap(currentpos.x(),currentpos.y(),size,size,pixmap);
    //绘制怪物血条
    if(ifmonster==1)
    {
        QBrush red_brush( QColor("#F20900") );//把刷子设置为红色
        painter->setBrush(red_brush);//应用刷子
        float rate = 1.0*now_hp/hp;//计算比例
        painter->drawRect(currentpos.x(),currentpos.y()-5,rate*40,40*0.15);//绘制矩形
    }

}

void myobject::move()
{
    //0.7秒静止效果
    if(monster_effect>=1&&monster_effect<7)
    {
        speed=0;
        monster_effect++;
    }
    if(monster_effect==7)
    {
        speed=1.0;
        monster_effect=0;
    }

    QVector2D vector(targetpos-currentpos);
    vector.normalize();
    currentpos=currentpos+vector.toPoint()*speed;

}
