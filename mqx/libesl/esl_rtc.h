/** ****************************************************************************
 *
 *  @file       esl_rtc.c
 *  @brief      Set of functions for the system time adjustment.
 *
 *  Provides basic functions for getting and setting the RTC time. Besides that
 *  the RTC and MQX time synchronization mechanism is defined withing this
 *  module.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Jan Kubiznak <kubiznak.jan@elnico.cz>
 *
 *  @version    2.3 2014-03-11: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Ported to MQX 4.1, keeping compatibility
 *                              with MQX 4.0 (#117).
 *
 *  @version    2.2 2014-03-08: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              esl_rtc_getTimeStrFmt() implemented (#115).
 *
 *  @version    2.1 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    2.0 2013-11-15: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Module integrated into ESL and more modularized.
 *
 *  @version    1.2 2013-10-21: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Call to _rtc_time_from_mqx_date + _rtc_set_time
 *                              replaced by _rtc_set_time_mqxd. Firstly it is
 *                              _only one call, secondly rtc_time_from_mqx_date
 *                              is not available for Vybrid.
 *
 *  @version    1.1 2012-12-27: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              RTC & MQX time synchronization added.
 *
 *  @version    1.0 2012-12-26: Jan Kubiznak <kubiznak.jan@elnico.cz>
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

#ifndef ESL_RTC_H_54310231530645521257122002
#define ESL_RTC_H_54310231530645521257122002
//******************************************************************************

#include "esl_rtc_config.h"

#include <mqx.h>
#include <bsp.h>

//******************************************************************************

// Module specific log IDs
enum {
  ESL_RTC_OK = MQX_OK,
  ESL_RTC_INVALID_ARGUMENT,
  ESL_RTC_INT_INSTALL_FAILURE,
  ESL_RTC_INT_ENABLE_FAILURE,
  ESL_RTC_INTERNAL_FAILURE,
  ESL_RTC_MODULE_OFF,
};

//******************************************************************************
// Macros and constants

#define ESL_RTC_DATEMASK_DATE           (0x10)                                  //!< Mask to get date as "YYYY-MM-DD".
#define ESL_RTC_DATEMASK_TIME           (0x2F)                                  //!< General mask to get time.
#define ESL_RTC_DATEMASK_TIME_MIN       (0x21)                                  //!< Mask to get time as "HH:MM".
#define ESL_RTC_DATEMASK_TIME_SEC       (0x22)                                  //!< Mask to get time as "HH:MM:SS".
#define ESL_RTC_DATEMASK_TIME_MSEC      (0x23)                                  //!< Mask to get time as "HH:MM:SS.MSC".

#define ESL_RTC_BARE_DATE_MAXSTRLEN     (8 + 1)                                 //!< Length of "YYYYMMDD" + 1 (\0)
#define ESL_RTC_BARE_TIME_MAXSTRLEN     (9 + 1)                                 //!< Length of "HHMMSSmmm" + 1 (\0)
#define ESL_RTC_BARE_DATETIME_MAXSTRLEN ((ESL_RTC_BARE_DATE_MAXSTRLEN) + \
                                         (ESL_RTC_BARE_TIME_MAXSTRLEN) - 1)     //!< Length of "YYYYMMDDHHMMSSmmm" + 1 (\0)

#define ESL_RTC_DATE_MAXSTRLEN          (ESL_RTC_BARE_DATE_MAXSTRLEN + 2)       //!< Length of "YYYY-MM-DD" + 1 (\0)
#define ESL_RTC_TIME_MAXSTRLEN          (ESL_RTC_BARE_TIME_MAXSTRLEN + 3)       //!< Length of "HH:MM:SS.MSC" + 1 (\0)
#define ESL_RTC_SPACE_MAXSTRLEN         (2)                                     //!< Length of the space separator between data and time + 1 (\0)
#define ESL_RTC_DATETIME_MAXSTRLEN      ((ESL_RTC_DATE_MAXSTRLEN) + \
                                         (ESL_RTC_TIME_MAXSTRLEN) + \
                                         (ESL_RTC_SPACE_MAXSTRLEN))             //!< Maximal length of the string "DATE TIME"

#define ESL_RTC_STDFMT_DATE             "%04d-%02d-%02d"                        //!< Timestamp format for ESL_RTC_DATEMASK_DATE.
#define ESL_RTC_STDFMT_TIME_MIN         "%02d:%02d"                             //!< Timestamp format for ESL_RTC_DATEMASK_TIME_MIN.
#define ESL_RTC_STDFMT_TIME_SEC         "%02d:%02d:%02d"                        //!< Timestamp format for ESL_RTC_DATEMASK_TIME_SEC.
#define ESL_RTC_STDFMT_TIME_MSEC        "%02d:%02d:%02d.%03d"                   //!< Timestamp format for ESL_RTC_DATEMASK_TIME_MSEC.

//******************************************************************************

/** Serves for adjusting the system time. This functions first sets the RTC
 *  time and then it synchronizes the MQX time with it.
 * @param [in]  date Structure containing the time to be set.
 * @return      0 on success, non-zero on failure. */
uint_8 esl_rtc_setTime (const DATE_STRUCT_PTR pDate);

/** Serves for obtaining the system time as DATE_STRUCT. The obtained time is
 *  the MQX time.
 * @param [out] pDate Structure containing the current time.
 * @return      0 on success, non-zero on failure. */
uint_8 esl_rtc_getTime (DATE_STRUCT_PTR pDate);

/** Serves for obtaining the system time as string. The obtained time is
 *  the MQX time.
 * @param [out] sDateTime Buffer to store the current time string in. It's strongly
 *  recommended to use the buffer of the minimum size of DATETIME_MAXSTRLEN!
 * @param [in]  u8DateMask Mask to specify which date and time values should be
 *  stored in the output buffer.
 * @return      ESL_RTC_OK on success.
 *              ESL_RTC_INVALID_ARGUMENT is NULL sDateTime or invalid mask given. */
uint_8 esl_rtc_getTimeStr (char *sDateTime, uint_8 u8DateMask);

/** Serves for obtaining a timestamp as a custom-formatted string,
 *  concatenated from date and time formatted strings (with no spacer).
 *  The time is obtained either from an argument or as the MQX time.
 * @param[out]  sDateTime Buffer to store the timestamp in.
 *                        Remember to use large enough buffer, according to
 *                        the format strings. Maximum GENERATED content length
 *                        is ESL_RTC_BARE_DATETIME_MAXSTRLEN.
 * @param[in]   u8BufLen  Buffer length.
 * @param[in]   sDateFmt  Date format, specifying up-to 3 integer fields,
 *                        they will be replaced by YEAR, MONTH and DAY (ordered).
 *                        Use NULL to ignore.
 * @param[in]   sTimeFmt  Time format, specifying up-to 4 integer fields,
 *                        they will be replaced by HOUR, MINUTE, SECOND and
 *                        MILLISECOND (ordered). Use NULL to ignore.
 * @param[in]   poDate    Date structure to generate the timestamp from.
 *                        If NULL, current MQX time is used instead.
 * @return      ESL_RTC_OK on success.
 *              ESL_RTC_INVALID_ARGUMENT if NULL sDateTime given or both format
 *               arguments are NULL. */
uint_8 esl_rtc_getTimeStrFmt (char                * sDateTime,
                              uint_8                u8BufLen,
                              const char          * sDateFmt,
                              const char          * sTimeFmt,
                              const DATE_STRUCT   * poDate);

/** Installs the RTC and MQX time synchronizer.
 * @return      0 on success, non-zero on failure. */
uint_8 esl_rtc_installSynchronizer (void);

//******************************************************************************
#endif // ESL_RTC_H_54310231530645521257122002 //
