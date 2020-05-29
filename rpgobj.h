#ifndef RPGOBJ_H
#define RPGOBJ_H
#include <QMediaPlayer>
#include <QImage>
#include <QPainter>
#include <string>
#include <icon.h>
#include <map>
using namespace std;
class RPGObj
{
public:
    RPGObj(){}

    void initObj(string type);
    void show(QPainter * painter);
    void move(int direction, int steps=1);

    void setPosX(int x){this->_pos.setX(x);}
    void setPosY(int y){this->_pos.setY(y);}

    int getPosX() const{return this->_pos.x();}
    int getPosY() const{return this->_pos.y();}
    QPoint getPos() const{return this->_pos;}
    int getHeight() const{return this->_icon.getHeight();}
    int getWidth() const{return this->_icon.getWidth();}

    bool canCover() const{return this->_coverable;}

    int getNextX(int direction);
    int getNextY(int direction);

    virtual void onErase();

    string getObjType() const{return this->_icon.getTypeName();}//返回类名

protected:
    //所有坐标，单位均为游戏中的格

    QImage _pic;
    QPoint _pos;//该物体在游戏中当前位置（左上角坐标）
    ICON _icon;//可以从ICON中获取对象的素材，尺寸等信息
    bool _coverable;
};

#endif // RPGOBJ_H
