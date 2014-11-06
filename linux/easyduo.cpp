#include "easyduo.h"

#include "config.h"
#include "network.h"
#include "alsa.h"

#include <unistd.h>

//******************************************************************************

#define TIMER_DELAY                     1000

//******************************************************************************

EasyDuo::EasyDuo(QWidget *parent)
    : QMainWindow(parent)
{
  QString sIp;

  ui.setupUi(this);

  if (0 == network_getIpStr(sIp, "eth0")) {
    ui.lblIpAddress->setText(sIp);
  }

  config_loadMedia(*ui.cbxMedia, "easyduo.cfg");

  m_pEasyPlayer = new EasyPlayer();

  connect(&m_qTimer, SIGNAL(timeout()), this, SLOT(refresh()));
  m_qTimer.start(TIMER_DELAY);
}

//******************************************************************************

EasyDuo::~EasyDuo()
{
  delete m_pEasyPlayer;
}

//******************************************************************************

void EasyDuo::play (void)
{
  const QList<QVariant> & qList = ui.cbxMedia->itemData(ui.cbxMedia->currentIndex()).toList();

  if (qList.isEmpty()) return;

  printf ("%d: '%s', '%s'\n",
      ui.cbxMedia->currentIndex(),
      ui.cbxMedia->currentText().toStdString().c_str(),
      qList[0].toString().toStdString().c_str());

  m_pEasyPlayer->play(qList[0].toString().toStdString().c_str(),
                      ui.chbxLoop->isChecked());
}

//******************************************************************************

void EasyDuo::refresh (void)
{
  for (int i=0; i<ui.cbxMedia->count(); ++i) {
    const QList<QVariant> & qList = ui.cbxMedia->itemData(i).toList();
    if (qList.size() >= 2) {
      bool bExists = EasyDuo::fileExists(qList[1].toString().toStdString().c_str());
      EasyDuo::cbxItemEnable(*ui.cbxMedia, i, bExists);
    }
  }
}

//******************************************************************************

void EasyDuo::cbxItemEnable(QComboBox & qCombo, int idx, bool bEnable)
{
  // dirty hack from https://qt-project.org/forums/viewthread/27969
  if (bEnable) {
    qCombo.setItemData(idx, QVariant(33), Qt::UserRole - 1);
  } else {
    qCombo.setItemData(idx, QVariant(0), Qt::UserRole - 1);
    if (qCombo.currentIndex() == idx) qCombo.setCurrentIndex(-1);
  }
}

//******************************************************************************

bool EasyDuo::fileExists(const char * sFilename)
{
  return (access(sFilename, F_OK) != -1);
}

//******************************************************************************

void EasyDuo::mute (bool bMute)
{
  alsa_muteSpeaker(bMute);
}

//******************************************************************************
