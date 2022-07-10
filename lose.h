#ifndef LOSE_H
#define LOSE_H


#include<QPushButton>
#include<QPixmap>
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
class lose;

class return_button:public QPushButton{
   Q_OBJECT
public:
    QPixmap* normal;
    lose* father;
    QSoundEffect* sound;
    explicit return_button(lose* father=nullptr);
    ~return_button(){
     delete normal;
    }
    void mousePressEvent(QMouseEvent*);
};

class remake_button:public QPushButton{
   Q_OBJECT
public:
    QPixmap* normal;
    lose* father;
    QSoundEffect* sound;
    explicit remake_button(lose* father=nullptr);
    ~remake_button(){
     delete normal;
    }
    void mousePressEvent(QMouseEvent*);
};

class lose:public QMainWindow
{
    Q_OBJECT
public:
    int sence;
    explicit lose(int scene,QWidget *father=nullptr);//int scene对应场景后的数字
    QSoundEffect* sound;
    return_button* returnbutton;
    remake_button* remakebutton;
    ~lose(){
        delete sound;
        delete returnbutton;
        delete remakebutton;
    }
};
#endif // LOSE_H
