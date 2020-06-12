#ifndef MW1_H
#define MW1_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include "rpgobj.h"
#include "world.h"
#include "waypoint.h"

namespace Ui {
class MW1;
}

class MW1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MW1(QWidget *parent = 0);
    ~MW1();
    void paintEvent(QPaintEvent *e);
    //void keyPressEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *e);
    //bool event(QEvent *e);
protected slots:
    void loadWave();
    void monsterMove();
    void updateMap();
    void drawMonster(){_game.addMonsters();this->repaint();}

private:
    Ui::MW1 *ui;
    World _game;
    QTimer *timer1,*timer2;
    QMediaPlayer *player;
    int _waves=0;
};

#endif // MW1_H
