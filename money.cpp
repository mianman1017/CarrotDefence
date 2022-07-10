
#include "money.h"
money1::money1(scene1*parent):QPushButton (parent){
    nowmoney=initmoney;
    father=parent;
    money_pic=new QPixmap(":/money/images/money.png");
    this->setFixedSize(money_pic->size());
    this->setStyleSheet("QPushButton{border:Opx;}");
    this->setIcon(*money_pic);
    this->setIconSize(QSize(money_pic->size()));
    this->move(330,11);//位置
    number=new QPushButton(this);
    number->setFont(QFont("宋体", 18));
    number->setText(QString::number(nowmoney));
    number->setFixedSize(100,20);//改变字框大小
    number->move(30,10);
    this->show();
    number->show();
};
void money1::destroytower(){
    nowmoney+=80;
};
void money1::buytower100(){
    nowmoney-=100;
};//-100
void money1::buytower180(){
    nowmoney-=180;
};//-180
void money1::killenemy(){
    nowmoney+=30;
};//+30
void money1::updatemoney(){
    number->setText(QString::number(nowmoney));
    number->setFixedSize(100,20);
    number->show();
}//改变钱币显示数值






money2::money2(scene2*parent):QPushButton (parent){
    nowmoney=initmoney*3;
    father=parent;
    money_pic=new QPixmap(":/money/images/money.png");
    this->setFixedSize(money_pic->size());
    this->setStyleSheet("QPushButton{border:Opx;}");
    this->setIcon(*money_pic);
    this->setIconSize(QSize(money_pic->size()));
    this->move(330,11);//位置
    number=new QPushButton(this);
    number->setFont(QFont("宋体", 18));
    number->setText(QString::number(nowmoney));
    number->setFixedSize(100,20);//改变字框大小
    number->move(30,10);
    this->show();
    number->show();
};
void money2::destroytower(){
    nowmoney+=80;
};
void money2::buytower100(){
    nowmoney-=100;
};//-100
void money2::buytower180(){
    nowmoney-=180;
};//-180
void money2::killenemy(){
    nowmoney+=30;
};//+30
void money2::updatemoney(){
    number->setText(QString::number(nowmoney));
    number->setFixedSize(100,20);
    number->show();
}//改变钱币显示数值





money3::money3(scene3*parent):QPushButton (parent){
    nowmoney=initmoney*5;
    father=parent;
    money_pic=new QPixmap(":/money/images/money.png");
    this->setFixedSize(money_pic->size());
    this->setStyleSheet("QPushButton{border:Opx;}");
    this->setIcon(*money_pic);
    this->setIconSize(QSize(money_pic->size()));
    this->move(330,11);//位置
    number=new QPushButton(this);
    number->setFont(QFont("宋体", 18));
    number->setText(QString::number(nowmoney));
    number->setFixedSize(100,20);//改变字框大小
    number->move(30,10);
    this->show();
    number->show();
};
void money3::buytower100(){
    nowmoney-=100;
};//-100
void money3::destroytower(){
    nowmoney+=80;
};
void money3::buytower180(){
    nowmoney-=180;
};//-180
void money3::killenemy(){
    nowmoney+=30;
};//+30
void money3::updatemoney(){
    number->setText(QString::number(nowmoney));
    number->setFixedSize(100,20);
    number->show();
}//改变钱币显示数值
