#include "mw1.h"
#include "ui_mw1.h"
#include "icon.h"
#include <QTime>
#include<QTimer>
#include <map>
#include <iostream>

using namespace std;

MW1::MW1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MW1)
{
    ui->setupUi(this);

    //init game world
    _game.initWorld("");//TODO 应该是输入有效的地图文件

    timer1 = new QTimer(this);
    //connect(timer1,SIGNAL(timeout()),this,SLOT(randomMove()));
    connect(timer1,SIGNAL(timeout()),this,SLOT(monsterMove()));

        //randomMove()为自定义槽函数
    timer1->start(50);
    timer1->setInterval(500);

    int interval[]={2000,4000,6000,8000,10000};
    for(int i=0;i<5;i++)
    {
        QTimer *timer = new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(drawMonster()));
        timer->start(50);
        timer->setInterval(interval[i]);
        timer->setSingleShot(true);
    }

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));//设置随机种子
}

MW1::~MW1()
{
    delete ui;
}

void MW1::paintEvent(QPaintEvent *e){
    QPainter *pa;
    pa = new QPainter();
    pa->begin(this);
    pa->drawPixmap(0,0,width(),height(),QPixmap("../QTMap/background.png"));
    this->_game.show(pa);
    pa->end();
    delete pa;
}

void MW1::showTower(){
    this->repaint();
}

/*void MW1::keyPressEvent(QKeyEvent *e)
{
    //direction = 1,2,3,4 for 上下左右
    if(e->key() == Qt::Key_A)
    {
        this->_game.handlePlayerMove(3,1);
    }
    else if(e->key() == Qt::Key_D)
    {
        this->_game.handlePlayerMove(4,1);
    }
    else if(e->key() == Qt::Key_W)
    {
        this->_game.handlePlayerMove(1,1);
    }
    else if(e->key() == Qt::Key_S)
    {
         this->_game.handlePlayerMove(2,1);
    }
    this->repaint();
}*/

void MW1::mousePressEvent(QMouseEvent *e)
{
    QPoint pressPos = e->pos();
    vector<TowerPos*>::iterator it;
    it=this->_game._towerpos.begin();
    while (it!=this->_game._towerpos.end()) {
        bool flag1=(*it)->inArea(pressPos);
        bool flag2=(*it)->canPutTower();
        if(flag1&&flag2){
            (*it)->setPutTower(false);
            Tower *t =new Tower;
            t->initObj("tower");
            t->setPosX((*it)->getPosX());
            t->setPosY((*it)->getPosY());
            this->_game.addtower(t);
            break;
        }else{
            it++;
        }
    }
    this->update();
}

void MW1::monsterMove(){
    this->_game.MonsterMove();
    this->repaint();
}

void MW1::drawMonster(){
    this->_game.addMonsters();
    this->repaint();
}
