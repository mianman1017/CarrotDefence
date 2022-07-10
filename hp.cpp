#include "hp.h"
#include <QPushButton>
#include<lose.h>
hp1::hp1(scene1*parent):QPushButton(parent)
{
    nowhp=5;
    father=parent;
    hp_pic=new QPixmap(":/health/images/hp5.png");
    setCheckable(true);
    this->setFlat(true);
    this->setFixedSize(hp_pic->size());
    this->setStyleSheet("QPushButton{Border:Opx;}");
    this->setIcon(*hp_pic);
    this->setIconSize(QSize(hp_pic->size()));
    this->move(738,122);//位置
    this->show();
}
void hp1::hurt(){
    nowhp--;
}
void hp1::setpic(){//0时弹出失败窗口
    switch(nowhp){
    case 1:{hp_pic->load(":/health/images/hp1.png");break;}
    case 2:{hp_pic->load(":/health/images/hp2.png");break;}
    case 3:{hp_pic->load(":/health/images/hp3.png");break;}
    case 4:{hp_pic->load(":/health/images/hp4.png");break;}
    case 5:{hp_pic->load(":/health/images/hp5.png");break;}
    }
    setCheckable(true);
    this->setFlat(true);
    this->setFocusPolicy(Qt::NoFocus);
    this->setFixedSize(hp_pic->size());
    this->setStyleSheet("QPushButton{Border:Opx;}");
    this->setIcon(*hp_pic);
    this->setIconSize(QSize(hp_pic->size()));
    this->move(738,122);//位置
    this->show();
}
bool hp1::ifdead(){
    if(nowhp==0){
        return true;
    }
    else{return false;}
}
hp2::hp2(scene2*parent):QPushButton(parent)
{
    nowhp=5;
    father=parent;
    hp_pic=new QPixmap(":/health/images/hp5.png");
    setCheckable(true);
    this->setFlat(true);
    this->setFixedSize(hp_pic->size());
    this->setStyleSheet("QPushButton{Border:Opx;}");
    this->setIcon(*hp_pic);
    this->setIconSize(QSize(hp_pic->size()));
    this->move(540,370);//位置
    this->show();
}
void hp2::hurt(){
    nowhp--;
}
void hp2::setpic(){//0时弹出失败窗口
    switch(nowhp){
    case 1:{hp_pic->load(":/health/images/hp1.png");break;}
    case 2:{hp_pic->load(":/health/images/hp2.png");break;}
    case 3:{hp_pic->load(":/health/images/hp3.png");break;}
    case 4:{hp_pic->load(":/health/images/hp4.png");break;}
    case 5:{hp_pic->load(":/health/images/hp5.png");break;}
    }
    setCheckable(true);
    this->setFlat(true);
    this->setFocusPolicy(Qt::NoFocus);
    this->setFixedSize(hp_pic->size());
    this->setStyleSheet("QPushButton{Border:Opx;}");
    this->setIcon(*hp_pic);
    this->setIconSize(QSize(hp_pic->size()));
    this->move(540,370);//位置
    this->show();
}
bool hp2::ifdead(){
    if(nowhp==0){
        return true;
    }
    else{return false;}
}
hp3::hp3(scene3*parent):QPushButton(parent)
{
    nowhp=5;
    father=parent;
    hp_pic=new QPixmap(":/health/images/hp5.png");
    setCheckable(true);
    this->setFlat(true);
    this->setFixedSize(hp_pic->size());
    this->setStyleSheet("QPushButton{Border:Opx;}");
    this->setIcon(*hp_pic);
    this->setIconSize(QSize(hp_pic->size()));
    this->move(740,180);//位置
    this->show();
}
void hp3::hurt(){
    nowhp--;
}
void hp3::setpic(){
    switch(nowhp){
    case 1:{hp_pic->load(":/health/images/hp1.png");break;}
    case 2:{hp_pic->load(":/health/images/hp2.png");break;}
    case 3:{hp_pic->load(":/health/images/hp3.png");break;}
    case 4:{hp_pic->load(":/health/images/hp4.png");break;}
    case 5:{hp_pic->load(":/health/images/hp5.png");break;}
    }
    setCheckable(true);
    this->setFlat(true);
    this->setFocusPolicy(Qt::NoFocus);
    this->setFixedSize(hp_pic->size());
    this->setStyleSheet("QPushButton{Border:Opx;}");
    this->setIcon(*hp_pic);
    this->setIconSize(QSize(hp_pic->size()));
    this->move(740,180);//位置
    this->show();
}
bool hp3::ifdead(){
    if(nowhp==0){
        return true;
    }
    else{return false;}
}
