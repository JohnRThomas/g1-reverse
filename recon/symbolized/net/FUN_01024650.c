#include "g1_net_symbols.h"
/* net-core FUN_01024650 @ 0x1024650  (parity 300 trials PROVEN) */

#include <stdbool.h>
bool FUN_01024650(void)
{
    volatile unsigned char * const p = (volatile unsigned char * const)((uintptr_t)&g_net_link_state) /*=0x21001bcc*/;
    return (unsigned char)(*p - 2) < 2;
}

