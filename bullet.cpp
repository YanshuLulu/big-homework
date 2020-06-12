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
    // ���������ԭ����:
    // ���ܶ���ڵ����е���,������һ����������,���µ���delete
    // �����ڵ��ٹ������ĵ��˾�����Ч�ڴ�����
    // ������ж��µ����Ƿ���Ч
    vector<Monster*>::iterator it;
    it=find(World::_monster.begin(),World::_monster.end(),_target);
    if (it!=World::_monster.end())
        _world->monsterDamaged(*it,_damage);
    _world->eraseBullet(this);
}
