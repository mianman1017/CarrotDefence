#ifndef SCENE1_H
#define SCENE1_H

#include "tower.h"
#include "myobject.h"
#include <QMainWindow>
#include <QSoundEffect>
#include <QPushButton>
#include<QTimer>

class scene1 : public QMainWindow
{
    Q_OBJECT
public:
    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer3;
    QSoundEffect *sound1;
    QSoundEffect *sound2;
    QSoundEffect *sound3;
    QSoundEffect *sound4;
    QSoundEffect *sound5;
    QPushButton *button1;
    QPushButton *button2;
    explicit scene1(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void setTower(int x,int y,QString towerpixmfileName,QString bulletpixfileName);
    void addmonster();
    void addbullet(QPoint pos1,QPoint pos2,QString bulletpixfileName,myobject *lockedmonster,int size);
    void updatescene();

private:
    QList<tower*> tower_list;//tower列表,便于管理tower
    QList<myobject*> monster_list;//怪物列表
    QList<myobject*> bullet_list;//子弹列表

signals:

};


#endif // SCENE1_H
