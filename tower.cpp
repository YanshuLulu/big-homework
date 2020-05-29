#include "tower.h"


void Tower::show(QPainter * pa){
    int gSize = ICON::GRID_SIZE;
    pa->drawImage(this->_pos.x()*gSize,this->_pos.y()*gSize,this->_pic);
    pa->save();
    pa->setPen(Qt::white);
    QPoint p(this->_pos.x()*5+25,this->_pos.y()*5+25);
    pa->drawEllipse(p,_attackRange,_attackRange);
    pa->restore();
}
