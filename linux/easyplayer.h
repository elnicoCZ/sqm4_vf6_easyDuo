#ifndef EASYPLAYER_H
#define EASYPLAYER_H

#include <QtGui>
#include <QtGui/QMainWindow>
#include "ui_easyplayer.h"

#include <sys/types.h>

class EasyPlayer : public QMainWindow
{
    Q_OBJECT

public:
    EasyPlayer(QWidget *parent = 0);
    ~EasyPlayer();

    void play (const QString & sPipeline, bool bLoop = false);

protected:
    QTimer  m_qTimer;
    QString m_sPipeline;
    pid_t   m_gstPid;
    bool    m_bLoop;

    pid_t execGst (const QString & sPipeline);

private:
    Ui::EasyPlayerClass ui;

    static void execute (const char * sFilename, const char * sArguments);

private slots:
    void killGst (void);
    void checkGst (void);

};

#endif // EASYPLAYER_H
