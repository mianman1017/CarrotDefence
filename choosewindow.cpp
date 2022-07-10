#include "choosewindow.h"
#include "choosewindow.h"
#include "scene1.h"
#include "scene2.h"
#include "scene3.h"
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


cho_button3::cho_button3(choosewindow *parent):QPushButton(parent){
    this->setMouseTracking(true);
    //setAttribute(Qt::WA_DeleteOnClose);
    father=parent;
    setCheckable(true);
    sound=new QSoundEffect(parent);
    normal=new QPixmap(":/background/images/map3_cho.png");
    mov=new QPixmap(":/background/images/map3_cho_move.png");
    sound->setSource(QUrl::fromLocalFile("D:\\QTproject\\CarrotDenfense\\cho_btn_move.wav"));//必须绝对路径
    this->setFlat(true);
    this->setFocusPolicy(Qt::NoFocus);
    this->setFixedSize(normal->size());
    this->setStyleSheet("QPushButton{Border:Opx;}");
    this->setIcon(*normal);
    this->setIconSize(QSize(normal->size()));
    this->move(550,100);
    this->show();
}

cho_button2::cho_button2(choosewindow *parent):QPushButton(parent){
    this->setMouseTracking(true);
    //setAttribute(Qt::WA_DeleteOnClose);
    father=parent;
    setCheckable(true);
    sound=new QSoundEffect(parent);
    normal=new QPixmap(":/background/images/map2_cho.png");
    mov=new QPixmap(":/background/images/map2_cho_move.png");
    sound->setSource(QUrl::fromLocalFile("D:\\QTproject\\CarrotDenfense\\cho_btn_move.wav"));//必须绝对路径
    this->setFlat(true);
    this->setFocusPolicy(Qt::NoFocus);
    this->setFixedSize(normal->size());
    this->setStyleSheet("QPushButton{Border:Opx;}");
    this->setIcon(*normal);
    this->setIconSize(QSize(normal->size()));
    this->move(300,100);
    this->show();
}

cho_button1::cho_button1(choosewindow *parent):QPushButton(parent){
    this->setMouseTracking(true);
    //setAttribute(Qt::WA_DeleteOnClose);
    father=parent;
    setCheckable(true);
    sound=new QSoundEffect(parent);
    normal=new QPixmap(":/background/images/map1_cho.png");
    mov=new QPixmap(":/background/images/map1_cho_move.png");
    sound->setSource(QUrl::fromLocalFile("D:\\QTproject\\CarrotDenfense\\cho_btn_move.wav"));//必须绝对路径
    this->setFlat(true);
    this->setFocusPolicy(Qt::NoFocus);
    this->setFixedSize(normal->size());
    this->setStyleSheet("QPushButton{Border:Opx;}");
    this->setIcon(*normal);
    this->setIconSize(QSize(normal->size()));
    this->move(50,100);
    this->show();
}

void cho_button1::mouseReleaseEvent(QMouseEvent *event){
    QPushButton::mouseReleaseEvent(event);
    scene1 *sc1=new scene1();
    this->close();
    father->close();
    father->sound->stop();
    sc1->show();
}//松开跳转对应页面

void cho_button2::mouseReleaseEvent(QMouseEvent *event){
    QPushButton::mouseReleaseEvent(event);
    scene2 *sc2=new scene2();
    this->close();
    father->close();
    father->sound->stop();
    sc2->show();
}

void cho_button3::mouseReleaseEvent(QMouseEvent *event){
    QPushButton::mouseReleaseEvent(event);
    scene3 *sc3=new scene3();
    this->close();
    father->close();
    father->sound->stop();
    sc3->show();
}

int choosewindow::btnEnter(QPoint pp){
    int height = map1->height();
    int width = map1->width();
    QPoint btnMinPos = map1->pos();
    QPoint btnMaxPos = map1->pos();
    btnMaxPos.setX(map1->pos().x()+width);
    btnMaxPos.setY(map1->pos().y()+height);
    if(pp.x() >= btnMinPos.x() && pp.y() >= btnMinPos.y()
            && pp.x() <= btnMaxPos.x() && pp.y() <= btnMaxPos.y()){
        return 1;
    }
    height = map2->height();
    width = map2->width();
    btnMinPos = map2->pos();
    btnMaxPos = map2->pos();
    btnMaxPos.setX(map2->pos().x()+width);
    btnMaxPos.setY(map2->pos().y()+height);
    if(pp.x() >= btnMinPos.x() && pp.y() >= btnMinPos.y()
            && pp.x() <= btnMaxPos.x() && pp.y() <= btnMaxPos.y()){
        return 2;
    }
    height = map3->height();
    width = map3->width();
    btnMinPos = map3->pos();
    btnMaxPos = map3->pos();
    btnMaxPos.setX(map3->pos().x()+width);
    btnMaxPos.setY(map3->pos().y()+height);
    if(pp.x() >= btnMinPos.x() && pp.y() >= btnMinPos.y()
            && pp.x() <= btnMaxPos.x() && pp.y() <= btnMaxPos.y()){
        return 3;
    }
    return 0;
}//判断是否进入按钮区域，如返回1说明进入map1按钮区域...

void choosewindow::mouseMoveEvent(QMouseEvent *event){
    QMainWindow::mouseMoveEvent(event);
    this->show();
    switch (btnEnter(event->pos())) {
    case 1:
        if(flag==false){
            map1->setFixedSize(map1->mov->size());
            map1->setIcon(*(map1->mov));
            map1->setIconSize(QSize(map1->mov->size()));
        map1->sound->setVolume(0.2);
        map1->sound->play();
        flag=true;
        }
        break;
    case 2:
        if(flag==false){
            map2->setFixedSize(map2->mov->size());
            map2->setIcon(*(map2->mov));
            map2->setIconSize(QSize(map2->mov->size()));
        map2->sound->setVolume(0.2);
        map2->sound->play();
        flag=true;
        }
        break;
    case 3:
        if(flag==false){
            map3->setFixedSize(map3->mov->size());
            map3->setIcon(*(map3->mov));
            map3->setIconSize(QSize(map3->mov->size()));
        map3->sound->setVolume(0.2);
        map3->sound->play();
        flag=true;
        }
        break;
    default:
        if(flag==true){
            map3->setFixedSize(map3->normal->size());
            map2->setFixedSize(map2->normal->size());
            map1->setFixedSize(map1->normal->size());
            map1->setIcon(*(map1->normal));
            map2->setIcon(*(map2->normal));
            map3->setIcon(*(map3->normal));
        }
        flag=false;
        break;
    }
}//进入按钮区域放大，音效

choosewindow::choosewindow(QWidget *parent)
    : QMainWindow{parent}
{
    this->setMouseTracking(true);
    this->setFixedSize(800,500);
    flag=false;
    //setAttribute(Qt::WA_DeleteOnClose);
    //背景照片
    QPalette background = this->palette();
    QImage Img(":/background/images/cho_bg.png");
    QImage image=Img.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    background.setBrush(QPalette::Window, QBrush(image));
    this->setPalette(background);

    //按钮
    map1=new cho_button1(this);
    map2=new cho_button2(this);
    map3=new cho_button3(this);

    //播放背景音乐
    sound=new QSoundEffect(this);
    sound->setSource(QUrl::fromLocalFile("D:\\QTproject\\CarrotDenfense\\choosewindow_BGMusic.wav"));//必须绝对路径
    sound->setLoopCount(QSoundEffect::Infinite);
    sound->setVolume(0.3);
    sound->play();
}

