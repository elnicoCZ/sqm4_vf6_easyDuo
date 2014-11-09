/*
 * CMcc.h
 *
 *  Created on: Nov 9, 2014
 *      Author: petr
 */

#ifndef CMCC_H_
#define CMCC_H_
//******************************************************************************

extern "C"
{
#include <linux/mcc_config.h>
#include <linux/mcc_common.h>
#include <mcc_api.h>
}
#include "../common/easyduo_mcc_common.h"

//******************************************************************************
// Return values
//******************************************************************************

enum {
  MCC_OK                          = 0,
  MCC_INIT_FAILURE,
  MCC_INFO_FAILURE,
  MCC_VERSION_FAILURE,
  MCC_ENDPOINT_FAILURE,
  MCC_SEND_FAILURE,
  MCC_RECV_FAILURE,
  MCC_FREE_FAILURE,
};

//******************************************************************************

class CMcc {
public:
  CMcc (MCC_NODE iNode, MCC_PORT iPort);

  int setLedOn (void);
  int setLedOff (void);
  int setLedAuto (void);

protected:
  static MCC_ENDPOINT s_mccEndpointLocal;
  static MCC_ENDPOINT s_mccEndpointRemote;

  int sendMsg (TMccMsg & oMsg);
};

//******************************************************************************
#endif /* CMCC_H_ */
