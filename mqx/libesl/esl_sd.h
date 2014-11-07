/** ****************************************************************************
 *
 *  @file       esl_sd.h
 *  @brief      SD-card task
 *
 *  Provides access to the SD-card and filesystem on it.
 *  HW-dependent functionality.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Jan Kubiznak <kubiznak.jan@elnico.cz>
 *
 *  @version    2.3 2014-09-03: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Interface for state monitoring added.
 *
 *  @version    2.2 2014-08-31: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Module restructuring.
 *
 *  @version    2.1 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    2.0 2013-11-21: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Module integrated into ESL.
 *
 *  @version    1.1 2012-12-21: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Adaption for ns150.
 *
 *  @version    1.0 2012-02-08: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Initial sdcard version.
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

#ifndef ESL_SD_H_46277689278467087609329408
#define ESL_SD_H_46277689278467087609329408
//******************************************************************************

#include "esl_sd_config.h"

#include <mqx.h>
#include <bsp.h>

//******************************************************************************
// Module error codes.
//******************************************************************************

enum {
  ESL_SD_OK = MQX_OK,
  ESL_SD_MODULE_OFF,
  ESL_SD_INV_ARG,
  ESL_SD_FOPEN_COMCHANNEL,
  ESL_SD_LWGPIO_INIT,
  ESL_SD_SDCARD_INSTALL,
  ESL_SD_FOPEN_SDDEV,
  ESL_SD_IOCTL_SET_FLAGS,
  ESL_SD_PART_MGR_INSTALL,
  ESL_SD_FOPEN_PARTMGR,
  ESL_SD_MFS_INSTALL_PARTMGR,
  ESL_SD_MFS_INSTALL_SDDEV,
  ESL_SD_FS_OPENFS,
  ESL_SD_FS_CLOSEFS,
  ESL_SD_MFS_UNINSTALL,
  ESL_SD_FCLOSE_PARTMGR,
  ESL_SD_UNINSTALL_PARTMGR,
  ESL_SD_FCLOSE_SDDEV,
  ESL_SD_LWSEM_POLL,
  ESL_SD_LWSEM_WAIT_TICKS,
  ESL_SD_NOT_DETECTABLE,
};

//******************************************************************************
// Module public objects.
//******************************************************************************

/** State information values. */
enum {
  ESL_SD_NOT_INSERTED,
  ESL_SD_INSERTED,
  ESL_SD_ERROR
};

/** Module state information structure. */
typedef struct {
  uint_8              u8State;                                                  //!< If SD card is inserted or not.
  uint_8              u8Updated;                                                //!< If the SD state was updated.
} esl_sd_state;

//******************************************************************************
// Module public functions.
//******************************************************************************

/** SD-card control task. The task periodically checks, if the SD card is
 * plugged in or not. In dependence on the state it installs/uninstalls the
 * file system (MFS).
 * @param [in]  u32InitialData Task initial data. */
void esl_sd_task (uint_32 u32InitialData);

/** Call this interface to obtain the SD card file system handle. That is needed
 * to be able to perform actions on SD FS using the esl_fs module.
 * @return      Handle to the SD-card file system on success, NULL on failure. */
MQX_FILE_PTR esl_sd_getHandle (void);

/** Getter of the module state information.
 * @param [out] poState   Pointer to a state information object, which to store
 *                        the obtained data to.
 * @param [in]  iMaxWait  Maximal wait in msec to wait for the access to the
 *                        module state critical section.
 * @param [out] err       Aditional information about error in case of failure.
 * @return                ESL_SD_OK if success, other ESL_SD_* value in case of
 *                        failure. */
uint_8 esl_sd_getState (esl_sd_state   * poState,
                        _mqx_int         iMaxWait,
                        _mqx_uint      * err);

//******************************************************************************
#endif // ESL_SD_H_46277689278467087609329408 //
