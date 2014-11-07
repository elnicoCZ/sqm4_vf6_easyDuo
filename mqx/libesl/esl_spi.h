/** ****************************************************************************
 *
 *  @file       esl_spi.h
 *  @brief      SPI bus module.
 *
 *  This module consists of the only one function, which purpose is to reinit
 *  the SPI bus at runtime as needed.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Jan Kubiznak <kubiznak.petr@elnico.cz>
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

#ifndef ESL_SPI_H_59023985498412093839753929
#define ESL_SPI_H_59023985498412093839753929

//******************************************************************************

#include "esl_spi_config.h"

//******************************************************************************

// Module specific log IDs
enum {
  ESL_SPI_OK = MQX_OK,
  ESL_SPI_MODULE_OFF,
  ESL_SPI_INVALID_ARG,
  ESL_SPI_FOPEN,
  ESL_SPI_IOCTL_SET_BAUD,
  ESL_SPI_IOCTL_SET_MODE,
  ESL_SPI_IOCTL_SET_ENDIAN,
  ESL_SPI_IOCTL_SET_TRANSFER_MODE,
  ESL_SPI_FCLOSE
};

//******************************************************************************

/** Call this function to reinit the SPI bus.
 * @param [in]  u8ConfigIdx  Index of the SPI bus configuration defined by
 *                           ESL_SPI_BUSCONFIG.
 * @param [out] err          Value adjusted in case of failure by commands
 *                           embedded in the function.
 * @return                   ESL_SPI_OK on success, other value on failure. */
uint_8 esl_spi_busReinit (uint_8 u8ConfigIdx, _mqx_int *err);

//******************************************************************************

#endif // ESL_SPI_H_59023985498412093839753929
