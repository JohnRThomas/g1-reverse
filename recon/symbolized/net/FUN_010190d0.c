#include "g1_net_symbols.h"
/* net-core FUN_010190d0 @ 0x10190d0  (parity 300 trials PROVEN) */

extern void FUN_01022a50(unsigned char a);
extern void FUN_010208b0(void);
extern void FUN_0101fca8(void);

void FUN_010190d0(void)
{
    unsigned int base = ((uintptr_t)&g_sdc_conn_ctx) /*=0x21000f90*/;
    if (*(volatile unsigned char*)(base+0x69)==0 && *(volatile int*)(base+0x64)!=0) {
        FUN_01022a50(*(volatile unsigned char*)(base+0x68));
    }
    if (*(volatile unsigned char*)(base+0x7c)!=0) {
        FUN_010208b0();
        FUN_0101fca8();
        *(volatile unsigned char*)(base+0x7c)=0;
    }
    *(volatile unsigned short*)(base+0xba)=0;
    *(volatile unsigned char*)(base+0x70)=0;
    *(volatile unsigned char*)(((uintptr_t)&g_net_radio_pending_proc_flag) /*=0x2100104a*/+2)=0;
}

