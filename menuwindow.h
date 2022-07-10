#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include<QSoundEffect>
#include<QPushButton>
#include<QPixmap>
#include<QWidget>

class menuwindow;

class menu_button:public QPushButton{
    Q_OBJECT
public:
    QPixmap *press;
    QPixmap *normal;
    QSoundEffect *sound;
    menuwindow *father;
    explicit menu_button(menuwindow *parent=nullptr);
    ~menu_button(){
        delete press;
        delete normal;
    };
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
};



class menuwindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit menuwindow(QWidget *parent = nullptr);
    QSoundEffect *music;
    menu_button *choose;
    ~menuwindow(){
        delete music;
        delete choose;
    }
signals:

};

#endif // MENUWINDOW_H
