#include "tower.h"
#include "world.h"
#include <math.h>

Tower::Tower(QPoint p):_pos(p),_pixmap(":/pics/tower.png")
{
    _rateTimer=new QTimer(this);
    connect(_rateTimer,SIGNAL(timeout()),this,SLOT(weapon()));
    _world=new World;
}
Tower::~Tower()
{
    delete _world;
}
void Tower::show(QPainter * pa){
    pa->drawPixmap(_pos*5,_pixmap);
    pa->save();
    if(_chooseMonster)
        pa->setPen(Qt::red);
    else
        pa->setPen(Qt::white);
    QPoint p(this->_pos.x()*5+25,this->_pos.y()*5+25);
    pa->drawEllipse(p,_attackRange,_attackRange);
    pa->restore();
}
bool Tower::meet(QPoint p1, int r1, QPoint p2, int r2)
{
    double dx=p1.x()-p2.x();
    double dy=p1.y()-p2.y();
    double d=sqrt(dx*dx+dy*dy);
    if(d<=r1+r2)
        return true;
    else
        return false;
}
void Tower::checkMonsterIn()
{
    if(this->_chooseMonster)
    {
        if(!meet(this->getPos(),_attackRange/5,this->_chooseMonster->getPos(),6))
            loseTarget();
    }else{
        int n=World::_monster.size();
        for(int i=0;i<n;i++)
        {
            if(meet(this->getPos(),_attackRange/5,World::_monster[i]->getPos(),6))
            {
                chooseMonster(World::_monster[i]);
                break;
            }
        }
    }
}
void Tower::attackMonster(){
    this->_rateTimer->start(this->_rate);
}
void Tower::chooseMonster(Monster *m){
    this->_chooseMonster=m;
    attackMonster();
    this->_chooseMonster->getAttacked(this);
}
void Tower::weapon()
{
    Bullet *bullet = new Bullet(QPoint(_pos.x()*5+15,_pos.y()*5+15),
                                QPoint(this->_chooseMonster->getPosX()*5+15,this->_chooseMonster->getPosY()*5+15),
                                _damage, this->_chooseMonster);
    bullet->move();
    World::_bullets.push_back(bullet);
}
void Tower::targetKilled()
{
    if(this->_chooseMonster)
        this->_chooseMonster=NULL;
    _rateTimer->stop();
}
void Tower::loseTarget()
{
    this->_chooseMonster->lostSight(this);
    if(this->_chooseMonster)
        this->_chooseMonster=NULL;
    _rateTimer->stop();
}
