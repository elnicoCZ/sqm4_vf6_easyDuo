/** ****************************************************************************
 *
 *  @file       esl_i2c_config.h
 *  @brief      I2C module config file
 *
 *  Default configuration of the i2c module. The settings should not be changed
 *  here but can be overridden in a project specific esl_config.h.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    2.2 2014-11-07: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              core_mutex locking option added for VF6.
 *
 *  @version    2.1 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    2.0 2014-01-07: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Initial revision for esl_i2c v2.0.
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

#ifndef ESL_I2C_CONFIG_H_96670630923252070536236520
#define ESL_I2C_CONFIG_H_96670630923252070536236520
//******************************************************************************

#include "esl_config.h"

//******************************************************************************
// Main module settings
//******************************************************************************

/** @def ESL_I2C_MODULE_ENABLE
 * @brief Set 1/0 to get module enabled or disabled. */
#ifndef ESL_I2C_MODULE_ENABLE
# define ESL_I2C_MODULE_ENABLE          (0)
#endif

/** @def ESL_I2C_CHANNELNAMEMAXLEN
 * @brief Maximum length of the i2c channel names (e.g. "ii2c0:"). */
#ifndef ESL_I2C_CHANNELNAMEMAXLEN
# define ESL_I2C_CHANNELNAMEMAXLEN      (10)
#endif

/** @def ESL_I2C_COREMUTEX_I2C_CHANNEL
 * @brief I2C channel to use the core_mutex API as mutual access mechanism.
 *        Use values of ESL_I2C0_NO, ESL_I2C1_NO, ESL_I2C2_NO and ESL_I2C3_NO.
 *        Any other value turns off this feature.
 *        This is only applicable on VF6. Also note core_mutex API provides
 *        blocking calls only without timeout; timeouts are hence ignored. */
#ifndef ESL_I2C_COREMUTEX_I2C_CHANNEL
# define ESL_I2C_COREMUTEX_I2C_CHANNEL  (-1)
#endif

//******************************************************************************
// Channel 0 settings
//******************************************************************************

/** @def ESL_I2C0_ENABLED
 * @brief Set to any non-zero value to enable the channel 0.
 *        It is done automatically here by using BSP definitions. */
#ifndef ESL_I2C0_ENABLED
# define ESL_I2C0_ENABLED               (BSPCFG_ENABLE_I2C0 + BSPCFG_ENABLE_II2C0)
#endif

/** @def ESL_I2C0_NAMEPOL
 * @brief Name of the I2C channel 0, polled driver mode. */
#ifndef ESL_I2C0_NAMEPOL
# define ESL_I2C0_NAMEPOL               "i2c0:"
#endif

/** @def ESL_I2C0_NAMEIRQ
 * @brief Name of the I2C channel 0, interrupt driver mode. */
#ifndef ESL_I2C0_NAMEIRQ
# define ESL_I2C0_NAMEIRQ               "ii2c0:"
#endif

//******************************************************************************
// Channel 1 settings
//******************************************************************************

/** @def ESL_I2C1_ENABLED
 * @brief Set to any non-zero value to enable the channel 1.
 *        It is done automatically here by using BSP definitions. */
#ifndef ESL_I2C1_ENABLED
# define ESL_I2C1_ENABLED               (BSPCFG_ENABLE_I2C1 + BSPCFG_ENABLE_II2C1)
#endif

/** @def ESL_I2C1_NAMEPOL
 * @brief Name of the I2C channel 1, polled driver mode. */
#ifndef ESL_I2C1_NAMEPOL
# define ESL_I2C1_NAMEPOL               "i2c1:"
#endif

/** @def ESL_I2C1_NAMEIRQ
 * @brief Name of the I2C channel 1, interrupt driver mode. */
#ifndef ESL_I2C1_NAMEIRQ
# define ESL_I2C1_NAMEIRQ               "ii2c1:"
#endif

//******************************************************************************
// Channel 2 settings
//******************************************************************************

/** @def ESL_I2C2_ENABLED
 * @brief Set to any non-zero value to enable the channel 2.
 *        It is done automatically here by using BSP definitions. */
#ifndef ESL_I2C2_ENABLED
# define ESL_I2C2_ENABLED               (BSPCFG_ENABLE_I2C2 + BSPCFG_ENABLE_II2C2)
#endif

/** @def ESL_I2C2_NAMEPOL
 * @brief Name of the I2C channel 2, polled driver mode. */
#ifndef ESL_I2C2_NAMEPOL
# define ESL_I2C2_NAMEPOL               "i2c2:"
#endif

/** @def ESL_I2C2_NAMEIRQ
 * @brief Name of the I2C channel 2, interrupt driver mode. */
#ifndef ESL_I2C2_NAMEIRQ
# define ESL_I2C2_NAMEIRQ               "ii2c2:"
#endif

//******************************************************************************
// Channel 3 settings
//******************************************************************************

/** @def ESL_I2C3_ENABLED
 * @brief Set to any non-zero value to enable the channel 3.
 *        It is done automatically here by using BSP definitions. */
#ifndef ESL_I2C3_ENABLED
# define ESL_I2C3_ENABLED               (BSPCFG_ENABLE_I2C3 + BSPCFG_ENABLE_II2C3)
#endif

/** @def ESL_I2C3_NAMEPOL
 * @brief Name of the I2C channel 3, polled driver mode. */
#ifndef ESL_I2C3_NAMEPOL
# define ESL_I2C3_NAMEPOL               "i2c3:"
#endif

/** @def ESL_I2C3_NAMEIRQ
 * @brief Name of the I2C channel 3, interrupt driver mode. */
#ifndef ESL_I2C3_NAMEIRQ
# define ESL_I2C3_NAMEIRQ               "ii2c3:"
#endif

//******************************************************************************
#endif /* ESL_I2C_CONFIG_H_96670630923252070536236520 */
