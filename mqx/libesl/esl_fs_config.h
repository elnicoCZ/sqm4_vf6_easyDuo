/** ****************************************************************************
 *
 *  @file       esl_fs_config.h
 *  @brief      General file system API config file
 *
 *  Default configuration of the FS module. The settings should not be changed
 *  here but can be overridden in a project specific esl_config.h.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Jan Kubiznak <kubiznak.jan@elnico.cz>
 *
 *  @version    2.2 2014-10-04: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Copy block size decreased from 4096B to only
 *                              256B to avoid easy to get stack overflows.
 *
 *  @version    2.1 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    2.0 2013-11-24: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Initial revision for esl_fs v2.0.
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

#ifndef ESL_FS_CONFIG_H_75846926876752675786722565
#define ESL_FS_CONFIG_H_75846926876752675786722565
//******************************************************************************

#include "esl_config.h"

//******************************************************************************
// Main module settings
//******************************************************************************

/** @def ESL_FS_MODULE_ENABLE
 * @brief Set 1/0 to get module enabled or disabled. */
#ifndef ESL_FS_MODULE_ENABLE
# define ESL_FS_MODULE_ENABLE           (0)
#endif

//******************************************************************************
// Size settings
//******************************************************************************

/** @def ESL_FS_MAXDEVNAMELEN
 * @brief Maximal supported length of the device name (sd:, nand:, ...). */
#ifndef ESL_FS_MAXDEVNAMELEN
# define ESL_FS_MAXDEVNAMELEN           (8)
#endif

/** @def ESL_FS_CPDIR_MAXFILECNT
 * @brief Maximal supported count of files in folder, which are processed
 *        by cpdir. */
#ifndef ESL_FS_CPDIR_MAXFILECNT
# define ESL_FS_CPDIR_MAXFILECNT        (50)
#endif

/** @def ESL_FS_CPDIR_MAXNESTING
 * @brief Maximal supported nesting level (of directories),
 *        which cpdir is able to process. */
#ifndef ESL_FS_CPDIR_MAXNESTING
# define ESL_FS_CPDIR_MAXNESTING        (10)
#endif

/** @def ESL_FS_CP_BLOCKSIZE
 * @brief Block size to copy by the cp command in bytes. Higher blocksize means
 * faster copy operation. The default value is kept pretty small to not to
 * cause a task stack overflow easily. It's recommended to increase this value
 * in the application, but with respect to the caller task stack size. */
#ifndef ESL_FS_CP_BLOCKSIZE
# define ESL_FS_CP_BLOCKSIZE            (256)
#endif

//******************************************************************************
#endif // ESL_FS_CONFIG_H_75846926876752675786722565 //
