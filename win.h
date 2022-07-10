#ifndef WIN_H
#define WIN_H
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
class win;
class youwinpic:public QLabel{
    Q_OBJECT
public:
    QPixmap* normal;
    win* father;
    explicit youwinpic(win* father=nullptr);
    ~youwinpic(){
        delete normal;
    }
};

class continue_button:public QPushButton{
   Q_OBJECT
public:
    QPixmap* normal;
    win* father;
    QSoundEffect* sound;
    explicit continue_button(win* father=nullptr);
    ~continue_button(){
     delete normal;
    }
    void mousePressEvent(QMouseEvent*);
};
class win:public QMainWindow
{
    Q_OBJECT
public:
    explicit win(QWidget *father=nullptr);
    QSoundEffect* sound;
    continue_button* button;
    youwinpic* youwin;
    ~win(){
        delete sound;
        delete button;
        delete youwin;
    }
};

#endif // WIN_H
