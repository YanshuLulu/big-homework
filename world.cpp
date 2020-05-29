#include "world.h"
#include "icon.h"
#include "rpgobj.h"
#include "monster.h"
#include <QMediaPlayer>
#include <iostream>
using namespace std;

void World::initWorld(string mapFile){
    //TODO 下面的内容应该改为从地图文件装载

    for(int i=0;i<5;i++)
    {
        RPGObj *p = new RPGObj;
        p->initObj("stone");
        p->setPosX(0+i*10);
        p->setPosY(20);
        this->_objs.push_back(p);
    }
    for(int i=0;i<3;i++)
    {
        RPGObj *p = new RPGObj;
        p->initObj("stone");
        p->setPosX(40);
        p->setPosY(30+i*10);
        this->_objs.push_back(p);
    }
    for(int i=0;i<9;i++)
    {
        RPGObj *p = new RPGObj;
        p->initObj("stone");
        p->setPosX(50+i*10);
        p->setPosY(50);
        this->_objs.push_back(p);
    }
    TowerPos *t1 = new TowerPos;
    t1->initObj("towerpos");
    t1->setPosX(20);
    t1->setPosY(30);
    this->_towerpos.push_back(t1);
    this->addWayPoints();
    TowerPos *t2 = new TowerPos;
    t2->initObj("towerpos");
    t2->setPosX(50);
    t2->setPosY(20);
    this->_towerpos.push_back(t2);
    TowerPos *t3 = new TowerPos;
    t3->initObj("towerpos");
    t3->setPosX(30);
    t3->setPosY(50);
    this->_towerpos.push_back(t3);
    TowerPos *t4 = new TowerPos;
    t4->initObj("towerpos");
    t4->setPosX(50);
    t4->setPosY(40);
    this->_towerpos.push_back(t4);
    TowerPos *t5 = new TowerPos;
    t5->initObj("towerpos");
    t5->setPosX(70);
    t5->setPosY(60);
    this->_towerpos.push_back(t5);
    TowerPos *t6 = new TowerPos;
    t6->initObj("towerpos");
    t6->setPosX(10);
    t6->setPosY(10);
    this->_towerpos.push_back(t6);
    TowerPos *t7 = new TowerPos;
    t7->initObj("towerpos");
    t7->setPosX(90);
    t7->setPosY(40);
    this->_towerpos.push_back(t7);
    TowerPos *t8 = new TowerPos;
    t8->initObj("towerpos");
    t8->setPosX(110);
    t8->setPosY(60);
    this->_towerpos.push_back(t8);
    RPGObj *p3 = new RPGObj;
    p3->initObj("end");
    p3->setPosX(140);
    p3->setPosY(44);
    this->_objs.push_back(p3);

    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/hdl.mp3"));
    player->setVolume(30);
    player->play();
}


void World::show(QPainter * painter){
    int n1 = this->_objs.size(),i=0;
    for (i=0;i<n1;i++){
        this->_objs[i]->show(painter);
    }
    for(i=0;i<this->_monster.size();i++)
        this->_monster[i]->show(painter);
    for(i=0;i<this->_towerpos.size();i++)
        this->_towerpos[i]->show(painter);
    for(i=0;i<this->_towers.size();i++)
        this->_towers[i]->show(painter);
    for (int i=0;i<4;i++){
        this->_wayPoints[i]->show(painter);
    }
}

void World::eraseMonster(){
    /*vector<RPGObj*>::iterator it;
    it = _objs.begin();
    while(it!=_objs.end()){
        int flag1 = ((*it)->getObjType()!="stone"); //不是石头
        int flag2 = ((*it)->getPosX() == x) && ((*it)->getPosY()==y);//位置重叠

        if (flag1 && flag2){
            cout<<(*it)->getObjType()<<endl;
            (*it)->onErase();
            delete (*it);
            it = this->_objs.erase(it);
            break;
         }
        else{
            it++;
        }
    }*/
    vector<Monster*>::iterator it;
    it=_monster.begin();
    while (it!=_monster.end()) {
        if((*it)->showStep()>160)
        {
            cout<<(*it)->getObjType()<<endl;
            (*it)->onErase();
            delete (*it);
            it=this->_monster.erase(it);
        }else{
            it++;
        }
    }
}

void World::MonsterMove(){
    int num=this->_monster.size();
    for(int i=0;i<num;i++)
    {
        int d=1;
        if(this->_monster[i]->showStep()<40)
            d=1;
        else if(this->_monster[i]->showStep()<70)
            d=2;
        else if(this->_monster[i]->showStep()<160)
            d=1;
        this->_monster[i]->move(d,1);
        this->_monster[i]->go();
    }
}

void World::addMonsters()
{
    Monster *m = new Monster;
    m->initObj("monster");
    m->setPosX(_objs[0]->getPos().x());
    m->setPosY(_objs[0]->getPos().y());
    this->_monster.push_back(m);
}

void World::addtower(Tower *t)
{
    this->_towers.push_back(t);
}

void World::addWayPoints()
{
    WayPoint *wayPoint1=new WayPoint(QPoint(0,100));
    this->_wayPoints.push_back(wayPoint1);

    WayPoint *wayPoint2=new WayPoint(QPoint(200,100));
    this->_wayPoints.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3=new WayPoint(QPoint(200,250));
    this->_wayPoints.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4=new WayPoint(QPoint(650,250));
    this->_wayPoints.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);
}
