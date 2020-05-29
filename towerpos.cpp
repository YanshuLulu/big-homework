#include "towerpos.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

const int TowerPos::SIZE_X=50;
const int TowerPos::SIZE_Y=50;

void TowerPos::setPutTower(bool canPut)
{
    this->_canPutTower=canPut;
}
bool TowerPos::operator ==(const TowerPos &p) const
{
    return (this->getPosX()==p.getPosX()&&this->getPosY()==p.getPosY());
}
/*TowerPos TowerPos::findPosition(int x, int y)
{
    vector<TowerPos *>::iterator it;
    it=find(_availablePos.begin(),_availablePos.end())
}*/
bool TowerPos::inArea(const QPoint &p) const
{
    bool x_in=p.x()>=(5*this->getPosX())&&p.x()<=(5*this->getPosX()+TowerPos::SIZE_X);
    bool y_in=p.y()>=(5*this->getPosY())&&p.y()<=(5*this->getPosY()+TowerPos::SIZE_Y);
    return x_in&&y_in;
}
