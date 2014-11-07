/** ****************************************************************************
 *
 *  @file       esl_nand_config.h
 *  @brief      Application nand module config file
 *
 *  Default configuration of the nandfs module. The settings should not be
 *  changed here but can be overridden in a project specific esl_config.h.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Jan Kubiznak <kubiznak.jan@elnico.cz>
 *
 *  @version    2.1 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    2.0 2014-01-04: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Integration into ESL.
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

#ifndef ESL_NAND_CONFIG_H_23323459083423849086473891
#define ESL_NAND_CONFIG_H_23323459083423849086473891

//******************************************************************************

#include "esl_config.h"

//******************************************************************************
// Main module settings
//******************************************************************************

/** @def ESL_NAND_MODULE_ENABLE
 * @brief Set 1/0 to get module enabled or disabled. */
#ifndef ESL_NAND_MODULE_ENABLE
# define ESL_NAND_MODULE_ENABLE        (0)
#endif

/** @def ESL_NAND_DEVNAME
 * @brief NAND file system drive name. To be used when opening any file in NAND. */
#ifndef ESL_NAND_DEVNAME
# define ESL_NAND_DEVNAME              "nand:"
#endif

/** @def ESL_NAND_FFSDEVNAME
 * @brief Flash file system device name. To be used exclusively just within this
 * module. It's not intended e.g. for a file access. */
#ifndef ESL_NAND_FFSDEVNAME
# define ESL_NAND_FFSDEVNAME           "nandflash_wl:"
#endif

//******************************************************************************
#endif /* ESL_NAND_CONFIG_H_23323459083423849086473891 */
