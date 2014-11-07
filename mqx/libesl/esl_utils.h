/** ****************************************************************************
 *
 *  @file       esl_utils.h
 *  @brief      Common useful macros
 *
 *  Project independent, but module-wide macros can be defined here.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version   1.11 2014-02-13: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              ARRAY_SIZE defined.
 *
 *  @version   1.10 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              STRNCPY and SNPRINTF definitions fixed.
 *
 *  @version    1.9 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    1.8 2014-01-24: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              ascii2hex() added.
 *
 *  @version    1.7 2013-11-25: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              CEIL_DIV macro defined.
 *
 *  @version    1.6 2013-11-08: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              MIN and MAX macros defined.
 *
 *  @version    1.5 2013-11-01: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              (MQX ticks) <-> (ms) conversion macros added.
 *
 *  @version    1.4 2013-10-30: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              assert definition added.
 *
 *  @version    1.3 2013-03-25: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              memAlloc() added.
 *
 *  @version    1.2 2013-02-12: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              _io_u64toa added.
 *
 *  @version    1.1 2013-01-27: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              _io_atou64 added.
 *
 *  @version    1.0 2011-01-26: Petr Kubiznak <kubiznak.petr@elnico.cz>
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

#ifndef ESL_UTILS_H_32578469357471127235713971
#define ESL_UTILS_H_32578469357471127235713971

#include "esl_config.h"
#include <mqx.h>

//******************************************************************************

/** Safe "sprintf". Prints formatted text of restricted length to given buffer.
 * Terminates the buffer with '\0'.
 * @warning     This macro expands in two statements terminated by semicolons (;).
 * @param [out] dst Buffer to store text in.
 * @param [in]  len Length of the output buffer.
 * @param [in]  fmt Format string.
 * @param [in]  ... Variable number of arguments depending by the fmt.
 * @return      Returns the same values as snprintf(). */
#define SNPRINTF(dst, len, fmt, ...) \
          snprintf (dst, len, fmt , ##__VA_ARGS__); \
          if(len>0) *((dst)+(len)-1)='\0';

/** Safe "strcpy". Copies at most *len* chars from source buffer to target
 * buffer. Terminates the buffer with '\0'.
 * @warning     This macro expands in two statements terminated by semicolons (;).
 * @param [out] dst Target buffer.
 * @param [in]  src Source buffer.
 * @param [in]  len Length of the output buffer.
 * @return      Returns the same values as strncpy(). */
#define STRNCPY(dst, src, len) \
          strncpy (dst, src, len); \
          if(len>0) *((dst)+(len)-1)='\0';

//******************************************************************************

/** Special size for a member of a structure, which doesn't really exist. Often
 * with advantage used together with the offsetof macro.
 * Usage: ESL_SIZEOF (TDataType, m_member). */
#define ESL_SIZEOF(s,m)     ((size_t) sizeof(((s *)0)->m))

//******************************************************************************

/** Returns the smaller of two given values (preferably the first one). */
#define MIN(a, b)           ((b)<(a) ? (b) : (a))
/** Returns the bigger of two given values (preferably the first one). */
#define MAX(a, b)           ((b)>(a) ? (b) : (a))

/** Divides integer a by integer b with rounding the value up. */
#define CEIL_DIV(a, b)      (((a) + (b) - 1) / (b))

//******************************************************************************

/** Computes number of elements of a static array. */
#define ARRAY_SIZE(ar)      (sizeof(ar) / sizeof(*ar))

//******************************************************************************

/** Makes a string of the input macro value. */
#define MACRO_VALUE(X)       MACRO_NAME(X)

/** Makes a string of the input macro name. */
#define MACRO_NAME(X)        #X

//******************************************************************************

/** Glues two values together, expanding them if they are macros. */
#define PASTE( a, b)          PASTE_NOEXPAND( a, b)
/** Glues three values together, expanding them if they are macros. */
#define PASTE3( a, b, c)      PASTE( PASTE( a, b), c)

/** Glues two values together without expanding macros. */
#define PASTE_NOEXPAND( a, b) a##b

//******************************************************************************

/** Converts MQX tick time to milliseconds. One MQX tick is typically 5 ms. */
#define MQX_TICKS_TO_MSECS(ticks)   ((ticks) * BSP_ALARM_RESOLUTION)
/** Converts milliseconds to MQX ticks. One MQX tick is typically 5 ms. */
#define MSECS_TO_MQX_TICKS(msecs)   ((msecs) / BSP_ALARM_RESOLUTION)

//******************************************************************************

/** Simple assert implementation. Define NDEBUG to disable all the asserted code. */
#ifndef assert
# ifdef NDEBUG
#   define assert(expr)
# else // NDEBUG //
#   define assert(expr)     if(!(expr)) { printf("assertion violated!\n"); while(1) ; }
# endif // NDEBUG //
#endif // assert //

//******************************************************************************

/** String to uint_64 conversion function. Basically just an extension of
 * _io_atoi from fio.h.
 * @param[in]  *str  Pointer to the '\0' terminated string containing a 64-bit
 *                   variable.
 * @return           64-bit binary value corresponding to the input string. */
uint_64 _io_atou64 (const char *str);

/** uint_64 to string conversion function.
 * @param[out]	*dst	Destination address to store the result to.
 * @param[in]   val     Value to be converted.
 * @return              Number of characters written (without the '\0' character
 *                      even though the string is terminated). */
int _io_u64toa (char *dst, uint_64 val);

/** int_64 to string conversion function.
 * @param[out]  *dst    Destination address to store the result to.
 * @param[in]   val     Value to be converted.
 * @return              Number of characters written (without the '\0' character
 *                      even though the string is terminated). */
int _io_i64toa (char *dst, int_64 val);

/** Ascii to Hex conversion function.
 * @param[in]   c   ASCII character in <0..9,a..f,A..F>.
 * @return      Hexadecimal value represented by the character.
 *              0xFF in case of invalid input. */
uint_8 ascii2hex (char c);

/** Allocates memory in default or specified memory pool.
 * @param[in] pPoolId   Memory pool ID to allocate memory from. Use NULL
 *                      to allocate memory from the default memory pool.
 * @param[in] size      Requested size of memory to be allocated.
 * @return              Pointer to the allocated memory block or NULL on failure. */
pointer memAlloc(_mem_pool_id     pPoolId,
                 _mem_size        size);

//******************************************************************************
#endif /* ESL_UTILS_H_32578469357471127235713971 */
