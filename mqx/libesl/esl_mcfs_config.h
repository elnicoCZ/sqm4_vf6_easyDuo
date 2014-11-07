/** ****************************************************************************
 *
 *  @file       esl_mcfs_config.h
 *  @brief      MCC filesystem config file
 *
 *  Default configuration of the MCFS module. In MQX, the settings should not
 *  be changed here but can be overridden in a project specific esl_config.h.
 *  In Linux, this file can be modified directly.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    2.0 2014-01-30: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Initial revision for esl_mcfs v2.0.
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

#ifndef ESL_MCFS_CONFIG_H_98147123854609878625070456
#define ESL_MCFS_CONFIG_H_98147123854609878625070456
//******************************************************************************

#if !__linux__
# include "esl_config.h"
#endif

//******************************************************************************
// Main module settings
//******************************************************************************

/** @def ESL_MCFS_MODULE_ENABLE
 * @brief Set 1/0 to get module enabled or disabled. */
#ifndef ESL_MCFS_MODULE_ENABLE
# define ESL_MCFS_MODULE_ENABLE         (0)
#endif

/** @def ESL_MCFS_DRIVE_ID_MAXLEN
 * @brief Maximum length of drive identifier (local/remote),
 *        e.g. "mcfs:", "\\root\\". */
#ifndef ESL_MCFS_DRIVE_ID_MAXLEN
# define ESL_MCFS_DRIVE_ID_MAXLEN       (20)
#endif

/** @def ESL_MCFS_FILENAME_MAXLEN
 * @brief Maximum length of a filename including the drive identifier. */
#ifndef ESL_MCFS_FILENAME_MAXLEN
# define ESL_MCFS_FILENAME_MAXLEN       (256 + (ESL_MCFS_DRIVE_ID_MAXLEN))
#endif

//******************************************************************************
// Endpoints settings
//******************************************************************************

/** @def ESL_MCFS_ENDPOINT_A5_CORE
 * @brief A5 core ID. For Vybrid, this should not be changed. */
#ifndef ESL_MCFS_ENDPOINT_A5_CORE
# define ESL_MCFS_ENDPOINT_A5_CORE      (0)
#endif
/** @def ESL_MCFS_ENDPOINT_A5_NODE
 * @brief A5 node ID. Task-specific in Linux, system-specific in MQX. */
#ifndef ESL_MCFS_ENDPOINT_A5_NODE
# define ESL_MCFS_ENDPOINT_A5_NODE      (0)
#endif
/** @def ESL_MCFS_ENDPOINT_A5_PORT
 * @brief A5 port ID. Arbitrary number except of MCC_RESERVED_PORT_NUMBER. */
#ifndef ESL_MCFS_ENDPOINT_A5_PORT
# define ESL_MCFS_ENDPOINT_A5_PORT      (1)
#endif

/** @def ESL_MCFS_ENDPOINT_M4_CORE
 * @brief M4 core ID. For Vybrid, this should not be changed. */
#ifndef ESL_MCFS_ENDPOINT_M4_CORE
# define ESL_MCFS_ENDPOINT_M4_CORE      (1)
#endif
/** @def ESL_MCFS_ENDPOINT_M4_NODE
 * @brief M4 node ID. Task-specific in Linux, system-specific in MQX. */
#ifndef ESL_MCFS_ENDPOINT_M4_NODE
# define ESL_MCFS_ENDPOINT_M4_NODE      (0)
#endif
/** @def ESL_MCFS_ENDPOINT_M4_PORT
 * @brief M4 port ID. Arbitrary number except of MCC_RESERVED_PORT_NUMBER. */
#ifndef ESL_MCFS_ENDPOINT_M4_PORT
# define ESL_MCFS_ENDPOINT_M4_PORT      (2)
#endif

//******************************************************************************
#endif // ESL_MCFS_CONFIG_H_98147123854609878625070456 //
