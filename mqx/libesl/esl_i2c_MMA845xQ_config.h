/** ****************************************************************************
 *
 *  @file       esl_i2c_MMA845xQ_config.h
 *  @brief      I2C_MMA845xQ module config file
 *
 *  Default configuration of the I2C_MMA845xQ module. The settings should not
 *  be changed here but can be overridden in a project specific esl_config.h.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.0 2014-09-16: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Initial revision for esl_i2c_MMA845xQ v1.0.
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

#ifndef ESL_I2C_MMA845XQ_CONFIG_H_26574037457462104540074254
#define ESL_I2C_MMA845XQ_CONFIG_H_26574037457462104540074254
//******************************************************************************

#include "esl_config.h"

//******************************************************************************
// Main module settings
//******************************************************************************

/** @def ESL_I2C_MMA845XQ_MODULE_ENABLE
 * @brief Set 1/0 to get module enabled or disabled. */
#ifndef ESL_I2C_MMA845XQ_MODULE_ENABLE
# define ESL_I2C_MMA845XQ_MODULE_ENABLE (0)
#endif

//******************************************************************************
#endif /* ESL_I2C_MMA845XQ_CONFIG_H_26574037457462104540074254 */
