/*
 * network.cpp
 *
 *  Created on: Nov 4, 2014
 *      Author: petr
 */

#include "network.h"

#include <QNetworkInterface>

int network_getIpStr (QString & sOut, const char * sIF) {
  QNetworkInterface oIF = QNetworkInterface::interfaceFromName(sIF);

  sOut = "0.0.0.0";
  if (oIF.isValid()) {
    sOut = oIF.addressEntries()[0].ip().toString();
    return 0;
  } else {
    return -1;
  }
}
