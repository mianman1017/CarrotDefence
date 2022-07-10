#ifndef CHOOSEWINDOW_H
#define CHOOSEWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include<QPixmap>
#include<QSoundEffect>

class choosewindow;

class cho_button3:public QPushButton{
    Q_OBJECT
public:
    QPixmap *normal;
    QPixmap *mov;
    QSoundEffect *sound;
    choosewindow *father;
    explicit cho_button3(choosewindow *parent=nullptr);
    ~cho_button3(){
        delete normal;
        delete mov;
    };
    void mouseReleaseEvent(QMouseEvent*);
};

class cho_button2:public QPushButton{
    Q_OBJECT
public:
    QPixmap *normal;
    QSoundEffect *sound;
    choosewindow *father;
    QPixmap *mov;
    explicit cho_button2(choosewindow *parent=nullptr);
    ~cho_button2(){
        delete normal;
        delete mov;
    };
    void mouseReleaseEvent(QMouseEvent*);
};

class cho_button1:public QPushButton{
    Q_OBJECT
public:
    QPixmap *normal;
    QSoundEffect *sound;
    choosewindow *father;
    QPixmap *mov;
    explicit cho_button1(choosewindow *parent=nullptr);
    ~cho_button1(){
        delete normal;
        delete mov;
    };
    void mouseReleaseEvent(QMouseEvent*);
};


class choosewindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit choosewindow(QWidget *parent = nullptr);
    QSoundEffect *sound;
    cho_button1 *map1;
    cho_button2 *map2;
    cho_button3 *map3;
    bool flag;
    ~choosewindow(){
        delete sound;
        delete map1;
        delete map2;
        delete map3;
    }
    void mouseMoveEvent(QMouseEvent*);
    int btnEnter(QPoint);
signals:

};

#endif // CHOOSEWINDOW_H
