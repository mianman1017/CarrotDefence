#ifndef MONEY_H
#define MONEY_H
#include<QPixmap>
#include<QLabel>
#include"scene1.h"
#include"scene2.h"
#include"scene3.h"
#include<QPushButton>
#define initmoney 180

//三个money类分别在对应数字的scene中使用
class money1:QPushButton
{
     Q_OBJECT
private:
   scene1* father;
   QPixmap* money_pic;
   QPushButton* number;
public:
   int nowmoney;
   explicit money1(scene1*parent);
   ~money1(){
       delete money_pic;
   }
   void buytower100();//-100
   void buytower180();//-180
   void destroytower();//+80
   void killenemy();//+30
   void updatemoney();//根据现在的钱币更改图标
};



class money2:QPushButton
{
     Q_OBJECT
private:
   scene2* father;
   QPixmap* money_pic;
   QPushButton* number;
public:
   int nowmoney;
   explicit money2(scene2*parent);
   ~money2(){
       delete money_pic;
   }
   void buytower100();//-100
   void buytower180();//-180
   void killenemy();//+30
   void destroytower();//+80
   void updatemoney();//更改钱币
};



class money3:QPushButton
{
     Q_OBJECT
private:

   scene3* father;
   QPixmap* money_pic;
   QPushButton* number;
public:
   int nowmoney;
   explicit money3(scene3*parent);
   ~money3(){
       delete money_pic;
   }
   void buytower100();//-100
   void buytower180();//-180
   void killenemy();//+30
   void destroytower();//+80
   void updatemoney();//更改钱币
};

#endif // MONEY_H
