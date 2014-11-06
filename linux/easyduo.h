#ifndef EASYDUO_H
#define EASYDUO_H

#include <QtGui/QMainWindow>
#include "ui_easyduo.h"

#include "easyplayer.h"

class EasyDuo : public QMainWindow
{
    Q_OBJECT

public:
    EasyDuo(QWidget *parent = 0);
    ~EasyDuo();

private:
    Ui::EasyDuoClass    ui;
    EasyPlayer        * m_pEasyPlayer;

private slots:
    void play();

};

#endif // EASYDUO_H
