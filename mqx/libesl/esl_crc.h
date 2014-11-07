/** ****************************************************************************
 *
 *  @file       esl_crc.h
 *  @brief      CRC module
 *
 *  Intent of this module is just to simplify the access to the CRC peripheral.
 *  It still expects understanding of the peripheral, e.g. that it cannot
 *  be used independently from two places at the same time - no locking
 *  mechanism is implemented.
 *
 *  Firstly initialize the module using esl_crc_init(), then use either
 *  esl_crc_write() or esl_crc_write32() to fill in the data (but use only
 *  one of these functions in a session) and finally use esl_crc_read()
 *  whenever you want to read the checksum (beware of the protocol width).
 *
 *  When the job is done, call esl_crc_deinit() to release the module
 *  or esl_crc_reinit() to start a new session.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.3 2014-06-27: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Vybrid support implemented (#163).
 *
 *  @version    1.2 2014-04-17: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              esl_crc_calcForBuf added.
 *
 *  @version    1.1 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    1.0 2013-12-23: Petr Kubiznak <kubiznak.petr@elnico.cz>
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

#ifndef ESL_CRC_H_87548726331466542873972785
#define ESL_CRC_H_87548726331466542873972785
//******************************************************************************

#include "esl_crc_config.h"

#include <mqx.h>
#include <bsp.h>

//******************************************************************************
// Return values
//******************************************************************************
enum {
  ESL_CRC_OK = MQX_OK,
  ESL_CRC_INVALID_ARG,
  ESL_CRC_NOT_INITIALIZED,
  ESL_CRC_ALREADY_INITIALIZED,
  ESL_CRC_MODULE_OFF,
  ESL_CRC_INVALID_VALUE = 0xFFFFFFFF,
};

//******************************************************************************
// Predefined seeds
//******************************************************************************
#define ESL_CRC_SEED_DEFAULT            (0xFFFFFFFF)

//******************************************************************************
// Predefined polynomials
//******************************************************************************
#define ESL_CRC_POLYNOMIAL_DEFAULT      (0x00001021)
#define ESL_CRC_POLYNOMIAL_16_CCITT     (0x00001021)
#define ESL_CRC_POLYNOMIAL_16_ARINC     (0x0000A02B)
#define ESL_CRC_POLYNOMIAL_16_CDMA2000  (0x0000C867)
#define ESL_CRC_POLYNOMIAL_16_DECT      (0x00000589)
#define ESL_CRC_POLYNOMIAL_16_T10DIF    (0x00008BB7)
#define ESL_CRC_POLYNOMIAL_16_DNP       (0x00003D65)
#define ESL_CRC_POLYNOMIAL_16_ANSI      (0x00008005)
#define ESL_CRC_POLYNOMIAL_32           (0x04C11DB7)
#define ESL_CRC_POLYNOMIAL_32C          (0x1EDC6F41)
#define ESL_CRC_POLYNOMIAL_32K          (0x741B8CD7)
#define ESL_CRC_POLYNOMIAL_32Q          (0x814141AB)

//******************************************************************************
// CRC Control Register Flags
//******************************************************************************
/** @def ESL_CRC_WIDTH_16_BIT, ESL_CRC_WIDTH_32_BIT
 * @brief Use either ESL_CRC_WIDTH_16_BIT or ESL_CRC_WIDTH_32_BIT flag
 *        to set the width of CRC protocol. */
#define ESL_CRC_WIDTH_16_BIT            (0x0 << (CRC_CTRL_TCRC_SHIFT))
#define ESL_CRC_WIDTH_32_BIT            (0x1 << (CRC_CTRL_TCRC_SHIFT))

/** @def ESL_CRC_FXOR
 * @brief Use this flag to invert or complement the read value of the CRC
 *        data register. */
#define ESL_CRC_FXOR                    (CRC_CTRL_FXOR_MASK)

/** @def ESL_CRC_TOTR_BITS, ESL_CRC_TOTR_BYTES, ESL_CRC_TOTR_BOTH
 * @brief Set the transpose configuration of the value read from the CRC
 *        data register. Refer to the description of the transpose feature
 *        for the available transpose options.
 *        Please note this feature is not available on Vybrid. */
#define ESL_CRC_TOTR_BITS               (CRC_CTRL_TOTR(0x1))
#define ESL_CRC_TOTR_BYTES              (CRC_CTRL_TOTR(0x3))
#define ESL_CRC_TOTR_BOTH               (CRC_CTRL_TOTR(0x2))

/** @def ESL_CRC_TOTW_BITS, ESL_CRC_TOTW_BYTES, ESL_CRC_TOTW_BOTH
 * @brief Set the transpose configuration of the data written to the CRC
 *        data register. Refer to the description of the transpose feature
 *        for the available transpose options.
 *        Please note this feature is not available on Vybrid. */
#define ESL_CRC_TOTW_BITS               (CRC_CTRL_TOT(0x1))
#define ESL_CRC_TOTW_BYTES              (CRC_CTRL_TOT(0x3))
#define ESL_CRC_TOTW_BOTH               (CRC_CTRL_TOT(0x2))

//******************************************************************************
// Public Functions
//******************************************************************************

/** Clocks on and initializes the CRC peripheral.
 * @param[in] u32ctrl   Control Register configuration flags. Use logical sum
 *                      of ESL_CRC_WIDTH_16_BIT / ESL_CRC_WIDTH_32_BIT,
 *                      ESL_CRC_FXOR,
 *                      ESL_CRC_TOTR_BITS / ESL_CRC_TOTR_BYTES / ESL_CRC_TOTR_BOTH
 *                      and ESL_CRC_TOTW_BITS / ESL_CRC_TOTW_BYTES / ESL_CRC_TOTW_BOTH.
 *                      If no flag specified, 16bit protocol with no special
 *                      functions is used.
 * @param[in] u32polynomial The polynomial for the CRC calculation.
 *                      For 16bit protocol, only the lower 16 bits are used.
 * @param[in] u32seed   Seed value.
 *                      For 16bit protocol, only the lower 16 bits are used.
 * @return    ESL_CRC_OK on success.
 *            ESL_CRC_ALREADY_INITIALIZED if the module is already initialized.
 *             @see esl_crc_reinit to reinitialize it for new session.
 *            ESL_CRC_MODULE_OFF if the module is turned off. */
uint_8 esl_crc_init (uint_32 u32ctrl, uint_32 u32polynomial, uint_32 u32seed);

/** Does exactly the same as @see esl_crc_init except of that it does not
 *  perform the test whether the module is already intialized.
 * @return    ESL_CRC_OK on success.
 *            ESL_CRC_MODULE_OFF if the module is turned off. */
uint_8 esl_crc_reinit (uint_32 u32ctrl, uint_32 u32polynomial, uint_32 u32seed);

/** Clocks off the CRC peripheral.
 * @return    ESL_CRC_OK on success.
 *            ESL_CRC_NOT_INITIALIZED if the module is not initialized.
 *            ESL_CRC_MODULE_OFF if the module is turned off. */
uint_8 esl_crc_deinit (void);

/** Returns the checksum value. Do not use before the module is successfully
 *  initialized.
 * @return  Current CRC. For 16bit protocol, only the lower 16 bits are valid,
 *          with the upper 16 bits containing undeterminated value.
 *          If not initialized, ESL_CRC_INVALID_VALUE is returned. */
uint_32 esl_crc_read (void);

/** Writes 1 byte to the CRC data register. During one session, use either
 *  this function or @see esl_crc_write32, which writes 4 bytes at once.
 *  Do NOT use both functions during one session!
 * @param[in] byte  One data byte. */
void esl_crc_write (uint_8 byte);
/** Writes 4 bytes to the CRC data register. During one session, use either
 *  this function or @see esl_crc_write32, which writes 4 bytes at once.
 *  Do NOT use both functions during one session!
 * @param[in] data  4 bytes of data where the MSB represents the first byte
 *                  in the data flow, the LSB represents the last one. */
void esl_crc_write32 (uint_32 data);

/** Calculates the CRC for the input buffer.
 * @param[in] u32Ctrl   Control Register configuration flags. Use logical sum
 *                      of ESL_CRC_WIDTH_16_BIT / ESL_CRC_WIDTH_32_BIT,
 *                      ESL_CRC_FXOR,
 *                      ESL_CRC_TOTR_BITS / ESL_CRC_TOTR_BYTES / ESL_CRC_TOTR_BOTH
 *                      and ESL_CRC_TOTW_BITS / ESL_CRC_TOTW_BYTES / ESL_CRC_TOTW_BOTH.
 *                      If no flag specified, 16bit protocol with no special
 *                      functions is used.
 * @param[in]  u32Polynomial The polynomial for the CRC calculation.
 *                           For 16bit protocol, only the lower 16 bits are used.
 * @param[in]  u32Seed       Seed value.
 *                           For 16bit protocol, only the lower 16 bits are used.
 * @param[in]  pu8Buf        Input data buffer.
 * @param[in]  u32BufLen     Input data buffer length.
 * @param[out] pu32Result    CRC calculation result.
 * @return    ESL_CRC_OK on success.
 *            ESL_CRC_MODULE_OFF if the module is turned off. */
uint_8 esl_crc_calcForBuf (uint_32         u32Ctrl,
                           uint_32         u32Polynomial,
                           uint_32         u32Seed,
                           const uint_8  * pu8Buf,
                           uint_32         u32BufLen,
                           uint_32       * pu32Result);

//******************************************************************************
#endif /* ESL_CRC_H_87548726331466542873972785 */
