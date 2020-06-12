#ifndef BULLET_H
#define BULLET_H
#include <QPoint>
#include <QPixmap>
#include <QObject>
#include <QPainter>
#include <QPropertyAnimation>
#include "monster.h"

class World;

class Bullet: QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint _currentPos READ getCurrentPos WRITE setCurrentPos)
public:
    Bullet(QPoint startp,QPoint targetp,int damage,Monster* m);
    ~Bullet();
    bool operator ==(const Bullet &b){return (this->_currentPos==b._currentPos
                                            && this->_target==b._target);}
    void show(QPainter *p);
    void move();
    void setCurrentPos(QPoint pos){_currentPos=pos;}
    QPoint getCurrentPos()const{return this->_currentPos;}
protected slots:
    void hitTarget();
private:
    const QPoint _startPos;
    const QPoint _targetPos;
    const QPixmap _pixmap;
    QPoint _currentPos;
    Monster* _target;
    int _damage;
    World *_world;
};

#endif // BULLET_H
