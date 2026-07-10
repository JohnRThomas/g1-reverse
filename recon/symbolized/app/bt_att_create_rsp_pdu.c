#include "g1_app_symbols.h"
/* named: bt_att_create_rsp_pdu */
/* Reconstructed bt_att_create_rsp_pdu @ 0x58f34  (parity: 300/300 trials, PROVEN) */

extern int bt_att_chan_create_pdu(void);
extern void FUN_00081ddc(int,int,void*);

int bt_att_create_rsp_pdu(int param_1, int param_2, int param_3, int param_4)
{
    unsigned int uStack_20 = param_3 + 1;
    unsigned short h2e = *(volatile unsigned short*)(param_1+0x2e);
    unsigned short h1e = *(volatile unsigned short*)(param_1+0x1e);
    unsigned int local_24 = h2e;
    if (h1e <= h2e) local_24 = h1e;
    if (local_24 < uStack_20) {
        struct { int f0; int f4; int f8; unsigned int fc; unsigned int f10; } s;
        s.f0 = 5;
        s.f4 = "ATT channel %p MTU too small for RSP (%u < %u)" /*=0xf4651*/;
        s.f8 = param_1;
        s.fc = local_24;
        s.f10 = uStack_20;
        FUN_00081ddc(((uintptr_t)&tbl_880d8) /*=0x88100*/, 0x2880, &s);
        return 0;
    } else {
        return bt_att_chan_create_pdu();
    }
}

