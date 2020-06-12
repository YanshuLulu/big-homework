#include "mw1.h"
#include "ui_mw1.h"
#include "icon.h"
#include <QTime>
#include <QTimer>
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
    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/listen to the wind.mp3"));
    player->setVolume(20);
    player->play();

    timer1 = new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(monsterMove()));
    connect(timer1,SIGNAL(timeout()),this,SLOT(updateMap()));

        //randomMove()为自定义槽函数
    timer1->start(50);
    timer1->setInterval(100);

    timer2=new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(loadWave()));
    timer2->start(50);
    timer2->setInterval(10000);

    int interval[]={1000,2000,3000,4000,5000};
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
    if(_game.lose||_game.win)
    {
        timer1->stop();
        timer2->stop();
        QPainter *p;
        p = new QPainter();
        p->begin(this);
        if(_game.win)
        {
            p->drawPixmap(0,0,width(),height(),QPixmap("../QTMap/win.png"));
        }else{
            p->drawPixmap(0,0,width(),height(),QPixmap("../QTMap/lose.png"));
        }
        return;
    }
}

void MW1::updateMap(){
    int n=World::_towers.size();
    for(int i=0;i<n;i++)
        World::_towers[i]->checkMonsterIn();
    this->repaint();
    this->update();
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
            Tower *t =new Tower((*it)->getPos());
            this->_game.addtower(t);
            break;
        }else if(flag1&&(!flag2)){
            (*it)->setPutTower(true);
            vector<Tower*>::iterator t;
            t=World::_towers.begin();
            while (t!=World::_towers.end()) {
                if((*it)->getPos()==(*t)->getPos())
                {
                    delete (*t);
                    World::_towers.erase(t);
                    break;
                }
                t++;
            }
        }
        else{
            it++;
        }
    }
    this->update();
}

/*bool MW1::event(QEvent *e)
{
    if(World::win||World::lose)
    {
        if(World::win)
            player->setMedia(QUrl("qrc:/sounds/win.mp3"));
        else
            player->setMedia(QUrl("qrc:/sounds/lose.mp3"));
        player->setVolume(30);
        player->play();
        return true;
    }
    return false;
}*/

void MW1::loadWave()
{
    if(_waves<6)
    {
        int interval[]={1000,2000,3000,4000,5000};
        for(int i=0;i<5;i++)
        {
            QTimer *timer = new QTimer(this);
            connect(timer,SIGNAL(timeout()),this,SLOT(drawMonster()));
            timer->start(50);
            timer->setInterval(interval[i]);
            timer->setSingleShot(true);
        }
        _waves++;
    }else{
        if(World::_monster.empty())
            _game.win=true;
    }
}

void MW1::monsterMove(){
    this->_game.MonsterMove();
}
