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
    const QList<QNetworkAddressEntry> & oAddrList = oIF.addressEntries();
    if (!oAddrList.empty()) {
      sOut = oAddrList[0].ip().toString();
      sOut.append("/");
      sOut.append(QString("%1").arg(oAddrList[0].prefixLength()));
      return 0;
    }
    return -2;
  } else {
    return -1;
  }
}
