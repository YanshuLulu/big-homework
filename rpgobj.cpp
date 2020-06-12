#include "rpgobj.h"
#include <iostream>
#include <math.h>

void RPGObj::initObj(string type)
{
    //TODO 所支持的对象类型应定义为枚举
    if (type.compare("stone")==0){
        this->_coverable = true;
    }
    else if (type.compare("end")==0){
        this->_coverable = false;
    }
    else if (type.compare("monster")==0){
        this->_coverable = false;
    }
    else if (type.compare("towerpos")==0){
        this->_coverable = true;
    }
    /*else if (type.compare("tower")==0){
        this->_coverable = false;
    }*/
    else{
        //TODO 应由专门的错误日志文件记录
        cout<<"invalid ICON type."<<endl;
        return;
    }

    this->_icon = ICON::findICON(type);
    QImage all;

    all.load(":/pics/Tile.png");
    this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
}

void RPGObj::show(QPainter * pa){
    int gSize = ICON::GRID_SIZE;
    pa->drawImage(this->_pos.x()*gSize,this->_pos.y()*gSize,this->_pic);
}

/*int RPGObj::getNextX(int direction){
    switch (direction){
        case 1:
           return this->_pos.x();
        case 2:
           return this->_pos.x();
        case 3:
           return this->_pos.x()-1;
        case 4:
           return this->_pos.x()+1;
    }
}

int RPGObj::getNextY(int direction){
    switch (direction){
        case 1:
           return this->_pos.y() - 1;
        case 2:
           return this->_pos.y() + 1;
        case 3:
           return this->_pos.y();
        case 4:
           return this->_pos.y();
    }
}*/
