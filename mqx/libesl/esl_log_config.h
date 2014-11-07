/** ****************************************************************************
 *
 *  @file       esl_log_config.h
 *  @brief      Application log module config file
 *
 *  Default configuration of the log module. The settings should not be changed
 *  here but can be overridden in a project specific esl_config.h.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    2.2 2014-03-16: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Configurability which messages to log to
 *                              STDIO/FS.
 *
 *  @version    2.1 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    2.0 2013-11-15: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Initial revision for esl_log v2.0.
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

#ifndef ESL_LOG_CONFIG_H_09483609345407682959483054
#define ESL_LOG_CONFIG_H_09483609345407682959483054
//******************************************************************************

#include "esl_config.h"
#include "esl_utils.h"
#include "esl_sd.h"
#include "esl_fs.h"

//******************************************************************************
// Main module settings
//******************************************************************************

/** @def ESL_LOG_MODULE_ENABLE
 * @brief Set 1/0 to get module enabled or disabled. */
#ifndef ESL_LOG_MODULE_ENABLE
# define ESL_LOG_MODULE_ENABLE          (0)
#endif

//******************************************************************************
// STDIO Log configuration
//******************************************************************************

/** @def ESL_LOG_STDIO_ENABLE
 * @brief Set 1/0 to enable or disable the STDIO log. */
#ifndef ESL_LOG_STDIO_ENABLE
# define ESL_LOG_STDIO_ENABLE           (1)
#endif

/** @def ESL_LOG_STDIO_ERRORS
 * @brief Set 1/0 to enable or disable logging errors into the STDIO log. */
#ifndef ESL_LOG_STDIO_ERRORS
# define ESL_LOG_STDIO_ERRORS           (1)
#endif

/** @def ESL_LOG_STDIO_WARNINGS
 * @brief Set 1/0 to enable or disable logging warnings into the STDIO log. */
#ifndef ESL_LOG_STDIO_WARNINGS
# define ESL_LOG_STDIO_WARNINGS         (1)
#endif

/** @def ESL_LOG_STDIO_INFOS
 * @brief Set 1/0 to enable or disable logging infos into the STDIO log. */
#ifndef ESL_LOG_STDIO_INFOS
# define ESL_LOG_STDIO_INFOS            (1)
#endif

/** @def ESL_LOG_STDIO_DEBUG
 * @brief Set 1/0 to enable or disable logging debug messagss into the STDIO
 * log. */
#ifndef ESL_LOG_STDIO_DEBUG
# define ESL_LOG_STDIO_DEBUG            (1)
#endif

//******************************************************************************
// FS Log configuration
//******************************************************************************

/** @def ESL_LOG_FS_ENABLE
 * @brief Set 1/0 to enable or disable the FS log. */
#ifndef ESL_LOG_FS_ENABLE
# define ESL_LOG_FS_ENABLE              (0)
#endif

/** @def ESL_LOG_FS_ERRORS
 * @brief Set 1/0 to enable or disable logging errors into the FS log. */
#ifndef ESL_LOG_FS_ERRORS
# define ESL_LOG_FS_ERRORS              (1)
#endif

/** @def ESL_LOG_FS_WARNINGS
 * @brief Set 1/0 to enable or disable logging warnings into the FS log. */
#ifndef ESL_LOG_FS_WARNINGS
# define ESL_LOG_FS_WARNINGS            (1)
#endif

/** @def ESL_LOG_FS_INFOS
 * @brief Set 1/0 to enable or disable logging infos into the FS log. */
#ifndef ESL_LOG_FS_INFOS
# define ESL_LOG_FS_INFOS               (1)
#endif

/** @def ESL_LOG_FS_DEBUG
 * @brief Set 1/0 to enable or disable logging debug messagss into the FS
 * log. */
#ifndef ESL_LOG_FS_DEBUG
# define ESL_LOG_FS_DEBUG               (0)
#endif

//******************************************************************************
// EEPROM Log configuration
//******************************************************************************

/** @def ESL_LOG_EEPROM_ENABLE
 * @brief Set 1/0 to enable or disable the EEPROM log. */
#ifndef ESL_LOG_EEPROM_ENABLE
# define ESL_LOG_EEPROM_ENABLE          (0)
#endif

/** @def ESL_LOG_EEPROM_ERRORS
 * @brief Set 1/0 to enable or disable logging errors into the EEPROM log. */
#ifndef ESL_LOG_EEPROM_ERRORS
# define ESL_LOG_EEPROM_ERRORS          (1)
#endif

/** @def ESL_LOG_EEPROM_WARNINGS
 * @brief Set 1/0 to enable or disable logging warnings into the EEPROM log. */
#ifndef ESL_LOG_EEPROM_WARNINGS
# define ESL_LOG_EEPROM_WARNINGS        (1)
#endif

/** @def ESL_LOG_EEPROM_INFOS
 * @brief Set 1/0 to enable or disable logging infos into the EEPROM log. */
#ifndef ESL_LOG_EEPROM_INFOS
# define ESL_LOG_EEPROM_INFOS           (0)
#endif

/** @def ESL_LOG_EEPROM_DEBUG
 * @brief Set 1/0 to enable or disable logging debug messagss into the EEPROM
 * log. */
#ifndef ESL_LOG_EEPROM_DEBUG
# define ESL_LOG_EEPROM_DEBUG           (0)
#endif

//******************************************************************************
// Task eslLog information
//******************************************************************************

/** @def ESL_LOG_TASK_STACK
 * @brief eslLog task stack size. */
#ifndef ESL_LOG_TASK_STACK
# define ESL_LOG_TASK_STACK             (2500)
#endif

/** @def ESL_LOG_TASK_STR
 * @brief eslLog task name - should be unique! */
#ifndef ESL_LOG_TASK_STR
# define ESL_LOG_TASK_STR               "eslLog"
#endif

//******************************************************************************
// Message queue settings
//******************************************************************************

/** @def ESL_LOG_MSG_STRLEN
 * @brief Maximal length of a message in chars. */
#ifndef ESL_LOG_MSG_STRLEN
# define ESL_LOG_MSG_STRLEN             (70)
#endif

/** @def ESL_LOG_EEPROM_DATALEN
 * @brief Length of the uint_32 array to be logged to EEPROM. */
#ifndef ESL_LOG_EEPROM_DATALEN
# define ESL_LOG_EEPROM_DATALEN         (2)
#endif

/** @def ESL_LOG_MSGQ_ID
 * @brief Application log gatekeeper queue ID. Needs to be unique! */
#ifndef ESL_LOG_MSGQ_ID
# define ESL_LOG_MSGQ_ID                (2)
#endif

/** @def ESL_LOG_MSGQ_SIZE
 * @brief Application log gatekeeper queue size (set 0 to unlimited). */
#ifndef ESL_LOG_MSGQ_SIZE
# define ESL_LOG_MSGQ_SIZE              (4)
#endif

/** @def ESL_LOG_MSGQ_MAXWAIT
 * @brief Application log gatekeeper queue's time to wait at message read
 *        (set 0 to unlimited wait). */
#ifndef ESL_LOG_MSGQ_MAXWAIT
# define ESL_LOG_MSGQ_MAXWAIT           (0)
#endif

/** @def ESL_LOG_MSGQ_MAXWAITTOFLUSH
 * @brief Application log gatekeeper queue's time to wait at message read before
 *        fflush for all previously written messages. The value is in ticks. */
#ifndef ESL_LOG_MSGQ_MAXWAITTOFLUSH
# define ESL_LOG_MSGQ_MAXWAITTOFLUSH    (MSECS_TO_MQX_TICKS(50))
#endif

//******************************************************************************
// Filesystem settings
//******************************************************************************

/** @def ESL_LOG_CFG_FILENAME
 * @brief Configuration file containing the log files count.
 * @see ESL_LOG_CFG_KEY_COUNTER */
#ifndef ESL_LOG_CFG_FILENAME
# define ESL_LOG_CFG_FILENAME           ESL_SD_FILESYSTEM_IDENTIFIER \
                                          "\\system\\log.cfg"
#endif

/** @def ESL_LOG_CFG_KEY_COUNTER
 * @brief Configuration file key: Counter of existing log files. */
#ifndef ESL_LOG_CFG_KEY_COUNTER
# define ESL_LOG_CFG_KEY_COUNTER        "LOG_COUNTER"
#endif

/** @def ESL_LOG_CFG_MEMPOOLID
 * @brief Memory pool ID to be used for config file memory allocations.
 *        Use NULL for the default pool. */
#ifndef ESL_LOG_CFG_MEMPOOLID
# define ESL_LOG_CFG_MEMPOOLID          NULL
#endif

/** @def ESL_LOG_FILE_FILENAME
 * @brief Output file name. The first wildcard will be replaced by the current
 *        counter value (@see ESL_LOG_CFG_KEY_COUNTER), the second wildcard
 *        will be replaced by a timestamp.
 * @see ESL_LOG_FILE_TIMESTAMP, ESL_LOG_FILE_FILENAMELEN */
#ifndef ESL_LOG_FILE_FILENAME
# define ESL_LOG_FILE_FILENAME          ESL_SD_FILESYSTEM_IDENTIFIER \
                                          "\\log\\%08X_%s.log"
#endif

/** @def ESL_LOG_FILE_TIMESTAMP
 * @brief Log file timestamp, used for a filename of the log file.
 * @see ESL_LOG_FILE_FILENAME, ESL_LOG_FILE_FILENAMELEN. */
#ifndef ESL_LOG_FILE_TIMESTAMP
# define ESL_LOG_FILE_TIMESTAMP         (ESL_RTC_DATEMASK_DATE)
#endif

/** @def ESL_LOG_FILE_FILENAMELEN
 * @brief Length of a log filename.
 * @see ESL_LOG_FILE_FILENAME, ESL_LOG_FILE_TIMESTAMP. */
#ifndef ESL_LOG_FILE_FILENAMELEN
# define ESL_LOG_FILE_FILENAMELEN       ((ESL_FS_MAXDEVNAMELEN) + (19) + \
                                          (ESL_RTC_DATE_MAXSTRLEN))
#endif


//******************************************************************************
// Output formatting
//******************************************************************************

/** @def ESL_LOG_OUTPUT_SEVERITY
 * @brief Set 1/0 to enable/disable outputting the message severity character.
 * Supported storages: FS/STDIO/EEPROM. */
#ifndef ESL_LOG_OUTPUT_SEVERITY
# if (ESL_LOG_EEPROM_ENABLE)
#  define ESL_LOG_OUTPUT_SEVERITY        (1)
# elif (ESL_LOG_FS_ENABLE)
#  define ESL_LOG_OUTPUT_SEVERITY        (1)
# elif (ESL_LOG_STDIO_ENABLE)
#  define ESL_LOG_OUTPUT_SEVERITY        (1)
# endif
#endif

/** @def ESL_LOG_OUTPUT_TIMESTAMP
 * @brief Set 1/0 to enable/disable outputting the message timestamp.
 * Supported storages: FS/STDIO/EEPROM.
 * @see ESL_LOG_TIMESTAMP_FORMAT for the timestamp format in FS/STDIO.
 * @see ESL_LOG_TIMESTAMP_EEPROM_SEC and ESL_LOG_TIMESTAMP_EEPROM_MSEC for the
 * timestamp format in EEPROM. */
#ifndef ESL_LOG_OUTPUT_TIMESTAMP
# if (ESL_LOG_EEPROM_ENABLE)
#  define ESL_LOG_OUTPUT_TIMESTAMP      (1)
# elif (ESL_LOG_FS_ENABLE)
#  define ESL_LOG_OUTPUT_TIMESTAMP      (1)
# elif (ESL_LOG_STDIO_ENABLE)
#  define ESL_LOG_OUTPUT_TIMESTAMP      (1)
# endif
#endif

/** @def ESL_LOG_OUTPUT_TASKID
 * @brief Set 1/0 to enable/disable outputting the caller task ID.
 * Supported storages: FS/STDIO/EEPROM. */
#ifndef ESL_LOG_OUTPUT_TASKID
# if (ESL_LOG_EEPROM_ENABLE)
#  define ESL_LOG_OUTPUT_TASKID         (0)
# elif (ESL_LOG_FS_ENABLE)
#  define ESL_LOG_OUTPUT_TASKID         (0)
# elif (ESL_LOG_STDIO_ENABLE)
#  define ESL_LOG_OUTPUT_TASKID         (0)
# endif
#endif

/** @def ESL_LOG_OUTPUT_FILEID
 * @brief Set 1/0 to enable/disable outputting the file ID.
 * Supported storages: FS/STDIO/EEPROM. */
#ifndef ESL_LOG_OUTPUT_FILEID
# if (ESL_LOG_EEPROM_ENABLE)
#  define ESL_LOG_OUTPUT_FILEID         (1)
# elif (ESL_LOG_FS_ENABLE)
#  define ESL_LOG_OUTPUT_FILEID         (0)
# elif (ESL_LOG_STDIO_ENABLE)
#  define ESL_LOG_OUTPUT_FILEID         (0)
# endif
#endif

/** @def ESL_LOG_OUTPUT_LINE
 * @brief Set 1/0 to enable/disable outputting the line.
 * Supported storages: FS/STDIO/EEPROM. */
#ifndef ESL_LOG_OUTPUT_LINE
# if (ESL_LOG_EEPROM_ENABLE)
#  define ESL_LOG_OUTPUT_LINE           (1)
# elif (ESL_LOG_FS_ENABLE)
#  define ESL_LOG_OUTPUT_LINE           (0)
# elif (ESL_LOG_STDIO_ENABLE)
#  define ESL_LOG_OUTPUT_LINE           (0)
# endif
#endif

/** @def ESL_LOG_OUTPUT_DATA
 * @brief Set 1/0 to enable/disable outputting the data.
 * Supported storages: EEPROM. */
#ifndef ESL_LOG_OUTPUT_DATA
# if (ESL_LOG_EEPROM_ENABLE)
#  define ESL_LOG_OUTPUT_DATA           (1)
# endif
#endif

/** @def ESL_LOG_OUTPUT_TEXT
 * @brief Set 1/0 to enable/disable outputting the message text.
 * Supported storages: FS/STDIO. */
#ifndef ESL_LOG_OUTPUT_TEXT
# if ((ESL_LOG_STDIO_ENABLE) || (ESL_LOG_FS_ENABLE))
#  define ESL_LOG_OUTPUT_TEXT           (1)
# endif
#endif

/** @def ESL_LOG_TIMESTAMP_DATEFORMAT
 * @brief Date format to be used in log messages for STDIO/FS. Use 0 if
 * e.g. just time shall be logged.
 * Supported storages: FS/STDIO.
 * @see ESL_LOG_OUTPUT_TIMESTAMP to enable/disable timestamp output. */
#ifndef ESL_LOG_TIMESTAMP_DATEFORMAT
# if ((ESL_LOG_STDIO_ENABLE) || (ESL_LOG_FS_ENABLE))
#  define ESL_LOG_TIMESTAMP_DATEFORMAT   ( ESL_RTC_STDFMT_DATE " " )
# endif
#endif

/** @def ESL_LOG_TIMESTAMP_TIMEFORMAT
 * @brief Date format to be used in log messages for STDIO/FS. Use 0 if
 * e.g. just time shall be logged.
 * Supported storages: FS/STDIO.
 * @see ESL_LOG_OUTPUT_TIMESTAMP to enable/disable timestamp output. */
#ifndef ESL_LOG_TIMESTAMP_TIMEFORMAT
# if ((ESL_LOG_STDIO_ENABLE) || (ESL_LOG_FS_ENABLE))
#  define ESL_LOG_TIMESTAMP_TIMEFORMAT   ( ESL_RTC_STDFMT_TIME_MSEC )
# endif
#endif

/** @def ESL_LOG_TIMESTAMP_EEPROM_SEC
 * @brief If to use seconds as a part of the timestamp of EEPROM log messages.
 * Supported storages: EEPROM.
 * @see ESL_LOG_OUTPUT_TIMESTAMP to enable/disable timestamp output. */
#ifndef ESL_LOG_TIMESTAMP_EEPROM_SEC
# if (ESL_LOG_EEPROM_ENABLE)
#  define ESL_LOG_TIMESTAMP_EEPROM_SEC  (1)
# endif
#endif

/** @def ESL_LOG_TIMESTAMP_EEPROM_MSEC
 * @brief If to use milliseconds as a part of the timestamp of EEPROM log
 * messages.
 * Supported storages: EEPROM.
 * @see ESL_LOG_OUTPUT_TIMESTAMP to enable/disable timestamp output. */
#ifndef ESL_LOG_TIMESTAMP_EEPROM_MSEC
# if (ESL_LOG_EEPROM_ENABLE)
#  define ESL_LOG_TIMESTAMP_EEPROM_MSEC (0)
# endif
#endif

//******************************************************************************
// EEPROM Log Settings
//******************************************************************************

/** @def ESL_LOG_EEPROM_ADDR_START
 * @brief Start address of the EEPROM log storage. Implicitly the full 25aa256
 * EEPROM memory is used. */
#ifndef ESL_LOG_EEPROM_ADDR_START
# define ESL_LOG_EEPROM_ADDR_START      (0x0000)
#endif

/** @def ESL_LOG_EEPROM_ADDR_END
 * @brief Size of the EEPROM log partition in Bytes. If any byte shall be
 * to an address bigger than ESL_LOG_EEPROM_ADDR_START + ESL_LOG_EEPROM_SIZE,
 * then it's written to the ESL_LOG_EEPROM_ADDR_START address. */
#ifndef ESL_LOG_EEPROM_SIZE
# define ESL_LOG_EEPROM_SIZE            (32768)
#endif

//******************************************************************************
#endif /* ESL_LOG_CONFIG_H_09483609345407682959483054 */
