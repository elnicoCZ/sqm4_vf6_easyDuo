/** ****************************************************************************
 *
 *  @file       esl_log_fileIDs.h
 *  @brief      File IDs defined here are used by log.
 *
 *  This file contains an enum of file IDs. Each file which wants to log its
 *  File ID, needs to:
 *    #include "esl_log.h"
 *    #undef  ESL_LOG_FILEID        // To undefine the default value
 *    #define ESL_LOG_FILEID  APP_FILEID_EXAMPLE_FILE_C
 *
 *  at the file beginning and also to undefine this macro at the file end:
 *    #undef ESL_LOG_FILEID
 *
 *  The APP_FILEID_EXAMPLE_FILE_C must be defined in the application. The
 *  application shall define its file IDs from (ESL_LOG_FILEID_END + 1).
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Jan Kubiznak <kubiznak.jan@elnico.cz>
 *
 *  @version    1.0 2014-03-16: Jan Kubiznak <kubiznak.jan@elnico.cz>
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

#ifndef ESL_LOG_FILEIDS_H_45642312575232154541321457
#define ESL_LOG_FILEIDS_H_45642312575232154541321457

//******************************************************************************

enum {
  ESL_LOG_FILEID_DEFAULT,
  ESL_LOG_FILEID_START,
  ESL_LOG_FILEID_APPCTRL_C,
  ESL_LOG_FILEID_GPIO_C,
  ESL_LOG_FILEID_LOG_C,
  ESL_LOG_FILEID_MCFS_C,
  ESL_LOG_FILEID_NAND_C,
  ESL_LOG_FILEID_RTC_C,
  ESL_LOG_FILEID_SD_C,
  ESL_LOG_FILEID_USBHMSD_C,
  ESL_LOG_FILEID_CUST_HW_API_C,
  ESL_LOG_FILEID_WIFI_C,
  ESL_LOG_FILEID_WIFI_AP_C,
  ESL_LOG_FILEID_WIFI_CLI_C,
  ESL_LOG_FILEID_WIFI_PRV_C,
  ESL_LOG_FILEID_WIFI_ENET_C,
  ESL_LOG_FILEID_END
};

/** Default FileID, which is used, if a file uses log but doesn't define any
 * FileID. */
#define ESL_LOG_FILEID            ESL_LOG_FILEID_DEFAULT

//******************************************************************************
#endif //ESL_LOG_FILEIDS_H_45642312575232154541321457
