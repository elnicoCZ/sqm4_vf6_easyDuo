/** ****************************************************************************
 *
 *  @file       esl_mcfs.h
 *  @brief      MCC filesystem client side.
 *
 *  This module contains main functionality of the MCC filesystem MQX client.
 *
 *  The module consists of two sides - MQX client and a remote (probably Linux)
 *  server. Firstly the remote server must be run, successfully initializing
 *  MCC endpoint as configured in esl_mcfs_config.h. Then _io_mcfs_install()
 *  must be called at the client side to install the virtual filesystem to MQX.
 *  Then standard IO functions (open, read, ioctl, ...) can be used to access
 *  the remote filesystem as a local MFS filesystem.
 *
 *  @copyright  Elnico s.r.o. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    2.0 2014-01-30: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Integrated into ESL, renamed from mccfscli.h
 *                              to esl_mcfs.h.
 *
 *  @version    1.0 2013-10-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
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

#ifndef ESL_MCFS_H_42395623540923692495090348
#define ESL_MCFS_H_42395623540923692495090348
//******************************************************************************

#include "esl_mcfs_config.h"

#include <mqx.h>
#include <bsp.h>

//******************************************************************************
// Platform check - available for VF6 only
//******************************************************************************

#if ESL_MCFS_MODULE_ENABLE && (MQX_CPU != PSP_CPU_VF65GS10_M4)
# warning "MCFS module is only available for Vybrid VF6 CPU core M4"
# undef ESL_MCFS_MODULE_ENABLE
# define ESL_MCFS_MODULE_ENABLE         (0)
#endif // ESL_MCFS_MODULE_ENABLE && !VF6 //

//******************************************************************************
// Return values
//******************************************************************************
enum {
  ESL_MCFS_OK = MQX_OK,
  ESL_MCFS_NOT_INITIALIZED,
  ESL_MCFS_INITIALIZED,
  ESL_MCFS_LWSEM_CREATE_FAILURE,
  ESL_MCFS_LWSEM_WAIT_FAILURE,
  ESL_MCFS_MCC_INIT_FAILURE,
  ESL_MCFS_MCC_CREATE_ENDPOINT_FAILURE,
  ESL_MCFS_MCC_INFO_FAILURE,
  ESL_MCFS_MCC_VERSION_MISMATCH,
  ESL_MCFS_MCC_FREE_BUFFER_FAILURE,
  ESL_MCFS_MCC_RECV_FAILURE,
  ESL_MCFS_MCC_SEND_FAILURE,
  ESL_MCFS_ACK_FAILURE,
  ESL_MCFS_PARAM_CONTROL_HASH_FAILURE,
  ESL_MCFS_MEMORY_FAILURE,
  ESL_MCFS_INSUFFICIENT_BUFFER_SIZE,
  ESL_MCFS_DEV_INSTALL_FAILURE,
  ESL_MCFS_FS_REGISTRATION_FAILURE,
  ESL_MCFS_SHARING_VIOLATION,
  ESL_MCFS_PATH_NOT_FOUND,
  ESL_MCFS_COMMUNICATION_FAILURE,
  ESL_MCFS_OPERATION_FAILURE,
  ESL_MCFS_INVALID_ARGUMENT,
  ESL_MCFS_UNIMPLEMENTED_OPERATION,
  ESL_MCFS_MODULE_OFF,
};

//******************************************************************************
// Public functions
//******************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

/** Installs MCFS filesystem. Remote server must already be initialized
 *  and running.
 * @param[in] sIdentifier       Local filesystem identifier, e.g. "mcfs:".
 * @param[in] sRemoteIdentifier Remote filesystem identifier = root directory,
 *                              e.g. "/mnt/mcfs/".
 * @return    ESL_MCFS_OK on success, various error codes on failure. */
extern uint_32  _io_mcfs_install    (const char_ptr sIdentifier,
                                     const char_ptr sRemoteIdentifier);

#ifdef __cplusplus
}
#endif

//******************************************************************************
#endif // ESL_MCFS_H_42395623540923692495090348 //
