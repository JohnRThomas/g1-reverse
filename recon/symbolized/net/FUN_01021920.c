#include "g1_net_symbols.h"
/* net-core FUN_01021920 @ 0x1021920  (parity 300 trials PROVEN) */

typedef void (*code)(void);
void FUN_01021920(void)
{
    ((code)(*(volatile unsigned int*)(*(volatile unsigned int*)((uintptr_t)&g_net_radio_ops_table_ptr) /*=0x21000530*/ + 4)))();
}

