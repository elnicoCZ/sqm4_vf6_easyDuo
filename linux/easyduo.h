#ifndef EASYDUO_H
#define EASYDUO_H

#include <QtGui/QMainWindow>
#include "ui_easyduo.h"

#include "easyplayer.h"
#include "CMcc.h"

class EasyDuo : public QMainWindow
{
    Q_OBJECT

public:
    EasyDuo(QWidget *parent = 0);
    ~EasyDuo();

private:
    Ui::EasyDuoClass    ui;
    EasyPlayer        * m_pEasyPlayer;
    QTimer              m_qTimerAccel;
    QTimer              m_qTimerMedia;
    CMcc              * m_poMcc;

    static void prgAccelSetValue(QProgressBar & qPrgBar, int val);
    static void cbxItemEnable(QComboBox & qCombo, int idx, bool bEnable);
    static bool fileExists(const char * sFilename);

    bool event(QEvent * ev);

private slots:
    void play ();
    void mute (bool bMute);
    void refreshMedia ();
    void refreshAccel ();
    void ledOn ();
    void ledOff ();
    void ledAuto ();

};

#endif // EASYDUO_H
