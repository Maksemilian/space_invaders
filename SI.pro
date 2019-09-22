#-------------------------------------------------
#
# Project created by QtCreator 2019-08-31T17:32:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SI
TEMPLATE = app
DEFINES +=QT_MESSAGELOGCONTEXT
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        main_window.cpp \
    player.cpp \
    enemy.cpp \
    bulet.cpp \
    enemy_group.cpp

HEADERS += \
        main_window.h \
    player.h \
    enemy.h \
    constant.h \
    bulet.h \
    enemy_group.h

FORMS += \
        mainwindow.ui

RESOURCES +=  res.qrc

DISTFILES += \
    resources/images/missile_enemy.png \
    resources/images/missile_player.png \
    resources/images/ship_enemy.png \
    resources/images/ship_player.png \
    resources/images/space_background.png
