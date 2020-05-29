#include "monster.h"

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
    player->setVolume(30);
    player->play();
}
/*void Monster::show(QPainter *painter)
{
    int gSize = ICON::GRID_SIZE;
    painter->drawImage(this->_pos.x()*gSize,this->_pos.y()*gSize,this->_pic);
}*/
