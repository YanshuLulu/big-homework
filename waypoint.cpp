#include "waypoint.h"

WayPoint::WayPoint(QPoint pos):_pos(pos),_nextWayPoint(NULL)
{
}
void WayPoint::setNextWayPoint(WayPoint *nextPoint)
{
    this->_nextWayPoint = nextPoint;
}
WayPoint* WayPoint::nextWayPoint() const
{
    return this->_nextWayPoint;
}
const QPoint WayPoint::pos() const
{
    return this->_pos;
}
void WayPoint::show(QPainter *painter) const
{
    painter->save();
    painter->setPen(QColor(0,255,0));
    painter->drawEllipse(this->_pos,6,6);
    painter->drawEllipse(this->_pos,2,2);
    if(this->_nextWayPoint)
        painter->drawLine(this->_pos,this->_nextWayPoint->_pos);
    painter->restore();
}
