/*
 * network.h
 *
 *  Created on: Nov 4, 2014
 *      Author: petr
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include <QtGui>

/** Retrieves IP address string of given interface.
 * @param[out]  sOut  Destination string.
 * @param[in]   sIF   Interface name, e.g. "eth0".
 * @return      0 on success.
 *              Any other value on failure. */
int network_getIpStr(QString & sOut, const char * sIF);

#endif /* NETWORK_H_ */
