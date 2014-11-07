/** ****************************************************************************
 *
 *  @file       esl_spimem_m25p20.h
 *  @brief      SPI Flash M25P20 Constants
 *
 *  Constants of the M25P20 SPI flash used in the esl_spimem module.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Jan Kubiznak <kubiznak.jan@elnico.cz>
 *
 *  @version    1.2 2014-01-16: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Chip config global moved to the C file, so it
 *                              can be shared by ESL and application.
 *
 *  @version    1.1 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    1.0 2014-01-06: Jan Kubiznak <kubiznak.jan@elnico.cz>
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

#ifndef ESL_SPIMEM_M25P20_H_30390985290910923898530992
#define ESL_SPIMEM_M25P20_H_30390985290910923898530992

//******************************************************************************

/** @var const ESL_SPIMEM_TChipCfg esl_spimem_oM25P20
 * @brief M25P20 SPI Flash memory configuration for the esl_spimem module. */
extern const ESL_SPIMEM_TChipCfg esl_spimem_oM25P20;

//******************************************************************************
#endif // ESL_SPIMEM_M25P20_H_30390985290910923898530992
