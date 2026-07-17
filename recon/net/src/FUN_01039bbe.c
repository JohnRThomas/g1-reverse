/* net-core assert_print @ 0x01039bbe
 * Raw/address back-map: FUN_01039bbe / 0x01039bbe.
 */
#include <stdarg.h>
extern void thunk_FUN_0103a2a6(const char *fmt, va_list ap);
void assert_print(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    thunk_FUN_0103a2a6(fmt, ap);
    va_end(ap);
}
