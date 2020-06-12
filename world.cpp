#include "world.h"
#include "icon.h"
#include "rpgobj.h"
#include <QMediaPlayer>
#include <QTimer>
#include <iostream>
#include <math.h>
using namespace std;

vector<Tower *> World::_towers;
vector<Monster *> World::_monster;
vector<Bullet *> World::_bullets;
bool World::lose=false;
bool World::win=false;

void World::initWorld(string mapFile){
    //TODO 下面的内容应该改为从地图文件装载

    for(int i=0;i<5;i++)
    {
        RPGObj *p = new RPGObj;
        p->initObj("stone");
        p->setPosX(0+i*10);
        p->setPosY(30);
        this->_objs.push_back(p);
    }
    for(int i=0;i<3;i++)
    {
        RPGObj *p = new RPGObj;
        p->initObj("stone");
        p->setPosX(40);
        p->setPosY(40+i*10);
        this->_objs.push_back(p);
    }
    for(int i=0;i<9;i++)
    {
        RPGObj *p = new RPGObj;
        p->initObj("stone");
        p->setPosX(50+i*10);
        p->setPosY(60);
        this->_objs.push_back(p);
    }
    TowerPos *t1 = new TowerPos;
    t1->initObj("towerpos");
    t1->setPosX(20);
    t1->setPosY(40);
    this->_towerpos.push_back(t1);
    this->addWayPoints();
    TowerPos *t2 = new TowerPos;
    t2->initObj("towerpos");
    t2->setPosX(50);
    t2->setPosY(30);
    this->_towerpos.push_back(t2);
    TowerPos *t3 = new TowerPos;
    t3->initObj("towerpos");
    t3->setPosX(30);
    t3->setPosY(60);
    this->_towerpos.push_back(t3);
    TowerPos *t4 = new TowerPos;
    t4->initObj("towerpos");
    t4->setPosX(50);
    t4->setPosY(50);
    this->_towerpos.push_back(t4);
    TowerPos *t5 = new TowerPos;
    t5->initObj("towerpos");
    t5->setPosX(70);
    t5->setPosY(70);
    this->_towerpos.push_back(t5);
    TowerPos *t6 = new TowerPos;
    t6->initObj("towerpos");
    t6->setPosX(10);
    t6->setPosY(20);
    this->_towerpos.push_back(t6);
    TowerPos *t7 = new TowerPos;
    t7->initObj("towerpos");
    t7->setPosX(90);
    t7->setPosY(50);
    this->_towerpos.push_back(t7);
    TowerPos *t8 = new TowerPos;
    t8->initObj("towerpos");
    t8->setPosX(110);
    t8->setPosY(70);
    this->_towerpos.push_back(t8);
    RPGObj *p3 = new RPGObj;
    p3->initObj("end");
    p3->setPosX(140);
    p3->setPosY(54);
    this->_objs.push_back(p3);
}


void World::show(QPainter * painter){
    int n1 = this->_objs.size(),i=0;
    for (i=0;i<n1;i++){
        this->_objs[i]->show(painter);
    }
    for(i=0;i<this->_towerpos.size();i++)
        this->_towerpos[i]->show(painter);
    for(i=0;i<_towers.size();i++)
        _towers[i]->show(painter);
    for(i=0;i<_monster.size();i++)
        _monster[i]->show(painter);
    for(i=0;i<_bullets.size();i++)
        _bullets[i]->show(painter);
}

void World::eraseMonster(Monster *m)
{
    vector<Monster*>::iterator it;
    it=find(_monster.begin(),_monster.end(),m);
    if(it==_monster.end())
        return;
    else{
        (*it)->onErase();
        delete (*it);
        _monster.erase(it);
    }
}

void World::eraseBullet(Bullet *b)
{
    vector<Bullet *>::iterator it;
    it=find(_bullets.begin(),_bullets.end(),b);
    if(it==_bullets.end())
        return;
    else
    {
        delete (*it);
        _bullets.erase(it);
    }
}

void World::MonsterMove(){
    int num=_monster.size();
    for(int i=0;i<num;i++)
    {
        _monster[i]->doActive();
        if(!_monster[i]->_active)
            return;
        int d=1;
        if(_monster[i]->showStep()<40)
            d=1;
        else if(_monster[i]->showStep()<70)
            d=2;
        else if(_monster[i]->showStep()<160)
            d=1;
        else{
            eraseMonster(_monster[i]);
            baseDamage();
        }
        _monster[i]->move(d,1);
        _monster[i]->go();
    }
}

void World::monsterDied(Monster *m)
{
    if(m->_attackers.empty())
        return;
    int n=m->_attackers.size();
    for(int i=0;i<n;i++)
        m->_attackers[i]->targetKilled();
    eraseMonster(m);
}

void World::monsterDamaged(Monster *m, int damage)
{
    m->getDamage(damage);
    if(m->currentHP<=0)
        monsterDied(m);
}

void World::baseDamage(int damage)
{
    this->_HP-=damage;
    if(this->_HP<=0)
        gameOver();
}

void World::addMonsters()
{
    Monster *m = new Monster;
    m->initObj("monster");
    m->setPosX(_objs[0]->getPos().x());
    m->setPosY(_objs[0]->getPos().y());
    _monster.push_back(m);
}

void World::addtower(Tower *t)
{
    _towers.push_back(t);
}

void World::addBullet(Bullet *b)
{
    _bullets.push_back(b);
}

void World::addWayPoints()
{
    WayPoint *wayPoint1=new WayPoint(QPoint(0,150));
    this->_wayPoints.push_back(wayPoint1);

    WayPoint *wayPoint2=new WayPoint(QPoint(200,150));
    this->_wayPoints.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3=new WayPoint(QPoint(200,300));
    this->_wayPoints.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4=new WayPoint(QPoint(650,300));
    this->_wayPoints.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);
}

void World::gameOver()
{
    if(!lose)
        lose=true;
}
