#ifndef TOWERPOS_H
#define TOWERPOS_H
#include "rpgobj.h"
#include <vector>

class TowerPos : public RPGObj
{
public:
    static const int SIZE_X;
    static const int SIZE_Y;
    //static TowerPos findPosition(int x, int y);
    TowerPos(){}
    ~TowerPos(){}
    void setPutTower(bool canPut = false);
    bool canPutTower() const{return _canPutTower;}
    bool inArea(const QPoint &p) const;
    bool operator == (const TowerPos &p) const;
protected:
    bool _canPutTower=true;
};

#endif // TOWERPOS_H
