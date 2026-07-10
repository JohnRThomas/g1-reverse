#include "g1_app_symbols.h"
/* named: msg_content_decrement_timer */
/* globals referenced:
//   0x20007dac  g_message_pool               
//   0x2001a22a  g_message_pool_index         
*/
/* Reconstructed msg_content_decrement_timer @ 0x3441c  (parity: 300/300 trials, PROVEN) */

void msg_content_decrement_timer(void)
{
    unsigned int idx = *(volatile unsigned char*)((uintptr_t)&g_message_pool_index) /*=0x2001a22a*/;
    unsigned int base = idx * 0x1b4 + (g_message_pool) /*=0x20007dac*/;
    int iVar1 = *(volatile int*)(base + 4);
    if (iVar1 != 0) {
        *(volatile int*)(base + 4) = iVar1 - 10;
    }
}

