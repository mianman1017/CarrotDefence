#include "lose.h"
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPushButton>
#include<QDebug>
#include<QSplashScreen>
#include<QLabel>
#include<QMovie>
#include<windows.h>
#include<QMouseEvent>
#include<QMediaPlayer>
#include<QSize>
#include"choosewindow.h"
#include"scene1.h"
#include"scene2.h"
#include"scene3.h"
remake_button::remake_button(lose* parent):QPushButton(parent){
    setAttribute(Qt::WA_DeleteOnClose);
    father=parent;
    setCheckable(true);
    sound=new QSoundEffect(parent);
    QSize picSize(210,60);//修改按钮大小
    normal=new QPixmap(":/end/images/remake.jpg");
    *normal = normal->scaled(picSize);
    sound->setSource(QUrl::fromLocalFile("D:\\QT_carrotdefence\\CarrotDenfense\\button_press.wav"));//必须绝对路径
    this->setFlat(true);
    this->setFocusPolicy(Qt::NoFocus);
    this->setFixedSize(normal->size());
    this->setStyleSheet("QPushButton{Border:Opx;}");
    this->setIcon(*normal);
    this->setIconSize(QSize(normal->size()));
    this->move(279,278);//修改按钮位置
    this->show();
}
void  remake_button::mousePressEvent(QMouseEvent *event){
    QPushButton::mousePressEvent(event);
    sound->setVolume(1.5);
    sound->play();
    this->close();
    father->close();
    father->sound->stop();
    //重建关卡
    switch(father->sence){
    case(1):{scene1* scen1=new scene1;scen1->show();break;}
    case(2):{scene2*scen2=new scene2;scen2->show();break;}
    case(3):{scene3*scen3=new scene3;scen3->show();break;}
    }
}

return_button::return_button(lose* parent):QPushButton(parent){
    setAttribute(Qt::WA_DeleteOnClose);
    father=parent;
    setCheckable(true);
    sound=new QSoundEffect(parent);
    QSize picSize(210,60);//修改按钮大小
    normal=new QPixmap(":/end/images/return.jpg");
    *normal = normal->scaled(picSize);
    sound->setSource(QUrl::fromLocalFile("D:\\QT_carrotdefence\\CarrotDenfense\\button_press.wav"));//必须绝对路径
    this->setFlat(true);
    this->setFocusPolicy(Qt::NoFocus);
    this->setFixedSize(normal->size());
    this->setStyleSheet("QPushButton{Border:Opx;}");
    this->setIcon(*normal);
    this->setIconSize(QSize(normal->size()));
    this->move(279,343);//修改按钮位置
    this->show();
}
void  return_button::mousePressEvent(QMouseEvent *event){
    QPushButton::mousePressEvent(event);
    sound->setVolume(1.5);
    sound->play();
    choosewindow *choosepage=new choosewindow;
    this->close();
    father->close();
    father->sound->stop();
    choosepage->show();
}
lose::lose(int sence,QWidget *parent)
    : QMainWindow{parent}
{
    this->sence=sence;
    this->setFixedSize(800,500);
    //背景照片
    QPalette background = this->palette();
    QImage Img(":/end/images/lose.jpg");
    QImage image=Img.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    background.setBrush(QPalette::Window, QBrush(image));
    this->setPalette(background);
    //按钮
    returnbutton=new return_button(this);
    remakebutton=new remake_button(this);
    //播放背景音乐
    sound=new QSoundEffect(this);
    sound->setSource(QUrl::fromLocalFile("D:\\QT_carrotdefence\\CarrotDenfense\\lose.wav"));//必须绝对路径
    sound->setLoopCount(1);
    sound->setVolume(3);
    sound->play();
}
