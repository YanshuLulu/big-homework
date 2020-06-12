#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <string>
#include <QPainter>
#include "fruit.h"
#include "rpgobj.h"
#include "monster.h"
#include "waypoint.h"
#include "tower.h"
#include "towerpos.h"
#include "bullet.h"

class World
{
public:
    World(){}
    ~World(){}
    void initWorld(string mapFile);
        //输入的文件中定义了初始状态下游戏世界有哪些对象，出生点在哪
        /*e.g.
           player 5 5
           stone 3 3
           fruit 7 8
         */
    void show(QPainter * painter);
        //显示游戏世界所有对象
    void MonsterMove();
    void eraseMonster(Monster *m);
    void addWayPoints();
    void addtower(Tower* t);
    void addMonsters();
    void addBullet(Bullet* b);
    //void attack();
    void monsterDied(Monster* m);
    void monsterDamaged(Monster* m,int damage);
    void eraseBullet(Bullet* b);
    void baseDamage(int damage=1);
    void gameOver();
    vector<TowerPos *> _towerpos;
    static vector<Tower *> _towers;
    static vector<Monster *> _monster;
    static vector<Bullet *> _bullets;
    static bool lose;
    static bool win;
private:
    vector<RPGObj *> _objs;
    vector<WayPoint *> _wayPoints;
    int _HP=10;
};

#endif // WORLD_H
