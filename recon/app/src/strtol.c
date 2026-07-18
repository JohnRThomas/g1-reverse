/* strtol @ 0x00077b24; raw FUN_00077b24 */
#include <stdint.h>

extern long FUN_00077a28(int *reent, const char *text, char **end, int base); /* _strtol_r */

long strtol(const char *text, char **end, int base)
{
    int *reent = *(int * volatile *)0x20002d20u;
    return FUN_00077a28(reent, text, end, base);
}
