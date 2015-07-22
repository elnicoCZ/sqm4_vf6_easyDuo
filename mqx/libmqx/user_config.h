/*
 * Copyright (c) 2008, 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*!
 * @brief  User configuration for MQX components
 */

#ifndef __user_config_h__
#define __user_config_h__

/* MQX revision identification */
#define MQX_4_1_1_REV_1_4

/* mandatory CPU identification */
#define MQX_CPU                  PSP_CPU_VF65GS10_M4

/*
** BSP settings - for defaults see mqx\source\bsp\<board_name>\<board_name>.h
*/

#define BSPCFG_ENABLE_TTYA       1
#define BSPCFG_ENABLE_ITTYA      1
#define BSPCFG_ENABLE_TTYB       1
#define BSPCFG_ENABLE_ITTYB      1
#define BSPCFG_ENABLE_TTYC       1
#define BSPCFG_ENABLE_ITTYC      1
#define BSPCFG_ENABLE_TTYD       0
#define BSPCFG_ENABLE_ITTYD      0
#define BSPCFG_ENABLE_TTYE       0
#define BSPCFG_ENABLE_ITTYE      0
#define BSPCFG_ENABLE_TTYF       0
#define BSPCFG_ENABLE_ITTYF      0
#define BSPCFG_ENABLE_I2C0       1
#define BSPCFG_ENABLE_II2C0      1
#define BSPCFG_ENABLE_I2C1       0
#define BSPCFG_ENABLE_II2C1      0
#define BSPCFG_ENABLE_I2C2       0
#define BSPCFG_ENABLE_II2C2      0
#define BSPCFG_ENABLE_I2C3       0
#define BSPCFG_ENABLE_II2C3      0
#define BSPCFG_ENABLE_SPI0       1
#define BSPCFG_ENABLE_SPI1       0
#define BSPCFG_ENABLE_SPI2       0
#define BSPCFG_ENABLE_QUADSPI0   0
#define BSPCFG_ENABLE_RTCDEV     1
#define BSPCFG_ENABLE_PCFLASH    0
#define BSPCFG_ENABLE_NANDFLASH  0

// We set the default IO channel (e.g. printf) to UART1 here, as this is the only
// port available at EasyBoard without extension boards. Anyway, UART1 is reserved
// for the A5 core, M4 is supposed to use UART2. Just comment out the following
// definition to use UART2 (ttyc) for M4.
// Please visit www.sqm4.com to get an extension board with UART2 port.
//#define BSP_DEFAULT_IO_CHANNEL   "ttyb:"

#define BSPCFG_ENABLE_FLASHX     0
#define BSPCFG_ENABLE_ESDHC      1
#define BSPCFG_ENABLE_IODEBUG    0

#define BSPCFG_ENABLE_II2S0      0
#define BSPCFG_ENABLE_LWADC0     1
#define BSPCFG_ENABLE_LWADC1     0

#define MQX_USE_MEM              1
#define MQX_USE_LWMEM            1
//#define MQX_USE_UNCACHED_MEM     1
#define MQX_USE_LWMEM_ALLOCATOR  0
#define MQX_USE_TIMER            1

//#define BSPCFG_HAS_SRAM_POOL     1
#define BSPCFG_ENET_SRAM_BUF     1

/*
** board-specific MQX settings - see for defaults mqx\source\include\mqx_cnfg.h
*/

#define MQX_USE_IDLE_TASK               1
#define MQX_ENABLE_LOW_POWER            0

/*
** enable floating point
*/
#define MQXCFG_ENABLE_FP                1
#define MQX_INCLUDE_FLOATING_POINT_IO   1

// DS-5 memcpy is bugged so we have to use MQX implementation
#define MQXCFG_MEM_COPY          1
/*
** board-specific RTCS settings - see for defaults rtcs\source\include\rtcscfg.h
*/

#define RTCSCFG_ENABLE_ICMP      1
#define RTCSCFG_ENABLE_UDP       1
#define RTCSCFG_ENABLE_TCP       1
#define RTCSCFG_ENABLE_IGMP      1
#define RTCSCFG_ENABLE_STATS     1
#define RTCSCFG_ENABLE_GATEWAYS  1
#define FTPDCFG_USES_MFS         1
#define RTCSCFG_ENABLE_SNMP      0

#define TELNETDCFG_NOWAIT        FALSE

#define MQX_TASK_DESTRUCTION     1

#define HTTPDCFG_POLL_MODE       0
#define HTTPDCFG_STATIC_TASKS    0
#define HTTPDCFG_DYNAMIC_TASKS   1
#define MQX_IS_MULTI_PROCESSOR      1
#define MQX_USE_IPC                 1
#define BSP_DEFAULT_MAX_MSGPOOLS    8

#define ENETCFG_SUPPORT_PTP      0
#define ENET_IPADDR IPADDR(192,168,10,201)

/*
** include common settings
*/
#define RTCSCFG_ENABLE_IP_REASSEMBLY              1

/*-------------------------------------------------
** The Atheros Wifi settings.
*/
#define BSPCFG_ENABLE_ATHEROS_WIFI                1

#if BSPCFG_ENABLE_SPI0
/* in file name, number after : is the mask for chip select. chip select 0 in this case. */
#define BSP_ATHEROS_WIFI_SPI_DEVICE                 "spi0:1"
#else
#error "SPI0 must be defined in user_config.h"
#endif
#define BSP_ATHEROS_WIFI_GPIO_INT_PIN               (LWGPIO_PIN_PTB23)
#define BSP_INT_PIN_MUX_GPIO                        (LWGPIO_MUX_PTB23_GPIO)
#define BSP_ATHEROS_WIFI_GPIO_PWD_PIN               (LWGPIO_PIN_PTB13)
#define BSP_PWD_PIN_MUX_GPIO                        (LWGPIO_MUX_PTB13_GPIO)

/*-------------------------------------------------
**                      Ethernet Info
*/
#define BSP_DEFAULT_ENET_DEVICE             0
#define ATHEROS_WIFI_DEFAULT_ENET_DEVICE    0
#define BSP_DEFAULT_ENET_OUI                { 0x00, 0x00, 0x5E, 0, 0, 0 }
#define BSPCFG_RX_RING_LEN                  8
#define BSPCFG_TX_RING_LEN                  4
#define BSPCFG_ENABLE_ENET_MULTICAST        1
#define BSPCFG_ENABLE_ENET_STATS            1
#define BSPCFG_ENET_RESTORE                 1
#define BSPCFG_ENABLE_CPP                   0



/* use the rest of defaults from small-RAM-device profile */
#include "small_ram_config.h"

/* and enable verification checks in kernel */
#include "verif_enabled_config.h"

#endif /* __user_config_h__ */
