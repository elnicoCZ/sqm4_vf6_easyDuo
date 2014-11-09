/** ****************************************************************************
 *
 *  @file       mcc.h
 *  @brief      Multicore communication task.
 *
 *  Realizes communication with the A5 core.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.0 2014-11-09: Petr Kubiznak <kubiznak.petr@elnico.cz>
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

#ifndef MCC_H_237678262778876362057387698
#define MCC_H_237678262778876362057387698
//******************************************************************************
#include <mqx.h>
#include <bsp.h>
#if (MQX_VERSION >= 410)
# include "psptypes_legacy.h"
#endif

//******************************************************************************
// Task information

#define MCC_TASKSTACK                   2000                                    //!< Task stack
#define MCC_TASKNAME                    "mcc"                                   //!< Task Name - should be unique

// NOTE: Task start strategy and priority is application dependent and that's
//       why it shouldn't be defined here, but in an application configuration!

//******************************************************************************
// Return values
//******************************************************************************

enum {
  MCC_OK                          = MQX_OK,
  MCC_INIT_FAILURE,
  MCC_INFO_FAILURE,
  MCC_ENDPOINT_FAILURE,
};

//******************************************************************************

/** Multicore communication task.
 * @param [in] initialData Task initial data. */
void mcc_task (uint_32 u32InitialData);

//******************************************************************************
#endif // MCC_H_237678262778876362057387698 //
