/** ****************************************************************************
 *
 *  @file       esl_nand.h
 *  @brief      Set of functions for the NAND memory handling.
 *
 *  This module provides basically just functions for the NAND filesystem
 *  initialization and deinitialization. An access to the data (files) stored
 *  in this memory should be done by classic MFS access functions. For that
 *  this module also exports the name of the NAND file system drive.
 *  Hint: This module uses two static global handles. An access to them is not
 *        anyhow guarded. In case of a frequent init/deinit of the NAND
 *        file system it should be considered to implement a new handling task
 *        encapsulating these globals instead of just this module.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Jan Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    2.1 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    2.0 2014-01-04: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Integration into ESL.
 *
 *  @version    1.1 2013-05-26: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              nandflash_installWl and nandflash_eraseChip
 *                              functions added.
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

#ifndef ESL_NAND_H_10943983013059592013030123
#define ESL_NAND_H_10943983013059592013030123

//******************************************************************************

#include "esl_nand_config.h"

//******************************************************************************

// Module specific log IDs
enum {
  ESL_NAND_OK = MQX_OK,
  ESL_NAND_MODULE_OFF,
  ESL_NAND_HDLNANDFLASH_OPEN,
  ESL_NAND_HDLNANDFS_OPEN,
  ESL_NAND_IO_NANDFLASH_WL_INSTALL,
  ESL_NAND_FOPENDEV,
  ESL_NAND_IO_MFS_INSTALL,
  ESL_NAND_FOPENFS,
  ESL_NAND_FORMAT_NEEDED,
  ESL_NAND_FCLOSEFS,
  ESL_NAND_IO_DEV_UNINSTALL,
  ESL_NAND_FCLOSEDEV
};

//******************************************************************************

/** Installs the wear-levelling module for the NAND memory FS. It's not needed
 * if esl_nand_initFs is called with u8InstallWl=TRUE. Might be needed in case,
 * in which the wear levelling module is installed in the application
 * initialization phase, but the NAND FS is initialized and deinitialized during
 * the application run several times.
 * @return                   ESL_NAND_OK on success, non-zero on failure. */
uint_8 esl_nand_installWl ();

/** Initializes and opens the NAND file system.
 * @param [in]  boInstallWl  Flag to call nandflash_wl_install within this function
 *                           or not. Use 1 to call it or 0 to not to call it.
 * @param [out] err          Value adjusted in case of failure by commands embedded
 *                           in the function.
 * @return                   ESL_NAND_FORMAT_NEEDED if initialization was
 *                           successful, but the NAND needs to be formatted.
 *                           ESL_NAND_OK in case of a full success (so there is
 *                           also an accessible drive on NAND.
 *                           Other ESL_NAND_* value on failure. */
uint_8 esl_nand_initFs (uint_8 u8InstallWl, _mqx_int *err);

/** Closes the NAND file system.
 * @param [out] err          Value adjusted in case of failure by commands embedded
 *                           in the function.
 * @return                   ESL_NAND_OK on success, non-zero on failure. */
uint_8 esl_nand_deinitFs (_mqx_int *err);

/** This function is used to erase all blocks in the NAND flash memory. Simply,
 * these blocks are erased directly by MFS ioctl. The wear leveling module is
 * not installed.
 * Hint: If it is the first time a NAND memory is used, then this command shall
 *       be run first!
 * @param [out] err          Value adjusted in case of failure by commands embedded
 *                           in the function.
 * @return                   ESL_NAND_OK on success, non-zero on failure. */
uint_8 esl_nand_eraseChip (_mqx_int *err);

/** Provides the NAND filesystem handle. This is needed to call functions
 * from the general FS library (like fs_cd()).
 * @return   Pointer the the NAND file system handle. Could be NULL if the FS
 *           is not initialized the whole module is OFF. */
MQX_FILE_PTR esl_nand_getHandle (void);

//******************************************************************************

#endif /* ESL_NAND_H_10943983013059592013030123 */
