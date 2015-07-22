/** ****************************************************************************
 *
 *  @file       accelerometer.h
 *  @brief      Accelerometer control task.
 *
 *  Control task for the MMA8451Q accelerometer.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.0 2014-09-18: Petr Kubiznak <kubiznak.petr@elnico.cz>
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

#ifndef ACCELEROMETER_H_385362083936620546820752037
#define ACCELEROMETER_H_385362083936620546820752037
//******************************************************************************
#include <mqx.h>
#include <bsp.h>
#if (MQX_VERSION >= 410)
# include "psptypes_legacy.h"
#endif

#include "easyduo_mcc_common.h"

//******************************************************************************
// Task information
//******************************************************************************

#define ACCEL_TASKSTACK       3000                                              //!< Task Stack
#define ACCEL_TASKNAME        "accelerometer"                                   //!< Task Name - should be unique

// NOTE: Task ID, start strategy and priority are application dependent and
//       that's why they shouldn't be defined here, but in the application
//       configuration in main.c!

//******************************************************************************
// Return values
//******************************************************************************

enum {
  ACCEL_OK                        = MQX_OK,
  ACCEL_LWEVENT_FAILURE,
  ACCEL_LWSEM_FAILURE,
  ACCEL_OUTDATED,
  ACCEL_MODULE_OFF,
};

//******************************************************************************
// Public types
//******************************************************************************

typedef struct t_accel_data_struct {
  uint32_t  u32Timestamp;                                                       //!< Data timestamp (simple increasing integer).
  float     afData[3];                                                          //!< Accelerometer 3-axis data.
} TAccelData;

//******************************************************************************
// Task related public functions
//******************************************************************************

/** Accelerometer task.
 * @param initialData Task initial data. */
void accel_task (uint32_t u32InitialData);

/** Retrieves accelerometer identifier, as defined in easyduo_mcc_common.h.
 * @return      ACCEL_TYPE_MMA8451Q, ACCEL_TYPE_MMA8452Q, ACCEL_TYPE_MMA8453Q.
                ACCEL_TYPE_UNKNOWN if not known. */
int32_t accel_getIdentifier (void);

/** Retrieves the last measured accelerometer data, guarded by a semaphore.
 * @param[out]  poDst         Destination memory to store the data to.
 * @param[in]   u32WaitTicks  Semaphore wait timeout ticks. Use 0 for infinity.
 * @return      ACCEL_OK on success.
 *              ACCEL_LWSEM_FAILURE if waiting for semaphore fails.
 *              ACCEL_OUTDATED if the read data is outdated because the module
 *              switched to the standby mode. Call this function within
 *              (ACCEL_MAX_MISSED_CNT * ACCEL_PERIODIC_INTERVAL) to retrieve
 *              up-to-date data. Anyway, the data is copied. */
uint_8 accel_getLastData (TAccelData  * poDst,
                          uint_32       u32WaitTicks);

//******************************************************************************
#endif // ACCELEROMETER_H_385362083936620546820752037 //
