/** ****************************************************************************
 *
 *  @file       esl_cfg.h
 *  @brief      Configuration files access module
 *
 *  This module provides simple access to special configuration files in the
 *  simplest possible form as in the example:
 *
 *  #esl_cfg config file
 *  TS_Calibrated=0000000001
 *  TS_Xoffset=0000000458
 *  TS_Yoffset=0000000351
 *  TS_XBitsPerPixelx16=0000000000
 *  TS_YBitsPerPixelx16=0000000000
 *
 *  Lines starting with sharp (#) are considered to be comments and are ignored.
 *  Otherwise "key=value" syntax of each line is expected, avoiding any
 *  whitespaces. Only integer and string values are currently supported.
 *
 *  First step is to open a ESL_CFG file by calling esl_cfg_open().
 *  That initializes ESL_CFG_FILE structure, reads and parses specified file
 *  if it exists. Values stored in the config can then be retrieved by calls
 *  to esl_cfg_getString() and esl_cfg_getInteger(). Similarly new values
 *  can be stored (or old values modified) by calls to esl_cfg_setString() and
 *  esl_cfg_setInteger(). All these actions only modify the dynamic structure
 *  represented by the pointer to ESL_CFG_FILE. To actually write the data
 *  to the file on a filesystem, esl_cfg_close() has to be called. After that,
 *  the structure is freed and should not be used any more.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    3.1 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    3.0 2013-11-21: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Module integrated into ESL and renamed
 *                              from lwcfg to esl_cfg.
 *
 *  @version    2.0 2013-03-25: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              No D4D library prerequisity - both structure
 *                              and interface changed.
 *
 *  @version    1.0 2012-08-24: Petr Kubiznak <kubiznak.petr@elnico.cz>
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

#ifndef ESL_CFG_H_21736430403755468641630015
#define ESL_CFG_H_21736430403755468641630015

/*******************************************************************************
*       Includes header files
*******************************************************************************/
#include "esl_cfg_config.h"

#include <mqx.h>

/*******************************************************************************
*       Types
*******************************************************************************/
typedef struct esl_cfg_record {
  char                  * key;
  char                  * value;
  struct esl_cfg_record * next;
} ESL_CFG_RECORD, * ESL_CFG_RECORD_PTR;

typedef struct esl_cfg_file {
  char                * fileName;
  ESL_CFG_RECORD_PTR    firstRecord;
  uint_8                bChanged;
  _mem_pool_id          pPoolId;
} ESL_CFG_FILE, *ESL_CFG_FILE_PTR;

//******************************************************************************
// Return values
//******************************************************************************
enum {
  ESL_CFG_OK = MQX_OK,
  ESL_CFG_OPEN_FAILURE,
  ESL_CFG_READ_FAILURE,
  ESL_CFG_WRITE_FAILURE,
  ESL_CFG_FFLUSH_FAILURE,
  ESL_CFG_STRINGIFY_FAILURE,
  ESL_CFG_RECORD_NOT_FOUND,
  ESL_CFG_MEMORY_FAILURE,
  ESL_CFG_INVALID_ARGUMENT,
  ESL_CFG_MODULE_OFF,
};
/*******************************************************************************
*       Functions declarations
*******************************************************************************/

/*******************************************************************************
* Opens a config file and initializes the config file structure. This needs
* to be called before any other function from this library.
* @param[in]  sFileName   Path to the config file in the filesystem.
* @param[in]  pPoolId     Memory pool ID (actually a pointer). That specifies
*                         what memory pool can be used to allocate memory
*                         for the structure being returned. Use NULL if using
*                         default memory pool.
* @return                 Config file structure on success, NULL on fail.
*******************************************************************************/
ESL_CFG_FILE_PTR esl_cfg_open(char            * sFileName,
                              _mem_pool_id      pPoolId);

/*******************************************************************************
* Closes a config file and destroys the config file structure.
* @param[in,out]  pCfgFile  Config file structure to destroy.
* @return                   ESL_CFG_OK on success.
*                           ESL_CFG_INVALID_ARGUMENT if NULL argument given.
*                           ESL_CFG_STRINGIFY_FAILURE on stringification failure.
*                           ESL_CFG_OPEN_FAILURE on file open failure.
*                           ESL_CFG_WRITE_FAILURE on file write failure.
*******************************************************************************/
uint_8 esl_cfg_close(ESL_CFG_FILE_PTR pCfgFile);

/*******************************************************************************
* Reads the string value given by the key.
* @param[in]  pCfgFile  Initialized config file structure.
* @param[in]  key       Key to locate its value in the config records.
* @param[out] value     Address to store the string value to. The memory space
*                       has to be allocated before the call.
* @param[in]  maxLen    Maximal length of data to copy.
* @return               ESL_CFG_OK if the key is found. Its value is stored
*                        to the address specified by the parameter "value".
*                       ESL_CFG_INVALID_ARGUMENT if NULL argument given.
*                       ESL_CFG_RECORD_NOT_FOUND if given key is not found
*                        in the config file. "value" stays unchanged in this case.
*******************************************************************************/
uint_8 esl_cfg_getString(ESL_CFG_FILE_PTR   pCfgFile,
                         char             * key,
                         char             * value,
                         uint_16            maxLen);

/*******************************************************************************
* Reads the integer value given by the key.
* @param[in]  pCfgFile  Initialized config file structure.
* @param[in]  key       Key to locate its value in the config records.
* @param[out] value     Address to store the integer value to.
* @return               ESL_CFG_OK if the key is found and assigned value
*                        is stored to the address specified by the parameter
*                        "value". If assigned value cannot be converted
*                        to any integer, "value" is set to zero then.
*                       ESL_CFG_INVALID_ARGUMENT if NULL argument given.
*                       ESL_CFG_RECORD_NOT_FOUND if given key is not found
*                        in the config file. "value" stays unchanged in this case.
*******************************************************************************/
uint_8 esl_cfg_getInteger(ESL_CFG_FILE_PTR    pCfgFile,
                          char              * key,
                          int_32            * value);

/*******************************************************************************
* Assigns a string value to the given key. The data is modified only in memory,
* config file structure needs to be closed first by calling esl_cfg_close()
* to write the changes to the config file on the filesystem.
* @param[in,out]  pCfgFile    Initialized config file structure.
* @param[in]      key         Key to be assigned a value for.
* @param[in]      value       Value to assign to the key.
* @return                     ESL_CFG_OK on success.
*                             ESL_CFG_INVALID_ARGUMENT if NULL argument given.
*                             ESL_CFG_MEMORY_FAILURE if memory allocation fails.
*******************************************************************************/
uint_8 esl_cfg_setString(ESL_CFG_FILE_PTR   pCfgFile,
                         char             * key,
                         char             * value);

/*******************************************************************************
* Assigns an integer value to the given key.
* @param[in,out]  pCfgFile    Initialized config file structure.
* @param[in]      key         Key to be assigned a value for.
* @param[in]      value       Value to be assigned to the key.
* @return                     ESL_CFG_OK on success.
*                             ESL_CFG_INVALID_ARGUMENT if NULL argument given.
*                             ESL_CFG_MEMORY_FAILURE if memory allocation fails.
*******************************************************************************/
uint_8 esl_cfg_setInteger(ESL_CFG_FILE_PTR    pCfgFile,
                          char              * key,
                          int_32              value);

/******************************************************************************/
#endif /* ESL_CFG_H_21736430403755468641630015 */
