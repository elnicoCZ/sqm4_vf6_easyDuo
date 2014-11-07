/** ****************************************************************************
 *
 *  @file       esl_log.h
 *  @brief      Application log task and API
 *
 *  Independent module to be included by an application to get the option for
 *  messages' logging.
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
 *                              Module integrated into ESL and more modularized.
 *
 *  @version    1.5 2013-10-21: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Automatic filesystem usage replaced by initFs()
 *                              function - prepares log for logging to a file.
 *
 *  @version    1.4 2013-03-24: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Logging into a file on SD card added.
 *
 *  @version    1.3 2012-12-27: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Variable formatting added for LOG?_FORMATTED.
 *                              Log stores also timestamp and severity.
 *
 *  @version    1.2 2012-12-21: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              The 2012-02-16 version rebuilt for ns150.
 *
 *  @version    1.1 2012-02-16: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Basic functionality integrated.
 *
 *  @version    1.0 2011-01-18: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Initial revision.
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

#ifndef ESL_LOG_H_23327150631432000240121162
#define ESL_LOG_H_23327150631432000240121162
//******************************************************************************

#include "esl_log_config.h"
#include "esl_log_fileIDs.h"

//******************************************************************************
// Module internal macros indicating if errors/warnings/... shall be logged.
//******************************************************************************

/** @def ESL_LOG_ERRORS
 * @brief This macro is equal to 1 if errors shall be logged or to 0 if not. */
#define ESL_LOG_ERRORS   (((ESL_LOG_STDIO_ENABLE)  & (ESL_LOG_STDIO_ERRORS))  | \
                          ((ESL_LOG_FS_ENABLE)     & (ESL_LOG_FS_ERRORS))     | \
                          ((ESL_LOG_EEPROM_ENABLE) & (ESL_LOG_EEPROM_ERRORS)))

/** @def ESL_LOG_WARNINGS
 * @brief This macro is equal to 1 if warnings shall be logged or to 0 if not. */
#define ESL_LOG_WARNINGS (((ESL_LOG_STDIO_ENABLE)  & (ESL_LOG_STDIO_WARNINGS))  | \
                          ((ESL_LOG_FS_ENABLE)     & (ESL_LOG_FS_WARNINGS))     | \
                          ((ESL_LOG_EEPROM_ENABLE) & (ESL_LOG_EEPROM_WARNINGS)))

/** @def ESL_LOG_INFOS
 * @brief This macro is equal to 1 if infos shall be logged or to 0 if not. */
#define ESL_LOG_INFOS    (((ESL_LOG_STDIO_ENABLE)  & (ESL_LOG_STDIO_INFOS))  | \
                          ((ESL_LOG_FS_ENABLE)     & (ESL_LOG_FS_INFOS))     | \
                          ((ESL_LOG_EEPROM_ENABLE) & (ESL_LOG_EEPROM_INFOS)))

/** @def ESL_LOG_DEBUG
 * @brief This macro is equal to 1 if debug messages shall be logged or to 0 if
 * not. */
#define ESL_LOG_DEBUG    (((ESL_LOG_STDIO_ENABLE)  & (ESL_LOG_STDIO_DEBUG))  | \
                          ((ESL_LOG_FS_ENABLE)     & (ESL_LOG_FS_DEBUG))     | \
                          ((ESL_LOG_EEPROM_ENABLE) & (ESL_LOG_EEPROM_DEBUG)))

//******************************************************************************
// Message types
//******************************************************************************

#define ESL_LOG_MSG_SEV_ERR_SHIFT         (0)                                   //!< Shift for error messages.
#define ESL_LOG_MSG_SEV_WARN_SHIFT        (1)                                   //!< Shift for warning messages.
#define ESL_LOG_MSG_SEV_INFO_SHIFT        (2)                                   //!< Shift for info messages.
#define ESL_LOG_MSG_SEV_DBG_SHIFT         (3)                                   //!< Shift for debug messages.
#define ESL_LOG_MSG_CMD_FS_INIT_SHIFT     (4)                                   //!< Shift for cmd fs init messages.
#define ESL_LOG_MSG_CMD_EEPROM_INIT_SHIFT (5)                                   //!< Shift for cmd EEPROM init messages.

#define ESL_LOG_MSG_SEV_ERR            (1 << ESL_LOG_MSG_SEV_ERR_SHIFT)         //!< Highest severity: error messages
#define ESL_LOG_MSG_SEV_WARN           (1 << ESL_LOG_MSG_SEV_WARN_SHIFT)        //!< Middle severity: warning messages
#define ESL_LOG_MSG_SEV_INFO           (1 << ESL_LOG_MSG_SEV_INFO_SHIFT)        //!< Low severity: info messages
#define ESL_LOG_MSG_SEV_DBG            (1 << ESL_LOG_MSG_SEV_DBG_SHIFT)         //!< Lowest severity: debug messages (these will not be stored into the log file)
#define ESL_LOG_MSG_CMD_FS_INIT        (1 << ESL_LOG_MSG_CMD_FS_INIT_SHIFT)     //!< Command to initialize logging to a filesystem
#define ESL_LOG_MSG_CMD_EEPROM_INIT    (1 << ESL_LOG_MSG_CMD_EEPROM_INIT_SHIFT) //!< Command to initialize logging to EEPROM

#define ESL_LOG_MSG_SEV_ERR_CHAR       ('E')                                    //!< Char to be logged for error messages.
#define ESL_LOG_MSG_SEV_WARN_CHAR      ('W')                                    //!< Char to be logged for warning messages.
#define ESL_LOG_MSG_SEV_INFO_CHAR      ('I')                                    //!< Char to be logged for info messages.
#define ESL_LOG_MSG_SEV_DBG_CHAR       ('D')                                    //!< Char to be logged for debug messages.
#define ESL_LOG_MSG_SEV_UNKNOWN_CHAR   ('?')                                    //!< Char to be logged if the severity is not recognized.

//******************************************************************************
// Macros LOGE_STR, LOGW_FORMATTED, etc. to be used by other modules
//******************************************************************************

#if ESL_LOG_ERRORS

# define LOGE_STR(str)           esl_log_sendStr(ESL_LOG_FILEID,             \
                                                 __LINE__,                   \
                                                 ESL_LOG_MSG_SEV_ERR,        \
                                                 str)

# define LOGE_FORMATTED(fmt,...) esl_log_sendFormatted(ESL_LOG_FILEID,       \
                                                       __LINE__,             \
                                                       ESL_LOG_MSG_SEV_ERR,  \
                                                       fmt, ##__VA_ARGS__)

#else

# define LOGE_STR(str)
# define LOGE_FORMATTED(fmt,...)

#endif

//*************************************

#if ESL_LOG_WARNINGS

# define LOGW_STR(str)           esl_log_sendStr(ESL_LOG_FILEID,             \
                                                 __LINE__,                   \
                                                 ESL_LOG_MSG_SEV_WARN,       \
                                                 str)

# define LOGW_FORMATTED(fmt,...) esl_log_sendFormatted(ESL_LOG_FILEID,       \
                                                       __LINE__,             \
                                                       ESL_LOG_MSG_SEV_WARN, \
                                                       fmt, ##__VA_ARGS__)

#else

# define LOGW_STR(str)
# define LOGW_FORMATTED(fmt,...)

#endif

//*************************************

#if ESL_LOG_INFOS

# define LOGI_STR(str)           esl_log_sendStr(ESL_LOG_FILEID,             \
                                                 __LINE__,                   \
                                                 ESL_LOG_MSG_SEV_INFO,       \
                                                 str)

# define LOGI_FORMATTED(fmt,...) esl_log_sendFormatted(ESL_LOG_FILEID,       \
                                                       __LINE__,             \
                                                       ESL_LOG_MSG_SEV_INFO, \
                                                       fmt, ##__VA_ARGS__)

#else

# define LOGI_STR(str)
# define LOGI_FORMATTED(fmt,...)

#endif

//*************************************

#if ESL_LOG_DEBUG

# define LOGD_STR(str)           esl_log_sendStr(ESL_LOG_FILEID,             \
                                                 __LINE__,                   \
                                                 ESL_LOG_MSG_SEV_DBG,       \
                                                 str)

# define LOGD_FORMATTED(fmt,...) esl_log_sendFormatted(ESL_LOG_FILEID,       \
                                                       __LINE__,             \
                                                       ESL_LOG_MSG_SEV_DBG, \
                                                       fmt, ##__VA_ARGS__)

#else

# define LOGD_STR(str)
# define LOGD_FORMATTED(fmt,...)

#endif

//******************************************************************************
// EEPROM log constants
//******************************************************************************

#define ESL_LOG_EEPROM_DEVNAME_LEN          (10)                                //!< Maximal allowed length of the SPI device name.
#define ESL_LOG_EEPROM_MSG_TERMINATOR       (0x00)                              //!< Flag written after every EEPROM log message.
#define ESL_LOG_EEPROM_MSG_CNT              ((ESL_LOG_EEPROM_SIZE-sizeof(esl_log_TEepromHead))/sizeof(esl_log_TEepromMsg))    //!< The size of the log message pool.
#define ESL_LOG_EEPROM_HEAD_INITIALIZED     (0x2F9E1CA3)                        //!< Mark of the initialized EEPROM log.


//******************************************************************************
// Return values
//******************************************************************************
enum {
  ESL_LOG_OK = MQX_OK,
  ESL_LOG_STORAGE_NOT_ENABLED,
  ESL_LOG_LWMSGQ_INIT_FAILURE,
  ESL_LOG_LWMSGQ_SEND_FAILURE,
  ESL_LOG_MODULE_OFF,
};

//******************************************************************************
// Typedefs
//******************************************************************************

/** Message to log to EEPROM. It uses the padding to not to align
 * the members in the 32-bit way. That is important to spare memory in the
 * actual location - EEPROM. */
#if (defined(__IAR_SYSTEMS_ICC__))
# pragma pack (1)
#elif (defined(GCC))
# pragma pack (1)
#else
# if (ESL_LOG_EEPROM_ENABLE)
#  warning "Please use a pack(1) equivalent, which is supported by your compiler."
# endif
#endif

/** EEPROM Configuration part Head */
typedef struct {
  uint_32        u32InitFlag;
  uint_16        u16StartIdx;
} esl_log_TEepromHead;

typedef struct {
#if (ESL_LOG_OUTPUT_SEVERITY)
  uint_8         u8Sev;
#endif
#if ((ESL_LOG_OUTPUT_TIMESTAMP) && (ESL_LOG_TIMESTAMP_EEPROM_SEC))
  uint_32        u32Sec;
#endif
#if ((ESL_LOG_OUTPUT_TIMESTAMP) && (ESL_LOG_TIMESTAMP_EEPROM_MSEC))
  uint_16        u16Msec;
#endif
#if (ESL_LOG_OUTPUT_TASKID)
  _task_id       xTaskId;
#endif
#if (ESL_LOG_OUTPUT_FILEID)
  uint_16        u16FileId;
#endif
#if (ESL_LOG_OUTPUT_LINE)
  uint_16        u16Line;
#endif
#if (ESL_LOG_OUTPUT_DATA)
  uint_32        au32Data[ESL_LOG_EEPROM_DATALEN];
#endif
} esl_log_TEepromMsg;

#if (defined(__IAR_SYSTEMS_ICC__))
# pragma pack ()
#elif (defined(GCC))
# pragma pack ()
#else
# if (ESL_LOG_EEPROM_ENABLE)
#  warning "Please use a pack() equivalent, which is supported by your compiler."
# endif
#endif

/** All EEPROM related information. */
typedef struct {
  esl_log_TEepromHead    m_oHead;
  esl_log_TEepromMsg     m_oMsg[ESL_LOG_EEPROM_MSG_CNT];
} esl_log_TEepromLog;

//******************************************************************************
// appLog related public functions. Important: Do not use them directly. Use
// the LOGE_STR, LOGW_FORMATTED, etc. macros instead!

/** Application log task.
 * @param initialData Task initial data. */
void esl_log_task (uint_32 initialData);

/** Initializes log structures to enable logging into a file on a filesystem.
 * @return  ESL_LOG_OK if command has successfully been sent to the task
 *           (the result of initialization itself cannot be retrieved).
 *          ESL_LOG_LWMSGQ_SEND_FAILURE if command fails to be written
 *           to the task message queue. */
int esl_log_initFs (void);

/** Initializes log structures to enable logging into EEPROM. This function is
 * not REENTRANT! Therefore a special care must be taken to NEVER call it from
 * more tasks in parallel.
 * @param [in] u8SpiChannel     Index of the SPI channel, on which the SPI
 *                              EEPROM memory is connected. See esl_spi module.
 * @param [in] psSpimemDevName  Device name of the SPI EEPROM memory. Depends on
 *                              the used SPI channel and chip select.
 *                              Examples: "spi0:1", "spi1:2", ...
 * @return                      ESL_LOG_OK if command has successfully been sent
 *                              to the task (the result of initialization itself
 *                              cannot be retrieved).
 *                              ESL_LOG_LWMSGQ_SEND_FAILURE if command fails to
 *                              be written to the task message queue. */
int esl_log_initEeprom (uint_8 u8SpiChannel, const char * psSpimemDevName);

/** For STDIO/FS log: Sends a formatted string message.
 * For EEPROM: If the EEPROM storage is used, then the first two parameters of
 *             the variable argument list are casted to uint_32 and written
 *             to EEPROM. All other parameters in the variable argument list
 *             are not used.
 * @param [in] u16FileId  ID of a file in which the message was fired.
 * @param [in] u16Line    Line number at which the message was fired.
 * @param [in] u8Sev      Log message severity.
 * @param [in] psStr      String to log. Maximum of ESL_LOG_MSG_STRLEN-1
 *                        characters can be logged - if the string is longer,
 *                        the rest is truncated. */
void esl_log_sendStr (uint_16        u16FileId,
                      uint_16        u16Line,
                      uint_8         u8Sev,
                      const char   * psStr);

/** Use to send specific formated string message containing one '%d' sequence
 * for printing a decimal number.
 * @param [in] u16FileId  ID of a file in which the message was fired.
 * @param [in] u16Line    Line number at which the message was fired.
 * @param [in] u8Sev      Log message severity.
 * @param [in] psFmtStr   Format string to log. Maximum of ESL_LOG_MSG_STRLEN-1
 *                        characters can be logged - if the string is longer,
 *                        the rest is truncated.
 * @param [in] ...        List of variables to be formatted within the format
 *                        string. */
void esl_log_sendFormatted (uint_16        u16FileId,
                            uint_16        u16Line,
                            uint_8         u8Sev,
                            const char   * psFmtStr,
                                           ...);

//******************************************************************************
#endif /* ESL_LOG_H_23327150631432000240121162 */
