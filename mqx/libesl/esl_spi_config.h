/** ****************************************************************************
 *
 *  @file       esl_spi_config.h
 *  @brief      SPI bus module configuration.
 *
 *  This module consists of the only one function, which purpose is to reinit
 *  the SPI bus at runtime as needed.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Jan Kubiznak <kubiznak.jan@elnico.cz>
 *
 *  @version    1.1 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    1.0 2014-01-07: Jan Kubiznak <kubiznak.jan@elnico.cz>
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

#ifndef ESL_SPI_CONFIG_H_39483209385947582928983494
#define ESL_SPI_CONFIG_H_39483209385947582928983494

//******************************************************************************

#include "esl_config.h"

//******************************************************************************
// Main module settings
//******************************************************************************

/** @def ESL_SPI_MODULE_ENABLE
 * @brief Set 1/0 to get module enabled or disabled. */
#ifndef ESL_SPI_MODULE_ENABLE
# define ESL_SPI_MODULE_ENABLE           (0)
#endif

//******************************************************************************

/** @def ESL_SPI_BUSCONFIG
 * @brief SPI bus configurations available by default. */
#ifndef ESL_SPI_BUSCONFIG
//                          Channel,  baud, clock mode           , endianity            , transfer mode.
# define ESL_SPI_BUSCONFIG  {"spi0:", 10e6, SPI_CLK_POL_PHA_MODE0, SPI_DEVICE_BIG_ENDIAN, SPI_DEVICE_MASTER_MODE}, \
                            {"spi2:", 40e6, SPI_CLK_POL_PHA_MODE0, SPI_DEVICE_BIG_ENDIAN, SPI_DEVICE_MASTER_MODE}
#endif

//******************************************************************************

#endif // ESL_SPI_CONFIG_H_39483209385947582928983494
