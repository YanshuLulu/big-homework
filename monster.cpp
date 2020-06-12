#include "monster.h"
#include "tower.h"

/*Monster::Monster(WayPoint *startWayPoint):RPGObj(),_destination(*startWayPoint->nextWayPoint())
{
    //this->_destination=startWayPoint->nextWayPoint();
}*/
//direction =1,2,3,4 for сробиовС

void Monster::move(int direction, int steps){
    switch (direction){
        case 1:
            this->_pos.rx() += steps;
            break;
        case 2:
            this->_pos.ry() += steps;
            break;
        case 3:
            this->_pos.ry() -= steps;
            break;
        case 4:
            this->_pos.rx() -= steps;
            break;
    }
}
void Monster::onErase(){
    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/crash.mp3"));
    player->setVolume(5);
    player->play();
}
void Monster::show(QPainter *painter)
{
    if(!_active)
        return;
    int gSize = ICON::GRID_SIZE;
    static const int Health_Bar_Width = 50;
    painter->drawImage(this->_pos.x()*gSize,this->_pos.y()*gSize,this->_pic);
    painter->save();
    QPoint healthBarPoint = this->_pos*5 + QPoint(0,-10);
    //painter->setPen(Qt::NoPen);
    if(currentHP<maxHP)
        painter->setBrush(Qt::red);
    else
        painter->setBrush(Qt::green);
    QRect currentBarBackRect(healthBarPoint, QSize(Health_Bar_Width*currentHP/maxHP, 5));
    painter->drawRect(currentBarBackRect);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::black);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 5));
    painter->drawRect(healthBarBackRect);
    painter->restore();
}
void Monster::lostSight(Tower *t)
{
    vector<Tower *>::iterator it;
    it=find(_attackers.begin(),_attackers.end(),t);
    if(it==_attackers.end())
        return;
    else {
        this->_attackers.erase(it);
    }
}
void Monster::getDamage(int damage)
{
    currentHP-=damage;
}

