/** ****************************************************************************
 *
 *  @file       easyduo_mcc_common.h
 *  @brief      MCC common definitions for EasyDuo Linux/MQX applications.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.0 2014-11-08: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Initial version.
 *
 ******************************************************************************/
/*
 *  THIS SOFTWARE IS PROVIDED BY ELNICO "AS IS" AND ANY EXPRESSED OR
 *  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *  IN NO EVENT SHALL ELNICO OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 *  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 *  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *  THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

#ifndef EASYDUO_MCC_COMMON_H_957416452703645164651780502134
#define EASYDUO_MCC_COMMON_H_957416452703645164651780502134
//******************************************************************************

#if __linux__
# include <linux/mcc_config.h>
# include <stdint.h>
#else // ! __linux__ //
# include "mcc_config.h"
#endif // ! __linux__ //

#include <stddef.h>

//******************************************************************************
// Endpoints settings
//******************************************************************************

/** @def MCC_ENDPOINT_A5_CORE
 * @brief A5 core ID. For Vybrid, this should not be changed. */
#ifndef MCC_ENDPOINT_A5_CORE
# define MCC_ENDPOINT_A5_CORE           (0)
#endif
/** @def MCC_ENDPOINT_A5_NODE
 * @brief A5 node ID. Task-specific in Linux, system-specific in MQX. */
#ifndef MCC_ENDPOINT_A5_NODE
# define MCC_ENDPOINT_A5_NODE           (1)
#endif
/** @def MCC_ENDPOINT_A5_PORT
 * @brief A5 port ID. Arbitrary number except of MCC_RESERVED_PORT_NUMBER. */
#ifndef MCC_ENDPOINT_A5_PORT
# define MCC_ENDPOINT_A5_PORT           (1)
#endif

/** @def MCC_ENDPOINT_M4_CORE
 * @brief M4 core ID. For Vybrid, this should not be changed. */
#ifndef MCC_ENDPOINT_M4_CORE
# define MCC_ENDPOINT_M4_CORE           (1)
#endif
/** @def MCC_ENDPOINT_M4_NODE
 * @brief M4 node ID. Task-specific in Linux, system-specific in MQX. */
#ifndef MCC_ENDPOINT_M4_NODE
# define MCC_ENDPOINT_M4_NODE           (0)
#endif
/** @def MCC_ENDPOINT_M4_PORT
 * @brief M4 port ID. Arbitrary number except of MCC_RESERVED_PORT_NUMBER. */
#ifndef MCC_ENDPOINT_M4_PORT
# define MCC_ENDPOINT_M4_PORT           (3)
#endif

//******************************************************************************
// Message structure
//******************************************************************************

/** Multi-core communication message structure. */
typedef struct mcc_msg_struct {
  int32_t           type;                                                       //!< Message type.
  struct {
    int32_t         iDataX;                                                     //!< X-axis accelerometer data.
    int32_t         iDataY;                                                     //!< Y-axis accelerometer data.
    int32_t         iDataZ;                                                     //!< Z-axis accelerometer data.
  };
} TMccMsg;

//******************************************************************************
// Message values
//******************************************************************************

/** Multi-core communication message type. */
enum {
  MCCMSG_RESERVED = 0,                                                          //!< Reserved value not to be used.
  MCCMSG_LED_ON,                                                                //!< Set LED ON.
  MCCMSG_LED_OFF,                                                               //!< Set LED OFF.
  MCCMSG_LED_AUTO,                                                              //!< Drive LED automatically by M4.
  MCCMSG_ACCEL_DATA,                                                            //!< Request/send accelerometer data.
};

//******************************************************************************
// Other definitions
//******************************************************************************

#define MCC_WAIT_INF                (0xFFFFFFFF)                                //!< Wait delay constant for infinite wait.

//******************************************************************************
#endif // EASYDUO_MCC_COMMON_H_957416452703645164651780502134 //
