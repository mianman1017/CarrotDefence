#include "scene3.h"
#include "tower.h"
#include "math.h"
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QDebug>
#include <QSplashScreen>
#include <QLabel>
#include <QMovie>
#include <windows.h>
#include <QMouseEvent>
#include <QTimer>
#include "win.h"
#include "lose.h"
#include "money.h"
#include "hp.h"
class point3
{
public:
    int x;
    int y;
    bool available;//是否可放置
    point3(){
        available=true;
    }
}p3[9];//记录可放置tower的点的位置,1~8编号对应8个tower点位

static void pointinitialize();
static float getdistance(QPoint pos1,QPoint pos2);



static int count=0;//记录怪物数
static int wave=1;//记录怪物波数
static hp3* carrot_hp3=nullptr;//血条
static money3*mymoney3=nullptr;//金钱

scene3::scene3(QWidget *parent)
    : QMainWindow{parent}
{
    this->setFixedSize(800,500);
    pointinitialize();
    {
        count=0;
        wave=1;

        timer1=new QTimer;
        timer2=new QTimer;
        timer3=new QTimer;
        //初始化button
        button1=new QPushButton;
        button2=new QPushButton;
        QPixmap pixmap1(":/tower/images/choose1.png");
        button1->setFixedSize(pixmap1.size());
        button1->setStyleSheet("QPushButton{Border:Opx;}");
        button1->setIcon(pixmap1);
        button1->setIconSize(QSize(pixmap1.size()));
        QPixmap pixmap2(":/tower/images/choose2.png");
        pixmap2.scaled(40,40);
        button2->setFixedSize(pixmap2.size());
        button2->setStyleSheet("QPushButton{Border:Opx;}");
        button2->setIcon(pixmap2);
        button2->setIconSize(QSize(pixmap2.size()));

        //设置背景图片（包含自适应大小操作）
        QPalette background = this->palette();
        QImage Img(":/stage/images/map3.png");
        QImage image=Img.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
        background.setBrush(QPalette::Window, QBrush(image));
        this->setPalette(background);

        //萝卜gif动图添加
        QMovie *movie=new QMovie(":/extra/images/carrot.gif");
        QLabel *label=new QLabel(this);
        label->setFixedSize(70,70);
        movie->setScaledSize(label->size());
        label->setMovie(movie);
        movie->setSpeed(300);
        label->move(675,165);
        movie->start();
        //血条初始化
        carrot_hp3=new hp3(this);
        //金币初始化
        mymoney3=new money3(this);
        //避免提前设置好，避免一直重新设置造成卡顿
        sound3=new QSoundEffect(this);
        sound3->setSource(QUrl::fromLocalFile("D:\\QTproject\\CarrotDenfense\\monster_fat1.wav"));//必须绝对路径
        sound3->setVolume(0.3);
        sound4=new QSoundEffect(this);
        sound4->setSource(QUrl::fromLocalFile("D:\\QTproject\\CarrotDenfense\\tower_attack.wav"));//必须绝对路径
        sound4->setVolume(0.7);
        sound5=new QSoundEffect(this);
        sound5->setSource(QUrl::fromLocalFile("D:\\QTproject\\CarrotDenfense\\carrot.wav"));//必须绝对路径
        sound5->setVolume(0.3);

        //播放背景音乐
        sound1=new QSoundEffect(this);
        sound1->setSource(QUrl::fromLocalFile("D:\\QTproject\\CarrotDenfense\\gamebk_music.wav"));//必须绝对路径
        sound1->setLoopCount(QSoundEffect::Infinite);
        sound1->setVolume(3.3);
        sound1->play();

        //开启屏幕不断更新
        connect(timer1,&QTimer::timeout,this,&scene3::updatescene);
        timer1->start(10);

        //go按钮，代表游戏开始
        //monster生成
        {
            QPixmap pixmap(":/extra/images/go.png");
            QPushButton *button=new QPushButton(this);
            button->setFixedSize(pixmap.size());
            button->setStyleSheet("QPushButton{Border:Opx;}");
            button->setIcon(pixmap);
            button->setIconSize(QSize(pixmap.size()));
            button->move(10,10);
            button->show();
            connect(button,&QPushButton::clicked,this,[=](){
                //点击音效
                sound2=new QSoundEffect(this);
                sound2->setSource(QUrl::fromLocalFile("D:\\QTproject\\CarrotDenfense\\button_press.wav"));//必须绝对路径
                sound2->setVolume(1.5);
                sound2->play();

                //计时器定时更新调用
                connect(timer2,&QTimer::timeout,this,&scene3::addmonster);
                connect(timer3,&QTimer::timeout,this,[=](){
                    for(int i=0;i<tower_list.size();i++)
                    {
                        int check=0;//检查是否范围内已没有怪物
                        for(int j=0;j<monster_list.size();j++)
                        {
                            if(getdistance(tower_list[i]->pos,monster_list[j]->currentpos)<700)
                            {
                                int size;
                                if(tower_list[i]->level==1)
                                    size=17;
                                else size=30;
                                //qDebug()<<monster_list.size();
                                tower_list[i]->target=monster_list[j];
                                addbullet(tower_list[i]->pos,monster_list[j]->currentpos,tower_list[i]->bulletpixfileName,monster_list[j],size);
                                check=1;
                                break;
                            }
                        }
                        if(check==0)
                        {
                            tower_list[i]->target=NULL;
                        }
                    }
                    //qDebug()<<tower_list.size();
                });
                timer2->start(500);
                timer3->start(500);
                button->close();
            }
            );//lambda表达式
        }
    }
}

void scene3::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        button1->close();
        button2->close();
        button1->disconnect();
        button2->disconnect();
        int x=this->mapFromGlobal(QCursor().pos()).x();//
        int y=this->mapFromGlobal(QCursor().pos()).y();//获取鼠标在窗口的相对位置
        qDebug()<<x<<" "<<y;//鼠标点击相对位置的输出
        for(int i=1;i<=24;i++)
        {
            if(x>p3[i].x&&x<p3[i].x+40&&y>p3[i].y&&y<p3[i].y+40&&p3[i].available==true)//如果鼠标点击处位于tower放置点且当前位置可放置Tower
            {
                //点击音效
                sound2=new QSoundEffect(this);
                sound2->setSource(QUrl::fromLocalFile("D:\\QTproject\\CarrotDenfense\\button_press.wav"));//必须绝对路径
                sound2->setVolume(1.5);
                sound2->play();

                //设置以图片形式呈现的按钮
                {
                button1->setParent(this);
                button2->setParent(this);
                QPixmap pixmap1(":/tower/images/choose1.png");
                button1->setFixedSize(pixmap1.size());
                button1->setStyleSheet("QPushButton{Border:Opx;}");
                button1->setIcon(pixmap1);
                button1->setIconSize(QSize(pixmap1.size()));
                button1->move(p3[i].x-3,p3[i].y+40);
                button1->show();
                QPixmap pixmap2(":/tower/images/choose2.png");
                pixmap2.scaled(40,40);
                button2->setFixedSize(pixmap2.size());
                button2->setStyleSheet("QPushButton{Border:Opx;}");
                button2->setIcon(pixmap2);
                button2->setIconSize(QSize(pixmap2.size()));
                button2->move(p3[i].x-3,p3[i].y-52);
                button2->show();
                }

                //鼠标点击处生成tower
                if(mymoney3->nowmoney>=100){
                connect(button1,&QPushButton::clicked,this,[=](){
                    //点击音效
                    mymoney3->buytower100();
                    sound2->setVolume(1.5);
                    sound2->play();

                    setTower(p3[i].x+5,p3[i].y+5,":/tower/images/tower1.png",":/extra/images/bullet1.png");
                    button1->close();
                    button2->close();
                    button1->disconnect();
                    button2->disconnect();
                    p3[i].available=false;
                });}
                if(mymoney3->nowmoney>=180){
                connect(button2,&QPushButton::clicked,this,[=](){
                    //点击音效
                    mymoney3->buytower180();
                    sound2->setVolume(1.5);
                    sound2->play();

                    setTower(p3[i].x+5,p3[i].y+5,":/tower/images/tower2.png",":/extra/images/bullet2.png");
                    button1->close();
                    button2->close();
                    button1->disconnect();
                    button2->disconnect();
                    p3[i].available=false;
                });}
                break;
            }
            if(x>p3[i].x&&x<p3[i].x+40&&y>p3[i].y&&y<p3[i].y+40&&p3[i].available==false)
            {
                //点击音效
                sound2=new QSoundEffect(this);
                sound2->setSource(QUrl::fromLocalFile("D:\\QTproject\\CarrotDenfense\\button_press.wav"));//必须绝对路径
                sound2->setVolume(1.5);
                sound2->play();

                //设置以图片形式呈现的按钮
                {
                button1->setParent(this);
                button2->setParent(this);
                QPixmap pixmap1(":/tower/images/remove.png");
                button1->setFixedSize(pixmap1.size());
                button1->setStyleSheet("QPushButton{Border:Opx;}");
                button1->setIcon(pixmap1);
                button1->setIconSize(QSize(pixmap1.size()));
                button1->move(p3[i].x-3,p3[i].y+40);
                button1->show();
                QPixmap pixmap2(":/tower/images/level_up.png");
                pixmap2.scaled(40,40);
                button2->setFixedSize(pixmap2.size());
                button2->setStyleSheet("QPushButton{Border:Opx;}");
                button2->setIcon(pixmap2);
                button2->setIconSize(QSize(pixmap2.size()));
                button2->move(p3[i].x-3,p3[i].y-52);
                button2->show();
                }

                //鼠标点击处生成tower
                connect(button1,&QPushButton::clicked,this,[=](){
                    //点击音效
                    mymoney3->destroytower();
                    sound2->setVolume(1.5);
                    sound2->play();
                    for(int j=0;j<tower_list.size();j++)
                    {
                        if(tower_list[j]->level==1)
                        {
                            if(tower_list[j]->pos.x()==p3[i].x+5&&tower_list[j]->pos.y()==p3[i].y+5)
                            {
                                delete tower_list[j];
                                tower_list.removeAt(j);
                                p3[i].available=true;

                            }
                        }
                        else if(tower_list[j]->level==2)
                        {
                            if(tower_list[j]->pos.x()==p3[i].x&&tower_list[j]->pos.y()==p3[i].y)
                            {
                                delete tower_list[j];
                                tower_list.removeAt(j);
                                p3[i].available=true;

                            }
                        }
                    }
                    button1->close();
                    button2->close();
                    button1->disconnect();
                    button2->disconnect();
                });
                if(mymoney3->nowmoney>=180){
                connect(button2,&QPushButton::clicked,this,[=](){
                    //点击音效
                    sound2->setVolume(1.5);
                    sound2->play();
                    foreach(tower* _tower,tower_list)
                    {
                        if(_tower->pos.x()==p3[i].x+5&&_tower->pos.y()==p3[i].y+5&&_tower->level==1)
                        {
                            mymoney3->buytower180();
                            _tower->pos=QPoint(p3[i].x,p3[i].y);
                            _tower->size=40;
                            _tower->level=2;
                            //金币
                        }
                    }
                    button1->close();
                    button2->close();
                    button1->disconnect();
                    button2->disconnect();
                    p3[i].available=false;
                });}
                break;
            }
        }
    }
}

void scene3::paintEvent(QPaintEvent *)
{
    foreach(tower *new_tower,tower_list)
    {
        QPainter *painter1=new QPainter(this);
        new_tower->draw(painter1);
        painter1->end();
    }//给每个tower进行绘制
    QPainter *painter2=new QPainter(this);
    {
    foreach(myobject *object,monster_list)
        object->draw(painter2);
    }//给每个物体进行绘制
    {
    foreach(myobject *object,bullet_list)
        object->draw(painter2);
    }//给每个子弹进行绘制
    painter2->end();
}

void scene3::setTower(int x,int y,QString towerpixfileName,QString bulletpixfileName)
{
    tower *new_tower=new tower(QPoint(x,y),towerpixfileName,bulletpixfileName);
    tower_list.push_back(new_tower);
    update();

}

void scene3::updatescene()
{
    for(int i=0;i<monster_list.size();i++)
    {
        //改变移动路线
        if(monster_list[i]->currentpos.x()==80&&monster_list[i]->currentpos.y()==385)
            monster_list[i]->targetpos=QPoint(343,385);
        if(monster_list[i]->currentpos.x()==343&&monster_list[i]->currentpos.y()==385)
            monster_list[i]->targetpos=QPoint(343,260);
        if(monster_list[i]->currentpos.x()==343&&monster_list[i]->currentpos.y()==260)
            monster_list[i]->targetpos=QPoint(477,260);
        if(monster_list[i]->currentpos.x()==477&&monster_list[i]->currentpos.y()==260)
            monster_list[i]->targetpos=QPoint(477,141);
        if(monster_list[i]->currentpos.x()==477&&monster_list[i]->currentpos.y()==141)
            monster_list[i]->targetpos=QPoint(544,141);
        if(monster_list[i]->currentpos.x()==544&&monster_list[i]->currentpos.y()==141)
            monster_list[i]->targetpos=QPoint(544,197);
        if(monster_list[i]->currentpos.x()==544&&monster_list[i]->currentpos.y()==197)
            monster_list[i]->targetpos=QPoint(647,197);

        //怪物抵达终点
        if(monster_list[i]->currentpos.x()==647&&monster_list[i]->currentpos.y()==197)
        {
            sound5->play();
            for(int j=0;j<bullet_list.size();)
            {
                if(bullet_list[j]->lock==monster_list[i])
                {
                    delete bullet_list[j];
                    bullet_list.removeAt(j);
                }
            }
            delete monster_list[i];
            monster_list.removeAt(i);
            i--;
            carrot_hp3->hurt();
            carrot_hp3->setpic();
            if(carrot_hp3->ifdead()){
                this->close();

                this->sound1->stop();
                timer3->stop();
                timer2->stop();
                timer1->stop();
                for(int i=1;i<9;i++)
                    p3[i].available=true;
                lose *los=new lose(3);
                los->show();
            }
            continue;
        }

        //判断怪物是否死亡
        if(monster_list[i]->now_hp<=0)
        {
            mymoney3->killenemy();
            sound3->play();
            for(int j=0;j<bullet_list.size();)
            {
                if(bullet_list[j]->lock==monster_list[i])
                {
                    delete bullet_list[j];
                    bullet_list.removeAt(j);
                }
            }
            delete monster_list[i];
            monster_list.removeAt(i);
            i--;
            continue;
        }

        //怪物移动
        monster_list[i]->move();
    }

    //子弹追踪锁定
    foreach(myobject *monster,monster_list)
    {
        foreach(myobject *bullet,bullet_list)
        {
            if(bullet->lock==monster)
                bullet->targetpos=monster->currentpos;
            bullet->move();
        }
    }

    //判断子弹是否已击中怪物
    int check=0;//避免多子弹同时击中怪物时持续调用sound3造成卡顿
    for(int i=0;i<bullet_list.size();i++)
    {
        //qDebug()<<bullet_list[i]->speed;
        if(getdistance(bullet_list[i]->currentpos,bullet_list[i]->lock->currentpos)<10)
        {
            //攻击音效
            //sound=new QSoundEffect(this);
            //sound3->setSource(QUrl::fromLocalFile("D:\\QTproject\\CarrotDenfense\\monster_fat1.wav"));//必须绝对路径
            //sound3->setVolume(0.3);
            if(check==0)
            {
                //sound3->play();//注意：这里是怪物受到攻击时的音效，加进去后tower一多就会卡顿，目前没有解决
                check=1;
            }
            //qDebug()<<bullet_list.size();
            if(bullet_list[i]->size==17)
                bullet_list[i]->lock->now_hp-=50;
            else bullet_list[i]->lock->now_hp-=100;
            if(bullet_list[i]->bullet_effect==1)
                bullet_list[i]->lock->monster_effect=1;
            delete bullet_list[i];
            bullet_list.removeAt(i);
            //qDebug()<<bullet_list.size();
        }
    }
    check=0;

    //tower对怪物的旋转角度锁定
    foreach(tower *_tower,tower_list)
    {
        if(_tower->target!=NULL)
        {
            float _angle=0;
            float deltax=_tower->pos.x()-_tower->target->currentpos.x();
            float deltay=_tower->pos.y()-_tower->target->currentpos.y();
            if((deltax>0&&deltay>0)||(deltax>0&&deltay<0))
            {
                _angle=(atan(deltay/deltax)*180)/3.1416;
                _tower->angle=270+_angle;
                //qDebug()<<_tower->angle;
            }
            else if((deltax<0&&deltay<0)||(deltax<0&&deltay>0))
            {
                _angle=(atan(deltay/deltax)*180)/3.1416;
                _tower->angle=90+_angle;
                //qDebug()<<_tower->angle;
            }
            else if(deltax==0&&deltay<0)
            {
                _tower->angle=180;
            }
        }
    }

    if(wave==3&&monster_list.size()==0&&carrot_hp3->ifdead()==false){

            this->close();

            this->sound1->stop();
            timer3->stop();
            timer2->stop();
            timer1->stop();
            for(int i=1;i<9;i++)
                p3[i].available=true;
            win *w=new win;
            w->show();

    }

    mymoney3->updatemoney();
    update();

}

void scene3::addmonster()
{
    count++;

    //设立各波次的怪物类型与数量
    if(count<=7)
    {
        myobject* monster03=new myobject(QPoint(80,200),QPoint(80,385),":/monster/images/monster3.png");
        monster03->hp=500;
        monster03->now_hp=500;
        monster03->ifmonster=1;
        monster_list.push_back(monster03);
    }
    if(count>7&&count<=12)
    {
        myobject* monster04=new myobject(QPoint(80,200),QPoint(80,385),":/monster/images/monster4.png");
        monster04->hp=2000;
        monster04->now_hp=2000;
        monster04->ifmonster=1;
        monster_list.push_back(monster04);
    }
    if(count==13)
    {
        myobject* monster05=new myobject(QPoint(80,200),QPoint(80,385),":/monster/images/monster5.png");
        monster05->hp=15000;
        monster05->now_hp=15000;
        monster05->ifmonster=1;
        monster_list.push_back(monster05);
    }

    //第一波怪物
    if(count>=7&&wave==1)
    {
        wave=2;
        timer2->stop();
        QTimer::singleShot(7000,this,[=](){
            timer2->start();
        });
    }

    //第二波怪物
    if(count>=12&&wave==2)
    {
        wave=3;
        timer2->stop();
        QTimer::singleShot(7000,this,[=](){
            timer2->start();
        });
    }

    //第三波怪物
    if(count>=13&&wave==3)
    {
        timer2->stop();
    }
}

void scene3::addbullet(QPoint pos1,QPoint pos2,QString bulletpixfileName,myobject *lockedmonster,int _size)
{
    //子弹发射音效
    //sound=new QSoundEffect(this);
    //sound->setSource(QUrl::fromLocalFile("D:\\QTproject\\CarrotDenfense\\tower_attack.wav"));//必须绝对路径
    //sound4->setVolume(0.3);
    sound4->play();

    myobject* bullet=new myobject(pos1,pos2,bulletpixfileName);
    if(bulletpixfileName.compare(":/extra/images/bullet2.png")==0)
        bullet->bullet_effect=1;
    bullet->lock=lockedmonster;
    bullet->speed=7.0;
    bullet->size=_size;
    bullet_list.push_back(bullet);
}


static void pointinitialize()
{
    {
        p3[1].x=145;
        p3[1].y=330;
        p3[2].x=213;
        p3[2].y=330;
        p3[3].x=281;
        p3[3].y=330;
        p3[4].x=348;
        p3[4].y=202;
        p3[5].x=415;
        p3[5].y=202;
        p3[6].x=415;
        p3[6].y=330;
        p3[7].x=415;
        p3[7].y=393;
        p3[8].x=553;
        p3[8].y=260;
    }//给每个塔防点坐标赋值,x、y为正方形左上角坐标，宽度40
}


static float getdistance(QPoint pos1,QPoint pos2)
{
    int deltax=pos1.x()-pos2.x();
    int deltay=pos1.y()-pos2.y();
    float result=sqrt(pow(deltax,2)+pow(deltay,2));
    return result;
}
