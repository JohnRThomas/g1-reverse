#include "g1_net_symbols.h"
/* net-core FUN_01033bf0 @ 0x1033bf0  (parity 300 trials PROVEN) */

void FUN_01033bf0(unsigned int param_1, int param_2)
{
    volatile unsigned char *s54 = (volatile unsigned char*)((uintptr_t)&g_esb_ppi_ch_id_1) /*=0x2100645b*/;
    volatile unsigned char *s58 = (volatile unsigned char*)((uintptr_t)&g_154_dppi_channel_ack) /*=0x2100645c*/;
    volatile unsigned char *s68 = (volatile unsigned char*)((uintptr_t)&g_net_radio_trx_ppi_ch_a) /*=0x2100645a*/;
    volatile unsigned char *f000 = (volatile unsigned char*)REG_4100f000 /*=0x4100f000*/;
    volatile unsigned char *b8080 = (volatile unsigned char*)REG_41008080 /*=0x41008080*/;
    volatile unsigned char *b4000 = (volatile unsigned char*)REG_41014000 /*=0x41014000*/;
    volatile unsigned char *f080 = (volatile unsigned char*)REG_4100f080 /*=0x4100f080*/;
    volatile unsigned char *b9000 = (volatile unsigned char*)REG_41019000 /*=0x41019000*/;

    unsigned int mask = 1u << *s54;
    unsigned int combined = (1u << *s58) | mask;
    *(volatile unsigned int*)(f000 + 0x508) = combined;

    *(volatile unsigned int*)(b4000 + 0x198) = 0;
    *(volatile unsigned int*)(b4000 + 0x19c) = 0;
    *(volatile unsigned int*)(b4000 + 0x9c) = 0;

    unsigned int off0 = (param_1 << 2) & 0xff;
    *(volatile unsigned int*)(b8080 + off0) = 0;

    unsigned int v68 = *s68;
    unsigned int off1 = (v68 * 8 + 4) & 0xff;
    *(volatile unsigned int*)(f080 + off1) = 0;

    *(volatile unsigned int*)(b4000 + 0x98) = 0;

    volatile unsigned int *fptr = (volatile unsigned int*)(REG_4100f800 /*=0x4100f800*/ + v68 * 4);
    *fptr = *fptr & ~mask;

    if (param_2 != 0) {
        *(volatile unsigned int*)(b9000 + 0x80) = 0;
    }
}

