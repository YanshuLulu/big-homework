#ifndef TOWER_H
#define TOWER_H
//#include "rpgobj.h"
#include <QObject>
#include "monster.h"
#include <QTimer>
#include "bullet.h"

class World;

class Tower : public QObject
{
    Q_OBJECT
public:
    Tower(QPoint p);
    ~Tower();
    bool operator ==(const Tower &t){return (this->_pos==t._pos);}
    void setPosX(int x){this->_pos.setX(x);}
    void setPosY(int y){this->_pos.setY(y);}
    int getPosX() const{return this->_pos.x();}
    int getPosY() const{return this->_pos.y();}
    QPoint getPos() const{return this->_pos;}
    void show(QPainter * pa);

    int getDamage()const{return _damage;}
    int getRate()const{return _rate;}
    void checkMonsterIn();
    void attackMonster();
    void chooseMonster(Monster*m);
    void targetKilled();
    void loseTarget();
    bool meet(QPoint p1,int r1,QPoint p2,int r2);
protected slots:
    void weapon();
protected:
    QPoint _pos;
    QPixmap _pixmap;
    int _attackRange=80;
    int _damage=10;
    int _rate=500;
    QTimer* _rateTimer;
    Monster* _chooseMonster=NULL;
    World* _world;
};

#endif // TOWER_H
