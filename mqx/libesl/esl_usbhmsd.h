/** ****************************************************************************
 *
 *  @file       esl_usbhmsd.h
 *  @brief      USB Host functionality.
 *
 *  The esl_usbhmsd sub-module allows the application to access the connected
 *  USB mass storage devices.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Jan Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.1 2014-10-03: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Module released.
 *
 *  @version    1.0 2014-09-08: Jan Kubiznak <kubiznak.jan@elnico.cz>
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

#ifndef ESL_USBH_MSD_H_54312345732123454754234571
#define ESL_USBH_MSD_H_54312345732123454754234571

//******************************************************************************

#include "esl_usbh_config.h"

//******************************************************************************
// Platform check - available for K70 only
//******************************************************************************

#if ((ESL_USBH_MODULE_ENABLE) && (ESL_USBH_CLASS_MSD)) && \
    ((MQX_CPU != PSP_CPU_MK70F120M) && (MQX_CPU != PSP_CPU_MK70F150M))
# warning "USBHMSD module is only available for Kinetis K70 CPU"
# undef ESL_USBH_CLASS_MSD
# define ESL_USBH_CLASS_MSD           (0)
#endif // USBH && !K70 //

//******************************************************************************
// Module specific log IDs
//******************************************************************************

enum {
  ESL_USBH_MSD_OK                     = MQX_OK,
  ESL_USBH_MSD_INITFAIL,
  ESL_USBH_MSD_FORMAT_NEEDED,
  ESL_USBH_MSD_INVALID_ARG,
  ESL_USBH_MSD_IO_USB_MFS_INSTALL,
  ESL_USBH_MSD_IO_PART_MGR_INSTALL,
  ESL_USBH_MSD_IOCTL_VAL_PART,
  ESL_USBH_MSD_IO_MFS_INSTALL,
  ESL_USBH_MSD_FOPEN_FS,
  ESL_USBH_MSD_NULLPTR_FS,
  ESL_USBH_MSD_FCLOSE_FS,
  ESL_USBH_MSD_DEV_UNINSTALL_FS,
  ESL_USBH_MSD_FOPEN_PM,
  ESL_USBH_MSD_NULLPTR_PM,
  ESL_USBH_MSD_FCLOSE_PM,
  ESL_USBH_MSD_DEV_UNINSTALL_PM,
  ESL_USBH_MSD_FOPEN_DEV,
  ESL_USBH_MSD_NULLPTR_DEV,
  ESL_USBH_MSD_FCLOSE_DEV,
  ESL_USBH_MSD_DEV_UNINSTALL_DEV,
  ESL_USBH_MSD_LWSEM_POLL,
  ESL_USBH_MSD_LWSEM_WAIT_TICKS,
  ESL_USBH_MSD_DEVICE_DETACHED,
  ESL_USBH_MSD_MODULE_OFF
};

//******************************************************************************
// State information
//******************************************************************************

#define ESL_USBH_MSD_STATE_DETACHED        (0)                                  //!< USB MSD State: Detached, i.e. not connected.
#define ESL_USBH_MSD_STATE_ATTACHED        (1)                                  //!< USB MSD State: Attached, i.e. connected, but FS not installed.
#define ESL_USBH_MSD_STATE_INTERFACED      (2)                                  //!< USB MSD State: Interfaced, i.e. connected and FS installed.
#define ESL_USBH_MSD_STATE_NEEDFORMAT      (3)                                  //!< USB MSD State: NeedFormat, i.e. FS of connected USB is not accessible, device needs to be formatted.

/** Module state information structure. */
typedef struct {
  uint8_t              u8State;                                                 //!< If USB device is inserted or not.
  uint8_t              u8Updated;                                               //!< If the USB device state was updated.
} esl_usbhmsd_state;

//******************************************************************************
// State information
//******************************************************************************

#define ESL_USBH_MSD_LABEL_NAMELEN         (12)                                 //!< Device label name length (from IO_IOCTL_GET_VOLUME)

//******************************************************************************
// Module public functions.
//******************************************************************************

/** USB Host control task for mass storage devices. The task installs/uninstalls
 * file system (MFS) for USB devices when they're plugged in/out.
 * @param [in]  u32InitialData Task initial data. */
void esl_usbhmsd_task (uint_32 u32InitialData);

/** Call this interface to obtain the USB device file system handle. That is
 * needed to be able to perform actions on USB FS using the esl_fs module.
 * @param  [in] u8DevIdx   Index of a USB device, which state is to be obtained.
 *                         A value smaller than ESL_USBH_MSD_MAXDEVCNT is
 *                         expected.
 * @return                 Handle to the particular USB file system on success,
 *                         NULL on failure. */
MQX_FILE * esl_usbhmsd_getHandle (uint8_t   u8DevIdx);

/** Getter of the module state information.
 * @param [out] poState   Pointer to a state information object, which to store
 *                        the obtained data to.
 * @param [in]  u8DevIdx  Index of a USB device, which state is to be obtained.
 *                        A value smaller than ESL_USBH_MSD_MAXDEVCNT is
 *                        expected.
 * @param [in]  iMaxWait   Maximal wait in msec to wait for the access to the
 *                         module state critical section. Use (-1) for no wait,
 *                         but just a poll. Use (0) for infinite wait.
 * @param [out] err        Aditional information about error in case of failure.
 * @return                 ESL_USBH_MSD_OK if success,
 *                         ESL_USBH_MSD_LWSEM_WAIT_TICKS if critical section was
 *                         unable to be entered in the given wait time,
 *                         other ESL_USBH_MSD_* value in case of failure. */
uint8_t esl_usbhmsd_getState (esl_usbhmsd_state   * poState,
                              uint8_t               u8DevIdx,
                              _mqx_int              iMaxWait,
                              _mqx_uint           * err);

/** Getter of the module state information.
 * @param [out] apoState[] Pointer to an array of state information objects,
 *                         which to store the obtained data to. This array must
 *                         have the length of ESL_USBH_MSD_MAXDEVCNT.
 * @param [in]  iMaxWait   Maximal wait in msec to wait for the access to the
 *                         module state critical section. Use (-1) for no wait,
 *                         but just a poll. Use (0) for infinite wait.
 * @param [out] err        Aditional information about error in case of failure.
 * @return                 ESL_USBH_MSD_OK if success,
 *                         ESL_USBH_MSD_LWSEM_WAIT_TICKS if critical section was
 *                         unable to be entered in the given wait time,
 *                         other ESL_USBH_MSD_* value in case of failure. */
uint8_t esl_usbhmsd_getStateAll (esl_usbhmsd_state (* paoState)[ESL_USBH_MSD_MAXDEVCNT],
                                 _mqx_int             iMaxWait,
                                 _mqx_uint          * err);

/** Getter of the drive file system name string.
 * @param [in]  u8DevIdx   Index of a USB device, which drive name is to be
 *                         obtained. A value smaller than ESL_USBH_MSD_MAXDEVCNT
 *                         is expected.
 * @param [out] err        Aditional information about error in case of failure.
 * @return                 Pointer to drive name on success, NULL on failure. */
const char * esl_usbhmsd_getDriveName (uint8_t u8DevIdx, _mqx_uint * err);

/** Getter of the drive label string.
 * @param [out] sLabel     Output USB device label string.
 * @param [in]  u8DevIdx   Index of a USB device, which drive label is to be
 *                         obtained. A value smaller than ESL_USBH_MSD_MAXDEVCNT
 *                         is expected.
 * @param [out] err        Aditional information about error in case of failure.
 * @return                 ESL_USBH_MSD_OK if success,
 *                         ESL_USBH_MSD_DEVICE_DETACHED if device is not attached
 *                         other ESL_USBH_MSD_* value in case of failure. */
uint8_t esl_usbhmsd_getDriveLabel (char       (* psLabel)[ESL_USBH_MSD_LABEL_NAMELEN],
                                   uint8_t       u8DevIdx,
                                   _mqx_uint   * err);

//******************************************************************************
#endif //ESL_USBH_MSD_H_54312345732123454754234571