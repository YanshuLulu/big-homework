#-------------------------------------------------
#
# Project created by QtCreator 2018-04-17T13:10:05
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTMap
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    mw1.cpp \
    icon.cpp \
    rpgobj.cpp \
    world.cpp \
    monster.cpp \
    end.cpp \
    waypoint.cpp \
    towerpos.cpp \
    tower.cpp \
    bullet.cpp

HEADERS  += \
    mw1.h \
    icon.h \
    rpgobj.h \
    world.h \
    end.h \
    waypoint.h \
    towerpos.h \
    bullet.h \
    tower.h \
    monster.h

FORMS    += \
    mw1.ui

DISTFILES += \
    ../../Downloads/3.3.28 �������� jc .docx \
    ../../Downloads/3619.txt

RESOURCES += \
    game.qrc
