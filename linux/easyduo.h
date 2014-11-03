#ifndef EASYDUO_H
#define EASYDUO_H

#include <QtGui/QMainWindow>
#include "ui_easyduo.h"

class EasyDuo : public QMainWindow
{
    Q_OBJECT

public:
    EasyDuo(QWidget *parent = 0);
    ~EasyDuo();

private:
    Ui::EasyDuoClass ui;
};

#endif // EASYDUO_H
