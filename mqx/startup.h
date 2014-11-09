/** ****************************************************************************
 *
 *  @file       startup.h
 *  @brief      Startup Task.
 *
 *  This task initializes application modules and goes to the BLOCK state.
 *  It's intended to be created at the application start before all other
 *  modules.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.0 2014-11-07: Petr Kubiznak <kubiznak.petr@elnico.cz>
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

#ifndef STARTUP_H_45123647894324158786524837
#define STARTUP_H_45123647894324158786524837
//******************************************************************************

#include <mqx.h>
#include <bsp.h>

//******************************************************************************
// Task information
//******************************************************************************

#define STARTUP_TASKSTACK     3000                                              //!< Task Stack
#define STARTUP_TASKNAME      "startup"                                         //!< Task Name - should be unique

// NOTE: Task ID, start strategy and priority are application dependent and
//       that's why they shouldn't be defined here, but in the application
//       configuration in main.c!

//******************************************************************************
// Return values
//******************************************************************************

enum {
  STARTUP_OK                      = MQX_OK,
};

//******************************************************************************
// Application Time Domains
//******************************************************************************

#define TIMEDOMAIN_10MS                 0                                       //!< Index of the 10 msec time domain.
#define TIMEDOMAIN_100MS                1                                       //!< Index of the 100 msec time domain.
#define TIMEDOMAIN_250MS                2                                       //!< Index of the 250 msec time domain.

//******************************************************************************
// Keyboard
//******************************************************************************

#define KEYID_EASYBUTTON                1                                       //!< Key ID of the EasyBoard Button.

//******************************************************************************
// LED
//******************************************************************************
#define LED_ON                          (LWGPIO_VALUE_LOW)                      //!< Mapping of the "LED On" state to the HW pin level.
#define LED_OFF                         (LWGPIO_VALUE_HIGH)                     //!< Mapping of the "LED Off" state to the HW pin level.

/** @var LWGPIO_STRUCT g_lwLED
 * @brief Lightweight GPIO object for LED. */
extern LWGPIO_STRUCT g_lwLED;

//******************************************************************************
// Task related public functions
//******************************************************************************

/** Startup task.
 * @param initialData Task initial data. */
void startup_task (uint32_t u32InitialData);

//******************************************************************************
#endif /* STARTUP_H_45123647894324158786524837 */
