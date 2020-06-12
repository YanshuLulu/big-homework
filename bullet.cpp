#include "bullet.h"
#include "world.h"
#include <QPropertyAnimation>

Bullet::Bullet(QPoint startp, QPoint targetp, int damage, Monster *m):_startPos(startp),
    _targetPos(targetp),_pixmap(":/pics/bullet.png"),_currentPos(startp),_target(m),_damage(damage)
{
    _world=new World;
}
Bullet::~Bullet()
{
    delete _world;
}
void Bullet::show(QPainter *p)
{
    p->drawPixmap(_currentPos,_pixmap);
}
void Bullet::move()
{
    static const int duration = 500;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "_currentPos");
    animation->setDuration(duration);
    animation->setStartValue(_startPos);
    animation->setEndValue(_targetPos);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));

    animation->start();
}
void Bullet::hitTarget()
{
    // 这样处理的原因是:
    // 可能多个炮弹击中敌人,而其中一个将其消灭,导致敌人delete
    // 后续炮弹再攻击到的敌人就是无效内存区域
    // 因此先判断下敌人是否还有效
    vector<Monster*>::iterator it;
    it=find(World::_monster.begin(),World::_monster.end(),_target);
    if (it!=World::_monster.end())
        _world->monsterDamaged(*it,_damage);
    _world->eraseBullet(this);
}
