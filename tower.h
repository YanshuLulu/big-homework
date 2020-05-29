#ifndef TOWER_H
#define TOWER_H
#include "rpgobj.h"

class Tower : public RPGObj
{
public:
    Tower(){}
    void show(QPainter * pa);
protected:
    int _attackRange=80;
    int _damage=10;
    int _rate=1000;
};

#endif // TOWER_H
