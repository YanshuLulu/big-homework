#ifndef MONSTER_H
#define MONSTER_H
#include "rpgobj.h"
#include <QObject>

class Tower;

class Monster : public RPGObj
{
public:
    Monster(){}
    ~Monster(){}
    bool operator ==(const Monster &m){return (this->_pos==m._pos);}
    void move(int direction, int steps=1);
    void onErase();
    void go(){step++;}
    int showStep(){return step;}
    void show(QPainter * painter);
    void getAttacked(Tower* t){_attackers.push_back(t);}
    void lostSight(Tower* t);
    void getDamage(int damage);
    vector<Tower *> _attackers;
    double currentHP=50;
    bool _active=false;
    void doActive(){_active=true;}
protected:
    double maxHP=50;
    int walkingSpeed=1;
    int step=0;
};

#endif // MONSTER_H
