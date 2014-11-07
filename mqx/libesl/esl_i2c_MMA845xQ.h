/** ****************************************************************************
 *
 *  @file       esl_i2c_MMA845xQ.h
 *  @brief      MMA845xQ accelerometers control.
 *
 *  Communication with the MMA8451Q, MMA8452Q and MMA8453Q accelerometers.
 *  These devices are almost the same, differing mainly in their data
 *  resolutions: 14, 12 and 10bit respectivelly.
 *
 *  User can use either the full module with its public interface,
 *  or just the register definitions manually.
 *
 *  @copyright  Petr Kubiznak. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.0 2014-09-16: Petr Kubiznak <kubiznak.petr@elnico.cz>
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

#ifndef ESL_I2C_MMA845XQ_H_78098410786934094827369882
#define ESL_I2C_MMA845XQ_H_78098410786934094827369882
//******************************************************************************

#include "esl_i2c_MMA845xQ_config.h"
#include "esl_i2c.h"

//******************************************************************************
// Main definitions
//******************************************************************************
/** I2C slave address.
 * @param[in] SA0   I2C least significant bit of the device address. */
#define ESL_I2C_MMA845XQ_SLAVE_ADDRESS(SA0)                 (0x1C | (((SA0)&0x1)<<0))

#define ESL_I2C_MMA845XQ_DEVICE_ID(x)                       ((x)*0x10 + 0x0A)
#define ESL_I2C_MMA8451Q_DEVICE_ID                          ESL_I2C_MMA845XQ_DEVICE_ID(1)                               //!< MMA8451Q Device ID (0x1A, see ESL_I2C_MMA845XQ_WHO_AM_I).
#define ESL_I2C_MMA8452Q_DEVICE_ID                          ESL_I2C_MMA845XQ_DEVICE_ID(2)                               //!< MMA8452Q Device ID (0x2A, see ESL_I2C_MMA845XQ_WHO_AM_I).
#define ESL_I2C_MMA8453Q_DEVICE_ID                          ESL_I2C_MMA845XQ_DEVICE_ID(3)                               //!< MMA8453Q Device ID (0x3A, see ESL_I2C_MMA845XQ_WHO_AM_I).

#define ESL_I2C_MMA845XQ_DEVICE_NUM(id)                     (((id)-0x0A) / 0x10)                                        //!< Retrieves the device number (1,2,3) out of the device identifier (0x1A,0x2A,0x3A).

/** MMA845XQ registers have 8-bit addresses (1 byte). */
#define ESL_I2C_MMA845XQ_REG_ADDR_SIZE                      (1)

//******************************************************************************
// Data conversions
//******************************************************************************
#define ESL_I2C_MMA845XQ_DATA_RESOLUTION(x)                 (16 - (x)*2)
#define ESL_I2C_MMA8451Q_DATA_RESOLUTION                    ESL_I2C_MMA845XQ_DATA_RESOLUTION(1)                         //!< MMA8451Q data resolution (14bit)
#define ESL_I2C_MMA8452Q_DATA_RESOLUTION                    ESL_I2C_MMA845XQ_DATA_RESOLUTION(2)                         //!< MMA8452Q data resolution (12bit)
#define ESL_I2C_MMA8453Q_DATA_RESOLUTION                    ESL_I2C_MMA845XQ_DATA_RESOLUTION(3)                         //!< MMA8453Q data resolution (10bit)

/** Converts raw data value (left-justified) to the type-specific (14/12/10bit) integer.
 * @param[in] raw   The raw (left-justified) data value.
 * @param[in] x     IC type specifier (1, 2 or 3 for MMA8451Q, MMA8452Q or MMA8453Q respectively). */
#define ESL_I2C_MMA845XQ_RAW2INT(raw,x)                     ((raw) >> (16 - ESL_I2C_MMA845XQ_DATA_RESOLUTION(x)))
/** Converts raw data value (left-justified) to the float value in multiples of gravity constant g.
 * @param[in] raw   The raw (left-justified) data value.
 * @param[in] scale Full scale - 2, 4 or 8 for 2g, 4g or 8g respectively. */
#define ESL_I2C_MMA845XQ_RAW2G(raw,scale)                   ((raw) / (ESL_I2C_MMA845XQ_RAW2G_DIVIDER(scale)))
#define ESL_I2C_MMA845XQ_RAW2G_DIVIDER(scale)               ((0x0001 << 14) / ((scale) >> 1))

//******************************************************************************
// Register addresses
//******************************************************************************
#define ESL_I2C_MMA845XQ_STATUS                             (0x00)                                                      //!< R  Realtime status. FMODE = 0.
#define ESL_I2C_MMA845XQ_F_STATUS                           (ESL_I2C_MMA845XQ_STATUS)                                   //!< R  FIFO status. FMODE > 0.
#define ESL_I2C_MMA845XQ_OUT_X_MSB                          (0x01)                                                      //!< R  X-axis data MSB (8 bits).
#define ESL_I2C_MMA845XQ_OUT_X_LSB                          (0x02)                                                      //!< R  X-axis data LSB (6/4/2 bits, padded by 0).
#define ESL_I2C_MMA845XQ_OUT_Y_MSB                          (0x03)                                                      //!< R  Y-axis data MSB (8 bits).
#define ESL_I2C_MMA845XQ_OUT_Y_LSB                          (0x04)                                                      //!< R  Y-axis data LSB (6/4/2 bits, padded by 0).
#define ESL_I2C_MMA845XQ_OUT_Z_MSB                          (0x05)                                                      //!< R  Z-axis data MSB (8 bits).
#define ESL_I2C_MMA845XQ_OUT_Z_LSB                          (0x06)                                                      //!< R  Z-axis data LSB (6/4/2 bits, padded by 0).
#define ESL_I2C_MMA845XQ_SYSMOD                             (0x0B)                                                      //!< R  Current system mode.
#define ESL_I2C_MMA845XQ_INT_SOURCE                         (0x0C)                                                      //!< R  Interrupt status.
#define ESL_I2C_MMA845XQ_WHO_AM_I                           (0x0D)                                                      //!< R  Device ID.
#define ESL_I2C_MMA845XQ_XYZ_DATA_CFG                       (0x0E)                                                      //!< RW Dynamic range settings.
#define ESL_I2C_MMA845XQ_HP_FILTER_CUTOFF                   (0x0F)                                                      //!< RW Cutoff frequency.
#define ESL_I2C_MMA845XQ_PL_STATUS                          (0x10)                                                      //!< R  Portrait/Landscape orientation status.
#define ESL_I2C_MMA845XQ_PL_CFG                             (0x11)                                                      //!< RW Portrait/Landscape orientation configuration.
#define ESL_I2C_MMA845XQ_FF_MT_CFG                          (0x15)                                                      //!< RW Freefall/Motion detect configuration.
#define ESL_I2C_MMA845XQ_FF_MT_SRC                          (0x16)                                                      //!< R  Freefall/Motion detect status.
#define ESL_I2C_MMA845XQ_CTRL_REG1                          (0x2A)                                                      //!< RW Control register 1 (data rate, active mode).
#define ESL_I2C_MMA845XQ_CTRL_REG2                          (0x2B)                                                      //!< RW Control register 2 (sleep enable, OS modes, RST, Self-test).
#define ESL_I2C_MMA845XQ_CTRL_REG3                          (0x2C)                                                      //!< RW Control register 3 (wake from Sleep, IPOL, PP_OD).
#define ESL_I2C_MMA845XQ_CTRL_REG4                          (0x2D)                                                      //!< RW Control register 4 (interrupt enable).
#define ESL_I2C_MMA845XQ_CTRL_REG5                          (0x2E)                                                      //!< RW Control register 5 (interrupt pin map).
#define ESL_I2C_MMA845XQ_OFF_X                              (0x2F)                                                      //!< RW X-axis offset status.
#define ESL_I2C_MMA845XQ_OFF_Y                              (0x30)                                                      //!< RW Y-axis offset status.
#define ESL_I2C_MMA845XQ_OFF_Z                              (0x31)                                                      //!< RW Z-axis offset status.

//******************************************************************************
// Register fields
//******************************************************************************
#define ESL_I2C_MMA845XQ_STATUS_ZYXOW_SHIFT                 (7)                                                         //!< X, Y, Z-axis Data Overwrite shift.
#define ESL_I2C_MMA845XQ_STATUS_ZYXOW_MASK                  (0x01 << ESL_I2C_MMA845XQ_STATUS_ZYXOW_SHIFT)               //!< X, Y, Z-axis Data Overwrite mask. 1: Previous data overwritten; 0: No overwrite.
#define ESL_I2C_MMA845XQ_STATUS_ZOW_SHIFT                   (6)                                                         //!< Z-axis Data Overwrite shift.
#define ESL_I2C_MMA845XQ_STATUS_ZOW_MASK                    (0x01 << ESL_I2C_MMA845XQ_STATUS_ZOW_SHIFT)                 //!< Z-axis Data Overwrite mask. 1: Previous data overwritten; 0: No overwrite.
#define ESL_I2C_MMA845XQ_STATUS_YOW_SHIFT                   (5)                                                         //!< Y-axis Data Overwrite shift.
#define ESL_I2C_MMA845XQ_STATUS_YOW_MASK                    (0x01 << ESL_I2C_MMA845XQ_STATUS_YOW_SHIFT)                 //!< Y-axis Data Overwrite mask. 1: Previous data overwritten; 0: No overwrite.
#define ESL_I2C_MMA845XQ_STATUS_XOW_SHIFT                   (4)                                                         //!< X-axis Data Overwrite shift.
#define ESL_I2C_MMA845XQ_STATUS_XOW_MASK                    (0x01 << ESL_I2C_MMA845XQ_STATUS_XOW_SHIFT)                 //!< X-axis Data Overwrite mask. 1: Previous data overwritten; 0: No overwrite.
#define ESL_I2C_MMA845XQ_STATUS_ZYXDR_SHIFT                 (3)                                                         //!< X, Y, Z-axis New Data Available shift.
#define ESL_I2C_MMA845XQ_STATUS_ZYXDR_MASK                  (0x01 << ESL_I2C_MMA845XQ_STATUS_ZYXDR_SHIFT)               //!< X, Y, Z-axis New Data Available mask. 1: New data available; 0: No data ready.
#define ESL_I2C_MMA845XQ_STATUS_ZDR_SHIFT                   (2)                                                         //!< Z-axis New Data Available shift.
#define ESL_I2C_MMA845XQ_STATUS_ZDR_MASK                    (0x01 << ESL_I2C_MMA845XQ_STATUS_ZDR_SHIFT)                 //!< Z-axis New Data Available mask. 1: New data available; 0: No data ready.
#define ESL_I2C_MMA845XQ_STATUS_YDR_SHIFT                   (1)                                                         //!< Y-axis New Data Available shift.
#define ESL_I2C_MMA845XQ_STATUS_YDR_MASK                    (0x01 << ESL_I2C_MMA845XQ_STATUS_YDR_SHIFT)                 //!< Y-axis New Data Available mask. 1: New data available; 0: No data ready.
#define ESL_I2C_MMA845XQ_STATUS_XDR_SHIFT                   (0)                                                         //!< X-axis New Data Available shift.
#define ESL_I2C_MMA845XQ_STATUS_XDR_MASK                    (0x01 << ESL_I2C_MMA845XQ_STATUS_XDR_SHIFT)                 //!< X-axis New Data Available mask. 1: New data available; 0: No data ready.

#define ESL_I2C_MMA845XQ_XYZ_DATA_CFG_HPF_OUT_SHIFT         (4)                                                         //!< High-pass filter shift.
#define ESL_I2C_MMA845XQ_XYZ_DATA_CFG_HPF_OUT_MASK          (0x01 << ESL_I2C_MMA845XQ_XYZ_DATA_CFG_HPF_OUT_SHIFT)       //!< High-pass filter mask. 1: Enabled; 0: Disabled.
#define ESL_I2C_MMA845XQ_XYZ_DATA_CFG_FS_SHIFT              (0)                                                         //!< Full scale format shift.
#define ESL_I2C_MMA845XQ_XYZ_DATA_CFG_FS_MASK               (0x03 << ESL_I2C_MMA845XQ_XYZ_DATA_CFG_FS_SHIFT)            //!< Full scale format mask.
#define ESL_I2C_MMA845XQ_XYZ_DATA_CFG_FS_VAL(val)           (((val) << ESL_I2C_MMA845XQ_XYZ_DATA_CFG_FS_SHIFT) & ESL_I2C_MMA845XQ_XYZ_DATA_CFG_FS_MASK)
#define ESL_I2C_MMA845XQ_XYZ_DATA_CFG_FS_VAL_2              (ESL_I2C_MMA845XQ_XYZ_DATA_CFG_FS_VAL(0))                   //!< Full scale format value: 2g.
#define ESL_I2C_MMA845XQ_XYZ_DATA_CFG_FS_VAL_4              (ESL_I2C_MMA845XQ_XYZ_DATA_CFG_FS_VAL(1))                   //!< Full scale format value: 4g.
#define ESL_I2C_MMA845XQ_XYZ_DATA_CFG_FS_VAL_8              (ESL_I2C_MMA845XQ_XYZ_DATA_CFG_FS_VAL(2))                   //!< Full scale format value: 8g.

#define ESL_I2C_MMA845XQ_PL_CFG_DBCNTM_SHIFT                (7)                                                         //!< Debounce counter mode shift.
#define ESL_I2C_MMA845XQ_PL_CFG_DBCNTM_MASK                 (0x01 << ESL_I2C_MMA845XQ_PL_CFG_DBCNTM_SHIFT)              //!< Debounce counter mode mask. 1: Clear counter; 0: Decrement debounce.
#define ESL_I2C_MMA845XQ_PL_CFG_PL_EN_SHIFT                 (6)                                                         //!< Portrait/Landscape Detection shift.
#define ESL_I2C_MMA845XQ_PL_CFG_PL_EN_MASK                  (0x01 << ESL_I2C_MMA845XQ_PL_CFG_PL_EN_SHIFT)               //!< Portrait/Landscape Detection mask. 1: Enabled; 0: Disabled.

#define ESL_I2C_MMA845XQ_CTRL_REG1_ASLP_RATE_SHIFT          (6)                                                         //!< Auto-SLEEP sample frequency shift.
#define ESL_I2C_MMA845XQ_CTRL_REG1_ASLP_RATE_MASK           (0x03 << ESL_I2C_MMA845XQ_CTRL_REG1_ASLP_RATE_SHIFT)        //!< Auto-SLEEP sample frequency mask.
#define ESL_I2C_MMA845XQ_CTRL_REG1_ASLP_RATE_VAL(val)       (((val) << ESL_I2C_MMA845XQ_CTRL_REG1_ASLP_RATE_SHIFT) & ESL_I2C_MMA845XQ_CTRL_REG1_ASLP_RATE_MASK)
#define ESL_I2C_MMA845XQ_CTRL_REG1_ASLP_RATE_VAL_50         (ESL_I2C_MMA845XQ_CTRL_REG1_ASLP_RATE_VAL(0))               //!< Auto-SLEEP sample frequency value: 50 Hz.
#define ESL_I2C_MMA845XQ_CTRL_REG1_ASLP_RATE_VAL_12_5       (ESL_I2C_MMA845XQ_CTRL_REG1_ASLP_RATE_VAL(1))               //!< Auto-SLEEP sample frequency value: 12.5 Hz.
#define ESL_I2C_MMA845XQ_CTRL_REG1_ASLP_RATE_VAL_6_25       (ESL_I2C_MMA845XQ_CTRL_REG1_ASLP_RATE_VAL(2))               //!< Auto-SLEEP sample frequency value: 6.25 Hz.
#define ESL_I2C_MMA845XQ_CTRL_REG1_ASLP_RATE_VAL_1_56       (ESL_I2C_MMA845XQ_CTRL_REG1_ASLP_RATE_VAL(3))               //!< Auto-SLEEP sample frequency value: 1.56 Hz.
#define ESL_I2C_MMA845XQ_CTRL_REG1_DR_SHIFT                 (3)                                                         //!< Data rate selection shift.
#define ESL_I2C_MMA845XQ_CTRL_REG1_DR_MASK                  (0x07 << ESL_I2C_MMA845XQ_CTRL_REG1_DR_SHIFT)               //!< Data rate selection mask.
#define ESL_I2C_MMA845XQ_CTRL_REG1_DR_VAL(val)              (((val) << ESL_I2C_MMA845XQ_CTRL_REG1_DR_SHIFT) & ESL_I2C_MMA845XQ_CTRL_REG1_DR_MASK)
#define ESL_I2C_MMA845XQ_CTRL_REG1_DR_VAL_800               (ESL_I2C_MMA845XQ_CTRL_REG1_DR_VAL(0))                      //!< Data rate selection value: 800 Hz.
#define ESL_I2C_MMA845XQ_CTRL_REG1_DR_VAL_400               (ESL_I2C_MMA845XQ_CTRL_REG1_DR_VAL(1))                      //!< Data rate selection value: 400 Hz.
#define ESL_I2C_MMA845XQ_CTRL_REG1_DR_VAL_200               (ESL_I2C_MMA845XQ_CTRL_REG1_DR_VAL(2))                      //!< Data rate selection value: 200 Hz.
#define ESL_I2C_MMA845XQ_CTRL_REG1_DR_VAL_100               (ESL_I2C_MMA845XQ_CTRL_REG1_DR_VAL(3))                      //!< Data rate selection value: 100 Hz.
#define ESL_I2C_MMA845XQ_CTRL_REG1_DR_VAL_50                (ESL_I2C_MMA845XQ_CTRL_REG1_DR_VAL(4))                      //!< Data rate selection value: 50 Hz.
#define ESL_I2C_MMA845XQ_CTRL_REG1_DR_VAL_12_5              (ESL_I2C_MMA845XQ_CTRL_REG1_DR_VAL(5))                      //!< Data rate selection value: 12.5 Hz.
#define ESL_I2C_MMA845XQ_CTRL_REG1_DR_VAL_6_25              (ESL_I2C_MMA845XQ_CTRL_REG1_DR_VAL(6))                      //!< Data rate selection value: 6.25 Hz.
#define ESL_I2C_MMA845XQ_CTRL_REG1_DR_VAL_1_56              (ESL_I2C_MMA845XQ_CTRL_REG1_DR_VAL(7))                      //!< Data rate selection value: 1.56 Hz.
#define ESL_I2C_MMA845XQ_CTRL_REG1_LNOISE_SHIFT             (2)                                                         //!< Reduced Noise mode shift.
#define ESL_I2C_MMA845XQ_CTRL_REG1_LNOISE_MASK              (0x01 << ESL_I2C_MMA845XQ_CTRL_REG1_LNOISE_SHIFT)           //!< Reduced Noise mode mask. 1: Reduced Noise mode; 0: Normal mode.
#define ESL_I2C_MMA845XQ_CTRL_REG1_F_READ_SHIFT             (1)                                                         //!< Fast Read mode shift.
#define ESL_I2C_MMA845XQ_CTRL_REG1_F_READ_MASK              (0x01 << ESL_I2C_MMA845XQ_CTRL_REG1_F_READ_SHIFT)           //!< Fast Read mode mask. 1: Fast Read mode; 0: Normal mode.
#define ESL_I2C_MMA845XQ_CTRL_REG1_ACTIVE_SHIFT             (0)                                                         //!< ACTIVE mode shift.
#define ESL_I2C_MMA845XQ_CTRL_REG1_ACTIVE_MASK              (0x01 << ESL_I2C_MMA845XQ_CTRL_REG1_ACTIVE_SHIFT)           //!< ACTIVE mode mask. 1: Active mode; 0: Standby mode.

#define ESL_I2C_MMA845XQ_CTRL_REG2_ST_SHIFT                 (7)                                                         //!< Self-Test Enable shift.
#define ESL_I2C_MMA845XQ_CTRL_REG2_ST_MASK                  (0x01 << ESL_I2C_MMA845XQ_CTRL_REG2_ST_SHIFT)               //!< Self-Test Enable mask. 1: Enabled; 0: Disabled.
#define ESL_I2C_MMA845XQ_CTRL_REG2_RST_SHIFT                (6)                                                         //!< Software Reset shift.
#define ESL_I2C_MMA845XQ_CTRL_REG2_RST_MASK                 (0x01 << ESL_I2C_MMA845XQ_CTRL_REG2_RST_SHIFT)              //!< Software Reset mask. 1: Reset; 0: No function.
#define ESL_I2C_MMA845XQ_CTRL_REG2_SMODS_SHIFT              (3)                                                         //!< SLEEP Mode Oversampling shift.
#define ESL_I2C_MMA845XQ_CTRL_REG2_SMODS_MASK               (0x03 << ESL_I2C_MMA845XQ_CTRL_REG2_SMODS_SHIFT)            //!< SLEEP Mode Oversampling mask.
#define ESL_I2C_MMA845XQ_CTRL_REG2_SMODS_VAL(val)           (((val) << ESL_I2C_MMA845XQ_CTRL_REG2_SMODS_SHIFT) & ESL_I2C_MMA845XQ_CTRL_REG2_SMODS_MASK)
#define ESL_I2C_MMA845XQ_CTRL_REG2_SMODS_VAL_NORMAL         (ESL_I2C_MMA845XQ_CTRL_REG2_SMODS_VAL(0))                   //!< SLEEP Mode Oversampling value: Normal.
#define ESL_I2C_MMA845XQ_CTRL_REG2_SMODS_VAL_LNLP           (ESL_I2C_MMA845XQ_CTRL_REG2_SMODS_VAL(1))                   //!< SLEEP Mode Oversampling value: Low Noise Low Power.
#define ESL_I2C_MMA845XQ_CTRL_REG2_SMODS_VAL_HI_RES         (ESL_I2C_MMA845XQ_CTRL_REG2_SMODS_VAL(2))                   //!< SLEEP Mode Oversampling value: High Resolution.
#define ESL_I2C_MMA845XQ_CTRL_REG2_SMODS_VAL_LP             (ESL_I2C_MMA845XQ_CTRL_REG2_SMODS_VAL(3))                   //!< SLEEP Mode Oversampling value: Low Power.
#define ESL_I2C_MMA845XQ_CTRL_REG2_SLPE_SHIFT               (2)                                                         //!< Auto-SLEEP Enable shift.
#define ESL_I2C_MMA845XQ_CTRL_REG2_SLPE_MASK                (0x01 << ESL_I2C_MMA845XQ_CTRL_REG2_SLPE_SHIFT)             //!< Auto-SLEEP Enable mask. 1: Enabled; 0: Disabled.
#define ESL_I2C_MMA845XQ_CTRL_REG2_MODS_SHIFT               (0)                                                         //!< ACTIVE Mode Oversampling shift.
#define ESL_I2C_MMA845XQ_CTRL_REG2_MODS_MASK                (0x03 << ESL_I2C_MMA845XQ_CTRL_REG2_MODS_SHIFT)             //!< ACTIVE Mode Oversampling mask.
#define ESL_I2C_MMA845XQ_CTRL_REG2_MODS_VAL(val)            (((val) << ESL_I2C_MMA845XQ_CTRL_REG2_MODS_SHIFT) & ESL_I2C_MMA845XQ_CTRL_REG2_MODS_MASK)
#define ESL_I2C_MMA845XQ_CTRL_REG2_MODS_VAL_NORMAL          (ESL_I2C_MMA845XQ_CTRL_REG2_MODS_VAL(0))                    //!< ACTIVE Mode Oversampling value: Normal.
#define ESL_I2C_MMA845XQ_CTRL_REG2_MODS_VAL_LNLP            (ESL_I2C_MMA845XQ_CTRL_REG2_MODS_VAL(1))                    //!< ACTIVE Mode Oversampling value: Low Noise Low Power.
#define ESL_I2C_MMA845XQ_CTRL_REG2_MODS_VAL_HI_RES          (ESL_I2C_MMA845XQ_CTRL_REG2_MODS_VAL(2))                    //!< ACTIVE Mode Oversampling value: High Resolution.
#define ESL_I2C_MMA845XQ_CTRL_REG2_MODS_VAL_LP              (ESL_I2C_MMA845XQ_CTRL_REG2_MODS_VAL(3))                    //!< ACTIVE Mode Oversampling value: Low Power.

#define ESL_I2C_MMA845XQ_CTRL_REG3_FIFO_GATE_SHIFT          (7)                                                         //!< FIFO Gate shift.
#define ESL_I2C_MMA845XQ_CTRL_REG3_FIFO_GATE_MASK           (0x01 << ESL_I2C_MMA845XQ_CTRL_REG3_FIFO_GATE_SHIFT)        //!< FIFO Gate mask. 1: Input buffer blocked; 0: FIFO gate bypassed.
#define ESL_I2C_MMA845XQ_CTRL_REG3_WAKE_TRANS_SHIFT         (6)                                                         //!< Transient function shift.
#define ESL_I2C_MMA845XQ_CTRL_REG3_WAKE_TRANS_MASK          (0x01 << ESL_I2C_MMA845XQ_CTRL_REG3_WAKE_TRANS_SHIFT)       //!< Transient function mask. 1: Can wake up system; 2: Bypassed in SLEEP mode.
#define ESL_I2C_MMA845XQ_CTRL_REG3_WAKE_LNDPRT_SHIFT        (5)                                                         //!< Orientation function shift.
#define ESL_I2C_MMA845XQ_CTRL_REG3_WAKE_LNDPRT_MASK         (0x01 << ESL_I2C_MMA845XQ_CTRL_REG3_WAKE_LNDPRT_SHIFT)      //!< Orientation function mask. 1: Can wake up system; 2: Bypassed in SLEEP mode.
#define ESL_I2C_MMA845XQ_CTRL_REG3_WAKE_PULSE_SHIFT         (4)                                                         //!< Pulse function shift.
#define ESL_I2C_MMA845XQ_CTRL_REG3_WAKE_PULSE_MASK          (0x01 << ESL_I2C_MMA845XQ_CTRL_REG3_WAKE_PULSE_SHIFT)       //!< Pulse function mask. 1: Can wake up system; 2: Bypassed in SLEEP mode.
#define ESL_I2C_MMA845XQ_CTRL_REG3_WAKE_FF_MT_SHIFT         (3)                                                         //!< Freefall/Motion function shift.
#define ESL_I2C_MMA845XQ_CTRL_REG3_WAKE_FF_MT_MASK          (0x01 << ESL_I2C_MMA845XQ_CTRL_REG3_WAKE_FF_MT_SHIFT)       //!< Freefall/Motion function mask. 1: Can wake up system; 2: Bypassed in SLEEP mode.
#define ESL_I2C_MMA845XQ_CTRL_REG3_IPOL_SHIFT               (1)                                                         //!< Interrupt polarity shift.
#define ESL_I2C_MMA845XQ_CTRL_REG3_IPOL_MASK                (0x01 << ESL_I2C_MMA845XQ_CTRL_REG3_IPOL_SHIFT)             //!< Interrupt polarity mask. 1: Active high; 0: Active low.
#define ESL_I2C_MMA845XQ_CTRL_REG3_PP_OD_SHIFT              (0)                                                         //!< Push-Pull/Open Drain selection shift.
#define ESL_I2C_MMA845XQ_CTRL_REG3_PP_OD_MASK               (0x01 << ESL_I2C_MMA845XQ_CTRL_REG3_PP_OD_SHIFT)            //!< Push-Pull/Open Drain selection mask. 1: Open Drain; 0: Push-Pull.

#define ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_ASLP_SHIFT        (7)                                                         //!< Auto-SLEEP/WAKE Interrupt Enable shift.
#define ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_ASLP_MASK         (0x01 << ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_ASLP_SHIFT)      //!< Auto-SLEEP/WAKE Interrupt Enable mask. 1: Enabled; 0: Disabled.
#define ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_FIFO_SHIFT        (6)                                                         //!< FIFO Interrupt Enable shift.
#define ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_FIFO_MASK         (0x01 << ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_FIFO_SHIFT)      //!< FIFO Interrupt Enable mask. 1: Enabled; 0: Disabled.
#define ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_TRANS_SHIFT       (5)                                                         //!< Transient Interrupt Enable shift.
#define ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_TRANS_MASK        (0x01 << ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_TRANS_SHIFT)     //!< Transient Interrupt Enable mask. 1: Enabled; 0: Disabled.
#define ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_LNDPR_SHIFT       (4)                                                         //!< Orientation Interrupt Enable shift.
#define ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_LNDPR_MASK        (0x01 << ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_LNDPR_SHIFT)     //!< Orientation Interrupt Enable mask. 1: Enabled; 0: Disabled.
#define ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_PULSE_SHIFT       (3)                                                         //!< Pulse Interrupt Enable shift.
#define ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_PULSE_MASK        (0x01 << ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_PULSE_SHIFT)     //!< Pulse Interrupt Enable mask. 1: Enabled; 0: Disabled.
#define ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_FF_MT_SHIFT       (2)                                                         //!< Freefall/Motion Interrupt Enable shift.
#define ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_FF_MT_MASK        (0x01 << ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_FF_MT_SHIFT)     //!< Freefall/Motion Interrupt Enable mask. 1: Enabled; 0: Disabled.
#define ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_DRDY_SHIFT        (0)                                                         //!< Data Ready Interrupt Enable shift.
#define ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_DRDY_MASK         (0x01 << ESL_I2C_MMA845XQ_CTRL_REG4_INT_EN_DRDY_SHIFT)      //!< Data Ready Interrupt Enable mask. 1: Enabled; 0: Disabled.

#define ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_ASLP_SHIFT       (7)                                                         //!< Auto-SLEEP/WAKE Interrupt Configuration shift.
#define ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_ASLP_MASK        (0x01 << ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_ASLP_SHIFT)     //!< Auto-SLEEP/WAKE Interrupt Configuration mask. 1: INT1; 0: INT2.
#define ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_FIFO_SHIFT       (6)                                                         //!< FIFO Interrupt Configuration shift.
#define ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_FIFO_MASK        (0x01 << ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_FIFO_SHIFT)     //!< FIFO Interrupt Configuration mask. 1: INT1; 0: INT2.
#define ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_TRANS_SHIFT      (5)                                                         //!< Transient Interrupt Configuration shift.
#define ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_TRANS_MASK       (0x01 << ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_TRANS_SHIFT)    //!< Transient Interrupt Configuration mask. 1: INT1; 0: INT2.
#define ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_LNDPR_SHIFT      (4)                                                         //!< Orientation Interrupt Configuration shift.
#define ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_LNDPR_MASK       (0x01 << ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_LNDPR_SHIFT)    //!< Orientation Interrupt Configuration mask. 1: INT1; 0: INT2.
#define ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_PULSE_SHIFT      (3)                                                         //!< Pulse Interrupt Configuration shift.
#define ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_PULSE_MASK       (0x01 << ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_PULSE_SHIFT)    //!< Pulse Interrupt Configuration mask. 1: INT1; 0: INT2.
#define ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_FF_MT_SHIFT      (2)                                                         //!< Freefall/Motion Interrupt Configuration shift.
#define ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_FF_MT_MASK       (0x01 << ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_FF_MT_SHIFT)    //!< Freefall/Motion Interrupt Configuration mask. 1: INT1; 0: INT2.
#define ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_DRDY_SHIFT       (0)                                                         //!< Data Ready Interrupt Configuration shift.
#define ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_DRDY_MASK        (0x01 << ESL_I2C_MMA845XQ_CTRL_REG5_INT_CFG_DRDY_SHIFT)     //!< Data Ready Interrupt Configuration mask. 1: INT1; 0: INT2.

//******************************************************************************
// Public types
//******************************************************************************
/** MMA845xQ I2C accelerometer device configuration. This can be retrieved by
 *  esl_i2c_MMA845xQ_getDefaultConfig() (default configuration) or
 *  esl_i2c_MMA845xQ_getConfig() (current configuration). User can modify it
 *  manually and then call esl_i2c_MMA845xQ_open() or
 *  esl_i2c_MMA845xQ_configure() to apply custom configuration. Please note
 *  the ACTIVE bit of u8CtrlReg1 and RST bit of u8CtrlReg2 are ignored.
 *  Instead, use dedicated functions to activate or reset the device. */
typedef struct esl_i2c_mma845xq_config_struct {
  uint_32             u32WaitTicks;                                             //!< Maximum number of ticks to wait for I2C bus access. Use 0 for infinite wait.
  uint_8              u8XyzDataCfg;                                             //!< XYZ_DATA_CFG register configuration.
  uint_8              u8PlCfg;                                                  //!< PL_CFG register configuration.
  uint_8              u8CtrlReg1;                                               //!< CTRL_REG1 register configuration. Value of ACTIVE bit is ignored.
  uint_8              u8CtrlReg2;                                               //!< CTRL_REG2 register configuration. Value of RST bit is ignored.
  uint_8              u8CtrlReg3;                                               //!< CTRL_REG3 register configuration.
  uint_8              u8CtrlReg4;                                               //!< CTRL_REG4 register configuration.
  uint_8              u8CtrlReg5;                                               //!< CTRL_REG5 register configuration.
} ESL_I2C_MMA845XQ_TConfig;

/** MMA845xQ I2C accelerometer device object structure. Do not edit manually! */
typedef struct esl_i2c_mma845xq_device_struct {
  ESL_I2C_TDevice             hI2CDevice;                                       //!< General I2C device handle.
  ESL_I2C_MMA845XQ_TConfig    oConfig;                                          //!< Device configuration.
  uint_8                      u8DeviceId;                                       //!< Device ID (value of ESL_I2C_MMA845XQ_WHO_AM_I).
} ESL_I2C_MMA845XQ_TDevice;

//******************************************************************************
// Return values
//******************************************************************************
enum {
  ESL_I2C_MMA845XQ_DATA_NOT_READY = ESL_I2C_MODULE_OFF + 1,
  ESL_I2C_MMA845XQ_INVALID_STATE,
  ESL_I2C_MMA845XQ_MODULE_OFF,
};

//******************************************************************************
// Public functions
//******************************************************************************

/** Opens and resets the I2C accelerometer device and sets its configuration,
 *  leaving it in the STANDBY mode. Use esl_i2c_MMA845xQ_activate() to activate.
 * @param[out]  hAccelDevice    Accelerometer device handle will be stored here.
 * @param[in]   u8ChannelNo     Channel number - ESL_I2C0_NO to ESL_I2C3_NO.
 * @param[in]   u8DriverMode    Required driver mode - ESL_I2C_DRIVERMODE_INT
 *                              or ESL_I2C_DRIVERMODE_POLLED.
 * @param[in]   u32BaudRate     Required channel baud rate.
 * @param[in]   u8SA0           The least significant bit of the device address,
 *                              configurable by the SA0 hardware pin.
 * @param[in]   poConfig        Accelerometer configuration. Retrieve the default
 *                              settings by esl_i2c_MMA845xQ_getDefaultConfig()
 *                              and modify it to your needs. Use NULL to apply
 *                              the default configuration directly.
 * @return      ESL_I2C_OK on success.
 *              ESL_I2C_INVALID_ARGUMENT if hAccelDevice is NULL or another
 *              argument has invalid value (see esl_i2c_open()).
 *              Any I2C bus communication error. */
uint_8 esl_i2c_MMA845xQ_open (ESL_I2C_MMA845XQ_TDevice        * hAccelDevice,
                              uint_8                            u8ChannelNo,
                              uint_8                            u8DriverMode,
                              uint_32                           u32BaudRate,
                              uint_8                            u8SA0,
                              const ESL_I2C_MMA845XQ_TConfig  * poConfig);
/** Closes the I2C accelerometer device and the I2C channel if not used any more.
 * @param[in]   hAccelDevice    Accelerometer device handle will be stored here.
 *                              After this call, the handle becomes invalid.
 * @return      ESL_I2C_OK on success.
 *              ESL_I2C_INVALID_ARGUMENT if invalid handle given.
 *              Any I2C bus communication error. */
uint_8 esl_i2c_MMA845xQ_close (ESL_I2C_MMA845XQ_TDevice * hAccelDevice);

/** Retrieves the default accelerometer configuration.
 * @param[out]  poConfig  Structure to be filled in by the default values.
 * @return      ESL_I2C_OK on success.
 *              ESL_I2C_INVALID_ARGUMENT if NULL given. */
uint_8 esl_i2c_MMA845xQ_getDefaultConfig (ESL_I2C_MMA845XQ_TConfig * poConfig);
/** Retrieves given accelerometer configuration.
 * @param[out]  poConfig      Structure to be filled in by the device
 *                            configuration. Please note the ACTIVE bit
 *                            of the u8CtrlReg1 is always set 0.
 * @param[in]   hAccelDevice  Opened accelerometer device handle.
 * @return      ESL_I2C_OK on success.
 *              ESL_I2C_INVALID_ARGUMENT if NULL or invalid handle given. */
uint_8 esl_i2c_MMA845xQ_getConfig (ESL_I2C_MMA845XQ_TConfig       * poConfig,
                                   const ESL_I2C_MMA845XQ_TDevice * hAccelDevice);
/** Reconfigures the accelerometer according to given configuration structure.
 *  It is called automatically during esl_i2c_MMA845xQ_open().
 * @param[in]   hAccelDevice  Opened accelerometer device handle.
 * @param[in]   poConfig      Configuration structure pointer. This can be
 *                            retrieved by esl_i2c_MMA845xQ_getDefaultConfig()
 *                            or esl_i2c_MMA845xQ_getConfig() and manually
 *                            edited. Please note the ACTIVE bit of u8CtrlReg1
 *                            field is ignored, use esl_i2c_MMA845xQ_activate()
 *                            or esl_i2c_MMA845xQ_standby() instead. Also RST
 *                            bit of u8CtrlReg2 is ignored,
 *                            use esl_i2c_MMA845xQ_reset() instead.
 * @return      ESL_I2C_OK on success.
 *              ESL_I2C_INVALID_ARGUMENT if invalid handle given.
 *              Any I2C bus communication error. */
uint_8 esl_i2c_MMA845xQ_configure (ESL_I2C_MMA845XQ_TDevice       * hAccelDevice,
                                   const ESL_I2C_MMA845XQ_TConfig * poConfig);

/** Changes the accelerometer mode from STANDBY to ACTIVE.
 * @param[in]   hAccelDevice  Opened accelerometer device handle.
 * @return      ESL_I2C_OK on success.
 *              ESL_I2C_INVALID_ARGUMENT if invalid handle given.
 *              Any I2C bus communication error. */
uint_8 esl_i2c_MMA845xQ_activate (ESL_I2C_MMA845XQ_TDevice * hAccelDevice);
/** Changes the accelerometer mode from ACTIVE to STANDBY.
 * @param[in]   hAccelDevice  Opened accelerometer device handle.
 * @return      ESL_I2C_OK on success.
 *              ESL_I2C_INVALID_ARGUMENT if invalid handle given.
 *              Any I2C bus communication error. */
uint_8 esl_i2c_MMA845xQ_standby (ESL_I2C_MMA845XQ_TDevice * hAccelDevice);
/** Resets the accelerometer (leaving the default configuration).
 * @param[in]   hAccelDevice  Opened accelerometer device handle.
 * @return      ESL_I2C_OK on success.
 *              ESL_I2C_INVALID_ARGUMENT if invalid handle given.
 *              Any I2C bus communication error. */
uint_8 esl_i2c_MMA845xQ_reset (ESL_I2C_MMA845XQ_TDevice * hAccelDevice);

/** Retrieves the device ID, i.e. content of ESL_I2C_MMA845XQ_WHO_AM_I.
 * @param[out]  pu8DeviceId   Device ID will be stored here. Compare with
 *                            ESL_I2C_MMA8451Q_DEVICE_ID,
 *                            ESL_I2C_MMA8452Q_DEVICE_ID and
 *                            ESL_I2C_MMA8453Q_DEVICE_ID.
 * @param[in]   hAccelDevice  Opened accelerometer device handle.
 * @return      ESL_I2C_OK on success.
 *              ESL_I2C_INVALID_ARGUMENT if invalid handle or NULL given. */
uint_8 esl_i2c_MMA845xQ_getDeviceId (uint_8                   * pu8DeviceId,
                                     ESL_I2C_MMA845XQ_TDevice * hAccelDevice);
/** Reads the data registers and retrieves 16bit data.
 * @param[out]  pi16Data      Pointer to array of int_16 counting 3 elements
 *                            in X, Y, Z order. The values are left-justified.
 * @param[in]   hAccelDevice  Opened accelerometer device handle.
 * @return      ESL_I2C_OK on success.
 *              ESL_I2C_INVALID_ARGUMENT if NULL or invalid handle given.
 *              ESL_I2C_MMA845XQ_DATA_NOT_READY if no new data is ready.
 *              Any I2C bus communication error. */
uint_8 esl_i2c_MMA845xQ_getRawData (int_16                    * pi16Data,
                                    ESL_I2C_MMA845XQ_TDevice  * hAccelDevice);
/** Converts raw data to the type-specific integer value.
 * @param[out]  pi16IntData   Pointer to array of int_16 counting 3 elements
 *                            in X, Y, Z order. The values are 14bit, 12bit,
 *                            10bit or 8bit wide, depending on the actual
 *                            accelerometer type and configuration.
 *                            This pointer can be the same as pi16RawData.
 * @param[in]   pi16RawData   Pointer to array of int_16 counting 3 elements
 *                            in X, Y, Z order. The values are left-justified,
 *                            as retrieved by esl_i2c_MMA845xQ_getRawData().
 * @param[in]   hAccelDevice  Opened accelerometer device handle.
 * @return      ESL_I2C_OK on success.
 *              ESL_I2C_INVALID_ARGUMENT if NULL or invalid handle given. */
uint_8 esl_i2c_MMA845xQ_raw2int (int_16                     * pi16IntData,
                                 const int_16               * pi16RawData,
                                 ESL_I2C_MMA845XQ_TDevice   * hAccelDevice);
/** Converts raw data to physical acceleration (g-force).
 * @param[out]  pfGData       Pointer to array of float counting 3 elements
 *                            in X, Y, Z order. The values are in g-force.
 * @param[in]   pi16RawData   Pointer to array of int_16 counting 3 elements
 *                            in X, Y, Z order. The values are left-justified,
 *                            as retrieved by esl_i2c_MMA845xQ_getRawData().
 * @param[in]   hAccelDevice  Opened accelerometer device handle.
 * @return      ESL_I2C_OK on success.
 *              ESL_I2C_INVALID_ARGUMENT if NULL or invalid handle given.
 *              ESL_I2C_MMA845XQ_INVALID_STATE if the internal object state
 *               is invalid. */
uint_8 esl_i2c_MMA845xQ_raw2g (float                      * pfGData,
                               const int_16               * pi16RawData,
                               ESL_I2C_MMA845XQ_TDevice   * hAccelDevice);

//******************************************************************************
#endif // ESL_I2C_MMA845XQ_H_78098410786934094827369882 //
