/** ****************************************************************************
 *
 *  @file       esl_sd_config.h
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

#ifndef ESL_SD_CONFIG_H_64564272321021290672102401
#define ESL_SD_CONFIG_H_64564272321021290672102401
//******************************************************************************

#include "esl_config.h"

//******************************************************************************
// Main module settings
//******************************************************************************

/** @def ESL_SD_MODULE_ENABLE
 * @brief Set 1/0 to get module enabled or disabled. */
#ifndef ESL_SD_MODULE_ENABLE
# define ESL_SD_MODULE_ENABLE           (0)
#endif

//******************************************************************************
// Task eslSdcard information
//******************************************************************************

/** @def ESL_SD_TASK_STACK
 * @brief eslSdcard task stack size. */
#ifndef ESL_SD_TASK_STACK
# define ESL_SD_TASK_STACK              (1500)
#endif

/** @def ESL_SD_TASK_STR
 * @brief eslSdcard task name - should be unique! */
#ifndef ESL_SD_TASK_STR
# define ESL_SD_TASK_STR                "eslSdcard"
#endif

//******************************************************************************
// Filesystem settings
//******************************************************************************

/** @def ESL_SD_DEVICE_IDENTIFIER
 * @brief SD card device identifier. Needs to be unique in the IO subsystem. */
#ifndef ESL_SD_DEVICE_IDENTIFIER
# define ESL_SD_DEVICE_IDENTIFIER       "sdcard:"
#endif

/** @def ESL_SD_FILESYSTEM_IDENTIFIER
 * @brief SD card filesystem identifier. Needs to be unique in the IO subsystem. */
#ifndef ESL_SD_FILESYSTEM_IDENTIFIER
# define ESL_SD_FILESYSTEM_IDENTIFIER   "sd:"
#endif

/** @def ESL_SD_PARTMAN_IDENTIFIER
 * @brief SD card partition manager identifier. Needs to be unique
 *        in the IO subsystem. */
#ifndef ESL_SD_PARTMAN_IDENTIFIER
# define ESL_SD_PARTMAN_IDENTIFIER      "apm:"
#endif

/** @def ESL_SD_READONLY
 * @brief Set 1 to configure the file system as read only, 0 to read & write. */
#ifndef ESL_SD_READONLY
# define ESL_SD_READONLY                0
#endif

//******************************************************************************
#endif /* ESL_SDCARD_CONFIG_H_64564272321021290672102401 */
