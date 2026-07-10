#include "g1_app_symbols.h"
/* named: rpmsg_send_ns_message */
/* Reconstructed rpmsg_send_ns_message @ 0x85898  (parity: 300/300 trials, PROVEN) */

extern void strncpy_zero_pad(void*, int, int);
extern unsigned int rpmsg_send_offchannel_nocopy(int, unsigned int, int, void*, int, int);

unsigned int rpmsg_send_ns_message(int param_1, unsigned int param_2)
{
    unsigned int uVar2 = *(volatile unsigned int*)(param_1 + 0x24);
    unsigned char buf[32];
    volatile unsigned int local_18;
    volatile unsigned int local_14;
    local_18 = uVar2;
    local_14 = param_2;
    strncpy_zero_pad(buf, param_1, 0x20);
    unsigned int uVar1 = rpmsg_send_offchannel_nocopy(param_1, uVar2, 0x35, buf, 0x28, 1);
    return uVar1 & ((int)uVar1 >> 31);
}

