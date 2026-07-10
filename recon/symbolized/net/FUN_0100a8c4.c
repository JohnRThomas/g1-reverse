#include "g1_net_symbols.h"
/* net-core FUN_0100a8c4 @ 0x100a8c4  (parity 300 trials PROVEN) */

#define DAT_0100a8d8 ((unsigned int)((uintptr_t)&g_net_ctrl_pending_req) /*=0x21000bf8*/)

void FUN_0100a8c4(void)
{
    unsigned int iVar1 = DAT_0100a8d8;
    *(volatile unsigned short *)(DAT_0100a8d8 + 0x34) = 0xffff;
    *(volatile unsigned short *)(iVar1 + 0x36) = 0xffff;
    *(volatile unsigned char *)(iVar1 + 0x32) = 0;
    *(volatile unsigned short *)(iVar1 + 0x38) = 0xffff;
    return;
}

