/** ****************************************************************************
 *
 *  @file       esl_spimem.h
 *  @brief      Set of functions for the SPI FLASH & EEPROM memory handling.
 *
 *  This module provides functions for a work with memories connected via SPI.
 *  It's based on spi_memory.c/.h 3.8.1.0 from the mqx\examples\spi\.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Jan Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.2 2014-04-21: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Support for calls from multiple tasks added.
 *
 *  @version    1.1 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    1.0 2014-01-05: Jan Kubiznak <kubiznak.jan@elnico.cz>
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

#ifndef ESL_SPIMEM_H_39502948593090293949502931
#define ESL_SPIMEM_H_39502948593090293949502931

//******************************************************************************

#include "esl_spimem_config.h"

//******************************************************************************

// Module specific log IDs
enum {
  ESL_SPIMEM_OK = MQX_OK,
  ESL_SPIMEM_MODULE_OFF,
  ESL_SPIMEM_INVALID_ARG,
  ESL_SPIMEM_FOPEN,
  ESL_SPIMEM_FCLOSE,
  ESL_SPIMEM_FWRITE,
  ESL_SPIMEM_FWRITE_ADDR,
  ESL_SPIMEM_FWRITE_DATA,
  ESL_SPIMEM_FREAD,
  ESL_SPIMEM_FFLUSH,
  ESL_SPIMEM_INVALID_ADDRLEN,
  ESL_SPIMEM_LWSEM_CREATE,
  ESL_SPIMEM_LWSEM_WAIT_TICKS,
};

//******************************************************************************

/** Memory configuration structure. */
typedef struct {
  uint_8    u8AddrLen;               //!< Count of address bytes.
  uint_32   u32MaxFreq;              //!< Maximal allowed chip clock frequency.

  uint_32   u32PageSize;             //!< Page size.
  uint_32   u32SectorSize;           //!< Sector size. Applies just for FLASH memories.
  uint_32   u32PageCnt;              //!< Page count.

  uint_8    u8CmdWriteStatus;        //!< Command: Write status.
  uint_8    u8CmdWriteData;          //!< Command: Write data.
  uint_8    u8CmdReadData;           //!< Command: Read data.
  uint_8    u8CmdWriteDisable;       //!< Command: Write latch disable.
  uint_8    u8CmdReadStatus;         //!< Command: Read status.
  uint_8    u8CmdWriteEnable;        //!< Command: Write latch enable.
  uint_8    u8CmdReadId;             //!< Command: Read id. Applies just for FLASH memories.
  uint_8    u8CmdSectorErase;        //!< Command: Sector erase. Applies just for FLASH memories.
  uint_8    u8CmdChipErase;          //!< Command: Chip erase. Applies just for FLASH memories.

  uint_8    u8StatusWIP;             //!< Status bit: Write in progress.
  uint_8    u8StatusWEL;             //!< Status bit: Write enable latch.
  uint_8    u8StatusBP0;             //!< Status bit: Block protect 0.
  uint_8    u8StatusBP1;             //!< Status bit: Block protect 1.
  uint_8    u8StatusWPEN;            //!< Status bit: Write protect enabled.

  uint_8    u8WriteCycleTime;        //!< Write cycle time in msec.
  uint_16   u16SectorEraseTime;      //!< Sectore erase time in msec.

} ESL_SPIMEM_TChipCfg;

//******************************************************************************

/** Initializes the esl_spimem interfaces. Shall be called first before all
 * other esl_spimem_* functions.
 * @param [out] err       Error details will be stored here in case of failure.
 * @return                ESL_SPIMEM_OK on success, other on failure. */
uint_8 esl_spimem_init (_mqx_int * err);

/** Opens the SPI chip specifed by name.
 * @param [out] phDev     Function output (handle to the opened SPI memory).
 * @param [in]  psDevName SPI channel name of the device to open.
 *                        Example: "spi0:1"
 * @param [in]  poCfg     Pointer to the chip config structure.
 * @param [out] err       Error details will be stored here in case of failure.
 * @return                ESL_SPIMEM_OK on success, other on failure. */
uint_8 esl_spimem_open (MQX_FILE_PTR              * phDev,
                        const char                * psDevName,
                        const ESL_SPIMEM_TChipCfg * poCfg,
                        _mqx_int                  * err);

/** Closes the opened SPI chip and sets the handle to NULL.
 * @param [in]  phDev     Open device handle.
 * @param [in]  poCfg     Pointer to the chip config structure.
 * @param [out] err       Error details will be stored here in case of failure.
 * @return                ESL_SPIMEM_OK on success, other on failure. */
uint_8 esl_spimem_close (MQX_FILE_PTR              * phDev,
                         const ESL_SPIMEM_TChipCfg * poCfg,
                         _mqx_int                  * err);

/** Erases the entire chip.
 * @param [in]  hDev      Open device handle.
 * @param [in]  poCfg     Pointer to the chip config structure.
 * @param [out] err       Error details will be stored here in case of failure.
 * @return                ESL_SPIMEM_OK on success, other on failure. */
uint_8 esl_spimem_chipErase (MQX_FILE_PTR                hDev,
                             const ESL_SPIMEM_TChipCfg * poCfg,
                             _mqx_int                  * err);

/** Erases one memory sector.
 * @param [in]  hDev      Open device handle.
 * @param [in]  poCfg     Pointer to the chip config structure.
 * @param [in]  u32Addr   Address of the memory sector to erase.
 * @param [out] err       Error details will be stored here in case of failure.
 * @return                ESL_SPIMEM_OK on success, other on failure. */
uint_8 esl_spimem_sectorErase (MQX_FILE_PTR                hDev,
                               const ESL_SPIMEM_TChipCfg * poCfg,
                               uint_32                     u32Addr,
                               _mqx_int                  * err);

/** Enables or disables the write operations on the opened memory.
 * @param [in]  hDev      Open device handle.
 * @param [in]  poCfg     Pointer to the chip config structure.
 * @param [in]  u8Enable  TRUE to enable the write operations, FALSE to disable
 *                        them.
 * @param [out] err       Error details will be stored here in case of failure.
 * @return                ESL_SPIMEM_OK on success, other on failure. */
uint_8 esl_spimem_setWriteLatch (MQX_FILE_PTR                hDev,
                                 const ESL_SPIMEM_TChipCfg * poCfg,
                                 uint_8                      u8Enable,
                                 _mqx_int                  * err);

/** Enables or disables the write protection on the whole chip.
 * @param [in]  hDev      Open device handle.
 * @param [in]  poCfg     Pointer to the chip config structure.
 * @param [in]  u8Status  Value to write to the status register. See status bits
 *                        mapping in your chip specific header file.
 * @param [out] err       Error details will be stored here in case of failure.
 * @return                ESL_SPIMEM_OK on success, other on failure. */
uint_8 esl_spimem_setProtection (MQX_FILE_PTR                hDev,
                                 const ESL_SPIMEM_TChipCfg * poCfg,
                                 uint_8                      u8Status,
                                 _mqx_int                  * err);

/** Reads the current state of the memory.
 * @param [in]  hDev      Open device handle.
 * @param [in]  poCfg     Pointer to the chip config structure.
 * @param [out] pu8State  Pointer to the variable where to store the state.
 * @param [out] err       Error details will be stored here in case of failure.
 * @return                ESL_SPIMEM_OK on success, other on failure. */
uint_8 esl_spimem_readState (MQX_FILE_PTR                hDev,
                             const ESL_SPIMEM_TChipCfg * poCfg,
                             uint_8                    * pu8State,
                             _mqx_int                  * err);

/** Writes 1 byte to the specific address.
 * @param [in]  hDev      Open device handle.
 * @param [in]  poCfg     Pointer to the chip config structure.
 * @param [in]  u32Addr   Address to the memory where to write.
 * @param [in]  ucData    Byte to write.
 * @param [out] err       Error details will be stored here in case of failure.
 * @return                ESL_SPIMEM_OK on success, other on failure. */
uint_8 esl_spimem_writeByte (MQX_FILE_PTR                hDev,
                             const ESL_SPIMEM_TChipCfg * poCfg,
                             uint_32                     u32Addr,
                             uchar                       ucData,
                             _mqx_int                  * err);

/** Reads 1 byte from the specific address.
 * @param [in]  hDev      Open device handle.
 * @param [in]  poCfg     Pointer to the chip config structure.
 * @param [in]  u32Addr   Address to the memory from where to read.
 * @param [out] pucData   Pointer to the variable where to store the read byte.
 * @param [out] err       Error details will be stored here in case of failure.
 * @return                ESL_SPIMEM_OK on success, other on failure. */
uint_8 esl_spimem_readByte (MQX_FILE_PTR                hDev,
                            const ESL_SPIMEM_TChipCfg * poCfg,
                            uint_32                     u32Addr,
                            uchar                     * pucData,
                            _mqx_int                  * err);

/** Writes data to the specific address.
 * @param [in]  hDev      Open device handle.
 * @param [in]  poCfg     Pointer to the chip config structure.
 * @param [in]  u32Addr   Address to the memory where to write.
 * @param [in]  u32Size   Number of bytes to write.
 * @param [in]  pucData   Pointer to the input data array.
 * @param [out] err       Error details will be stored here in case of failure.
 * @return                ESL_SPIMEM_OK on success, other on failure. */
uint_8 esl_spimem_writeData (MQX_FILE_PTR                hDev,
                             const ESL_SPIMEM_TChipCfg * poCfg,
                             uint_32                     u32Addr,
                             uint_32                     u32Size,
                             uchar                     * pucData,
                             _mqx_int                  * err);

/** Reads data from the specific address.
 * @param [in]  hDev      Open device handle.
 * @param [in]  poCfg     Pointer to the chip config structure.
 * @param [in]  u32Addr   Address to the memory from where to read.
 * @param [in]  u32Size   Number of bytes to read.
 * @param [out] pucData   Pointer to the output data array.
 * @param [out] err       Error details will be stored here in case of failure.
 * @return                ESL_SPIMEM_OK on success, other on failure. */
uint_8 esl_spimem_readData (MQX_FILE_PTR                hDev,
                            const ESL_SPIMEM_TChipCfg * poCfg,
                            uint_32                     u32Addr,
                            uint_32                     u32Size,
                            uchar                     * pucData,
                            _mqx_int                  * err);

/** Reads the opened memory ID.
 * @param [in]  hDev      Open device handle.
 * @param [in]  poCfg     Pointer to the chip config structure.
 * @param [out] pu32Id    Pointer to the variable where to store the ID.
 * @param [out] err       Error details will be stored here in case of failure.
 * @return                ESL_SPIMEM_OK on success, other on failure. */
uint_8 esl_spimem_readId (MQX_FILE_PTR                hDev,
                          const ESL_SPIMEM_TChipCfg * poCfg,
                          uint_32                   * pu32Id,
                          _mqx_int                  * err);

//******************************************************************************

#endif // ESL_SPIMEM_H_39502948593090293949502931
