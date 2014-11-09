/*
 * CMcc.cpp
 *
 *  Created on: Nov 9, 2014
 *      Author: petr
 */

#include "CMcc.h"

#include <stdio.h>
#include <string.h>

//******************************************************************************
// Static initializers
//******************************************************************************

MCC_ENDPOINT CMcc::s_mccEndpointLocal;                                          //!< Local EasyDuo MCC endpoint.
MCC_ENDPOINT CMcc::s_mccEndpointRemote = { MCC_ENDPOINT_M4_CORE,
                                           MCC_ENDPOINT_M4_NODE,
                                           MCC_ENDPOINT_M4_PORT };              //!< Remote EasyDuo MCC endpoint.

//******************************************************************************
//******************************************************************************
//******************************************************************************

CMcc::CMcc (MCC_NODE iNode, MCC_PORT iPort)
{
  MCC_INFO_STRUCT   mccInfo;
  int               ret;

  ret = mcc_initialize(iNode);
  if (MCC_SUCCESS != ret) {
    printf("mcc_initialize failed: %d\n", ret);
    throw MCC_INIT_FAILURE;
  }

  ret = mcc_get_info(iNode, &mccInfo);
  if (MCC_SUCCESS != ret) {
    printf("mcc_get_info failed: %d\n", ret);
    mcc_destroy(iNode);
    throw MCC_INFO_FAILURE;
  } else if (strncmp(mccInfo.version_string, MCC_VERSION_STRING, 3) != 0) {     // compare first 3 bytes (major number)
    printf("MCC Library versions do not match ('%s' vs '%s')\n",
           mccInfo.version_string, MCC_VERSION_STRING);
    mcc_destroy(iNode);
    throw MCC_VERSION_FAILURE;
  } else {
    printf("MCC version %s loaded\n", mccInfo.version_string);
  }

  ret = mcc_create_endpoint(&CMcc::s_mccEndpointLocal, iPort);
  if (MCC_SUCCESS != ret) {
    printf("mcc_create_endpoint() failed: %d, node,port: %d, %d\n",
           ret, iNode, iPort);
    throw MCC_ENDPOINT_FAILURE;
  }
}

//******************************************************************************

int CMcc::sendMsg (TMccMsg & oMsg)
{
  int ret;

  ret = mcc_send(&CMcc::s_mccEndpointRemote, &oMsg, sizeof(oMsg), 0);           // non-blocking call
  if (MCC_SUCCESS != ret) {
    printf("mcc_send failed: %d\n", ret);
    return MCC_SEND_FAILURE;
  }
  return MCC_OK;
}

//******************************************************************************

int CMcc::setLedOn (void)
{
  TMccMsg oMsg;

  oMsg.type = MCCMSG_LED_ON;
  return this->sendMsg(oMsg);
}

//******************************************************************************

int CMcc::setLedOff (void)
{
  TMccMsg oMsg;

  oMsg.type = MCCMSG_LED_OFF;
  return this->sendMsg(oMsg);
}

//******************************************************************************

int CMcc::setLedAuto (void)
{
  TMccMsg oMsg;

  oMsg.type = MCCMSG_LED_AUTO;
  return this->sendMsg(oMsg);
}

//******************************************************************************
