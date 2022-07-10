#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menuwindow.h"
#include "scene1.h"
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QDebug>
#include <QSplashScreen>
#include <QLabel>
#include <QMovie>
#include <windows.h>
#include <QMouseEvent>
#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>

QMediaPlayer *myPlayer=new QMediaPlayer;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(800,500);
    ui->setupUi(this);
    myPlayer->setParent(this);
    QVideoWidget *videoWidget=new QVideoWidget(this);
    QAudioOutput *audiooutput=new QAudioOutput(this);
    myPlayer->setVideoOutput(videoWidget);
    myPlayer->setAudioOutput(audiooutput);
    videoWidget->setFixedSize(800,500);
    videoWidget->show();
    myPlayer->setSource(QUrl::fromLocalFile("D:\\QTproject\\CarrotDenfense\\images\\CarrotDefense.mp4"));//这里不能是资源文件相对路径，必须是文件的绝对地址
    myPlayer->play();//播放MP4视频

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    {
    //QPainter painter(this);
    //QPixmap pixmap1(":/background/images/mainbackground.jpg");
    //painter.drawPixmap(0,0,this->width(),this->height(),pixmap1);
    }//背景图片，该方法只适用于主窗口

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        myPlayer->stop();
        menuwindow *menupage=new menuwindow;
        this->close();

        menupage->show();
    }
}
