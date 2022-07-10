#include "menuwindow.h"
#include "choosewindow.h"
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

menu_button::menu_button(menuwindow *parent):QPushButton(parent){
    //setAttribute(Qt::WA_DeleteOnClose);
    father=parent;
    setCheckable(true);
    sound=new QSoundEffect(parent);
    press=new QPixmap(":/background/images/choose_button_move.png");
    normal=new QPixmap(":/background/images/choose_button_normal.png");
    sound->setSource(QUrl::fromLocalFile("D:\\QTproject\\CarrotDenfense\\button_press.wav"));//必须绝对路径
    this->setFlat(true);
    this->setFocusPolicy(Qt::NoFocus);
    this->setFixedSize(normal->size());
    this->setStyleSheet("QPushButton{Border:Opx;}");
    this->setIcon(*normal);
    this->setIconSize(QSize(normal->size()));
    this->move(570,230);
    this->show();
}

void menu_button::mousePressEvent(QMouseEvent *event){
    QPushButton::mousePressEvent(event);
    this->setIcon(*press);
    this->show();
    sound->setVolume(1.5);
    sound->play();
}//按下产生音效和按钮特效

void menu_button::mouseReleaseEvent(QMouseEvent *event){
    QPushButton::mouseReleaseEvent(event);
    choosewindow *choosepage=new choosewindow;
    this->close();
    father->close();
    father->music->stop();
    choosepage->show();
}//松开关闭menuwindow和音乐，打开choosewindow

menuwindow::menuwindow(QWidget *parent)
    : QMainWindow{parent}
{
    this->setFixedSize(800,500);
    //setAttribute(Qt::WA_DeleteOnClose);
    //背景照片
    QPalette background = this->palette();
    QImage Img(":/background/images/main_bg.jpg");
    QImage image=Img.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    background.setBrush(QPalette::Window, QBrush(image));
    this->setPalette(background);

    //gif动图添加
    /*QMovie *movie=new QMovie(":/background/images/carr.gif");
    QLabel *label=new QLabel(this);
    label->setFixedSize(117,111);
    movie->setScaledSize(label->size());
    label->setMovie(movie);
    movie->setSpeed(300);
    label->move(700,20);
    movie->start();*/

    //按钮
    choose=new menu_button(this);

    //播放背景音乐
    music=new QSoundEffect(this);
    music->setSource(QUrl::fromLocalFile("D:\\QTproject\\carrotDenfense\\menu_bg_music.wav"));//必须绝对路径
    music->setLoopCount(QSoundEffect::Infinite);
    music->setVolume(0.2);
    music->play();

}

