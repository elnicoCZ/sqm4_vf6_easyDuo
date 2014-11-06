#include "easyduo.h"

#include "config.h"
#include "network.h"

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
}

//******************************************************************************

EasyDuo::~EasyDuo()
{
  delete m_pEasyPlayer;
}

//******************************************************************************

void EasyDuo::play (void)
{
  printf ("%d:'%s', '%s'\n",
      ui.cbxMedia->currentIndex(),
      ui.cbxMedia->currentText().toStdString().c_str(),
      ui.cbxMedia->itemData(ui.cbxMedia->currentIndex()).toString().toStdString().c_str());
  m_pEasyPlayer->play(ui.cbxMedia->itemData(ui.cbxMedia->currentIndex()).toString(),
                      ui.chbxLoop->isChecked());
}

//******************************************************************************
