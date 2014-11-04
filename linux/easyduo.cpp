#include "easyduo.h"

#include "config.h"
#include "network.h"

EasyDuo::EasyDuo(QWidget *parent)
    : QMainWindow(parent)
{
  QString sIp;

  ui.setupUi(this);

  if (0 == network_getIpStr(sIp, "eth0")) {
    ui.lblIpAddress->setText(sIp);
  }

  config_loadMedia(*ui.cbxMedia, "easyduo.cfg");
}

EasyDuo::~EasyDuo()
{

}
