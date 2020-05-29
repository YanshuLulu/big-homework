#ifndef MONSTER_H
#define MONSTER_H
#include "rpgobj.h"

class Monster : public RPGObj
{
public:
    Monster(){}
    ~Monster(){}
    bool active();
    void move(int direction, int steps=1);
    void onErase();
    void go(){step++;}
    int showStep(){return step;}
    //void show(QPainter * painter);
protected:
    int maxHP=40;
    int currentHP=40;
    double walkingSpeed=1.0;
    int step=0;
};

#endif // MONSTER_H
