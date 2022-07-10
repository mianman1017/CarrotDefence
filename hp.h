#ifndef HP_H
#define HP_H
#include<QPixmap>
#include<QLabel>
#include"scene1.h"
#include"scene2.h"
#include"scene3.h"
#include<QPushButton>
//scene1中用hp1,scene2中用hp2，scene3中用hp3
class hp1:public QPushButton
{
     Q_OBJECT

private:
    int nowhp;
    scene1* father;
    QPixmap* hp_pic;
public:
    void hurt();//血量-1
    explicit hp1(scene1*parent);
    ~hp1(){
        delete hp_pic;
    }
    bool ifdead();//血量为0返回ture
    void setpic();//根据血量设置并显示血条
};
class hp2:public QPushButton
{
     Q_OBJECT

private:
    int nowhp;
    scene2* father;
    QPixmap* hp_pic;
public:
    void hurt();
    explicit hp2(scene2*parent);
    ~hp2(){
        delete hp_pic;
    }
    bool ifdead();
    void setpic();
};
class hp3:public QPushButton
{
     Q_OBJECT

private:
    int nowhp;
    scene3* father;
    QPixmap* hp_pic;
public:
    void hurt();//血量-1
    explicit hp3(scene3*parent);
    ~hp3(){
        delete hp_pic;
    }
    bool ifdead();//血量为0返回true
    void setpic();//根据当前血量设置并显示血条
};


#endif // HP_H
