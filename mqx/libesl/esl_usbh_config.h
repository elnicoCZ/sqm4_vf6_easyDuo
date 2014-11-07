/** ****************************************************************************
 *
 *  @file       esl_usbh_config.h
 *  @brief      USB Host functionality.
 *
 *  Configuration of the USB Host module.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Jan Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.2 2014-10-07: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Warning for Bug #181 added.
 *  
 *  @version    1.1 2014-10-03: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Module released.
 *
 *  @version    1.0 2012-09-08: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Initial revision
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

#ifndef ESL_USBH_CONFIG_H_21543212403545312044556715
#define ESL_USBH_CONFIG_H_21543212403545312044556715
//******************************************************************************

#include "esl_config.h"

//******************************************************************************
// Main module settings
//******************************************************************************

/** @def ESL_USBH_MODULE_ENABLE
 * @brief Set 1/0 to get module enabled or disabled. */
#ifndef ESL_USBH_MODULE_ENABLE
# define ESL_USBH_MODULE_ENABLE               (0)
#endif

//******************************************************************************
// USB Host classes
//******************************************************************************

/** @def ESL_USBH_CLASS_MSD
 * @brief Set 1/0 to enable the MSD functionality or not. */
#ifndef ESL_USBH_CLASS_MSD
# define ESL_USBH_CLASS_MSD                   (0)
#endif

/** @def ESL_USBH_CLASS_HUB
 * @brief Set 1/0 to enable the HUB functionality or not. */
#ifndef ESL_USBH_CLASS_HUB
# define ESL_USBH_CLASS_HUB                   (0)
#endif

//******************************************************************************
// USB Host MSD task information
//******************************************************************************

/** @def ESL_USBH_MSD_TASK_STACK
 * @brief USB MSD task stack size. */
#ifndef ESL_USBH_MSD_TASK_STACK
# define ESL_USBH_MSD_TASK_STACK              (2500)
#endif

/** @def ESL_USBH_MSD_TASK_STR
 * @brief USB MSD task name - should be unique! */
#ifndef ESL_USBH_MSD_TASK_STR
# define ESL_USBH_MSD_TASK_STR                "eslUsbHostMsd"
#endif

//******************************************************************************
// USB Host MSD configuration
//******************************************************************************

/** @def ESL_USBH_MSD_MAXDEVCNT
 * @brief Supported count of USB MSD devices.
 * @warning Bug #181: The maximal amount of file systems (nand, sd, usb, ...) is
 * hardcoded in the MAX_FS_INSTANCES macro in MQX fio.h. Therefore a higher
 * number of USB devices might not really work as expected. In such case it's
 * possible to hack the MAX_FS_INSTANCES value and build a custom MQX BSP. */
#ifndef ESL_USBH_MSD_MAXDEVCNT
# define ESL_USBH_MSD_MAXDEVCNT               (1)
#endif

/** @def ESL_USBH_MSD_DEVICE_NAME
 * @brief USB device identifier root part. The real name of the mounted device
 * will be extended by the slot number in range from 0 to ESL_USBH_MSD_MAXDEVCNT
 * and ":" Example: "usb0:". Needs to be unique in the IO subsystem. */
#ifndef ESL_USBH_MSD_DEVICE_NAME
# define ESL_USBH_MSD_DEVICE_NAME             "usb"
#endif

/** @def ESL_USBH_MSD_PARTMGR_NAME
 * @brief USB device partition manager identifier root part. The real name of
 * the mounted partition manager will be extended by the slot number in range
 * from 0 to ESL_USBH_MSD_MAXDEVCNT and ":". Example: "usbpm0:". Needs to be
 * unique in the IO subsystem. */
#ifndef ESL_USBH_MSD_PARTMGR_NAME
# define ESL_USBH_MSD_PARTMGR_NAME            "usbpm"
#endif

/** @def ESL_USBH_MSD_FS_NAME
 * @brief USB device file system identifier root part. The real name of the
 * mounted file system will be extended by the slot number in range from 0 to
 * ESL_USBH_MSD_MAXDEVCNT and ":". Example: "usbfs0:". Needs to be unique in the
 * IO subsystem. */
#ifndef ESL_USBH_MSD_FS_NAME
# define ESL_USBH_MSD_FS_NAME                 "usbfs"
#endif

/** @def ESL_USBH_MSD_POWER_PIN
 * @brief LWGPIO Power pin. */
#ifndef ESL_USBH_MSD_POWER_PIN
# define ESL_USBH_MSD_POWER_PIN               (LWGPIO_PORT_D | LWGPIO_PIN6)
#endif

/** @def ESL_USBH_MSD_POWER_MUX_GPIO
 * @brief LWGPIO Power multiplexor. */
#ifndef ESL_USBH_MSD_POWER_MUX_GPIO
# define ESL_USBH_MSD_POWER_MUX_GPIO          (LWGPIO_MUX_D6_GPIO)
#endif

/** @def ESL_USBH_MSD_POWER_ON
 * @brief Mapping of the "Power On" state to the HW pin level. */
#ifndef ESL_USBH_MSD_POWER_ON
# define ESL_USBH_MSD_POWER_ON                (LWGPIO_VALUE_HIGH)
#endif

/** @def ESL_USBH_MSD_POWER_OFF
 * @brief Mapping of the "Power Off" state to the HW pin level. */
#ifndef ESL_USBH_MSD_POWER_OFF
# define ESL_USBH_MSD_POWER_OFF               (LWGPIO_VALUE_LOW)
#endif

//******************************************************************************
#endif /* ESL_USBH_CONFIG_H_21543212403545312044556715 */
