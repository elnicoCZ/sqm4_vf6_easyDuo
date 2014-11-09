#include "easyduo.h"

#include "config.h"
#include "network.h"
#include "alsa.h"
#include "../common/easyduo_mcc_common.h"

#include <unistd.h>

//******************************************************************************

#define TIMER_DELAY_ACCEL               (50)
#define TIMER_DELAY_MEDIA               (1000)

//******************************************************************************

EasyDuo::EasyDuo(QWidget *parent)
    : QMainWindow(parent), m_poMcc(NULL)
{
  QString sIp;

  ui.setupUi(this);

  if (0 == network_getIpStr(sIp, "eth0")) {
    ui.lblIpAddress->setText(sIp);
  }

  config_loadMedia(*ui.cbxMedia, "easyduo.cfg");

  try {
    m_poMcc = new CMcc(MCC_ENDPOINT_A5_NODE, MCC_ENDPOINT_A5_PORT);
  } catch (...) {
    printf("mcc initialization failed");
  }
  m_pEasyPlayer = new EasyPlayer();

  connect(&m_qTimerAccel, SIGNAL(timeout()), this, SLOT(refreshAccel()));
  m_qTimerAccel.start(TIMER_DELAY_ACCEL);
  connect(&m_qTimerMedia, SIGNAL(timeout()), this, SLOT(refreshMedia()));
  m_qTimerMedia.start(TIMER_DELAY_MEDIA);
}

//******************************************************************************

EasyDuo::~EasyDuo()
{
  this->ledAuto();
  delete m_poMcc;
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

void EasyDuo::refreshAccel (void)
{
  TAccelData  oAccelData;
  int         ret;

  if (m_poMcc) {
    ret = m_poMcc->getAccelData(&oAccelData);
    if (MCC_OK == ret) {
      printf("getAccelData: %d %d %d\n", oAccelData.x, oAccelData.y, oAccelData.z);
      ui.prgAccelX->setValue(oAccelData.x);
      ui.prgAccelY->setValue(oAccelData.y);
      ui.prgAccelZ->setValue(oAccelData.z);
    } else {
      // just to see that MCC communication is broken
      ui.prgAccelX->setValue(-1);
      ui.prgAccelY->setValue(0);
      ui.prgAccelZ->setValue(1);
    }
  }
}

//******************************************************************************

void EasyDuo::refreshMedia (void)
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

void EasyDuo::ledOn ()
{
  if (m_poMcc) m_poMcc->setLedOn();
}

//******************************************************************************

void EasyDuo::ledOff ()
{
  if (m_poMcc) m_poMcc->setLedOff();
}

//******************************************************************************

void EasyDuo::ledAuto ()
{
  if (m_poMcc) m_poMcc->setLedAuto();
}

//******************************************************************************
