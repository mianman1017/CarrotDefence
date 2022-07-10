#include "win.h"
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
youwinpic::youwinpic(win* parent):QLabel(parent){
    setAttribute(Qt::WA_DeleteOnClose);
    father=parent;
    QSize picSize(620,180);
    normal=new QPixmap(":/end/images/win.jpg");
    *normal = normal->scaled(picSize);
    this->move(90,50);
    this->setPixmap(*normal);
    this->resize(normal->size());
    this->show();
}
continue_button::continue_button(win* parent):QPushButton(parent){
    setAttribute(Qt::WA_DeleteOnClose);
    father=parent;
    setCheckable(true);
    sound=new QSoundEffect(parent);
    QSize picSize(230,75);
    normal=new QPixmap(":/end/images/continue.jpg");
    *normal = normal->scaled(picSize);
    sound->setSource(QUrl::fromLocalFile("D:\\QT_carrotdefence\\CarrotDenfense\\button_press.wav"));//必须绝对路径
    this->setFlat(true);
    this->setFocusPolicy(Qt::NoFocus);
    this->setFixedSize(normal->size());
    this->setStyleSheet("QPushButton{Border:Opx;}");
    this->setIcon(*normal);
    this->setIconSize(QSize(normal->size()));
    this->move(275,350);
    this->show();
}
void continue_button::mousePressEvent(QMouseEvent *event){
    QPushButton::mousePressEvent(event);
    sound->setVolume(1.5);
    sound->play();
    choosewindow *choosepage=new choosewindow;
    this->close();
    father->close();
    father->sound->stop();
    choosepage->show();
}
win::win(QWidget *parent)
    : QMainWindow{parent}
{
    this->setFixedSize(800,500);
    //背景照片
    QPalette background = this->palette();
    QImage Img(":/background/images/cho_bg.png");
    QImage image=Img.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    background.setBrush(QPalette::Window, QBrush(image));
    this->setPalette(background);
    //按钮
    button=new continue_button(this);

    //胜利图片
    youwin=new youwinpic(this);
    //播放背景音乐
    sound=new QSoundEffect(this);
    sound->setSource(QUrl::fromLocalFile("D:\\QT_carrotdefence\\CarrotDenfense\\win.wav"));//必须绝对路径
    sound->setLoopCount(1);
    sound->setVolume(3);
    sound->play();
}
