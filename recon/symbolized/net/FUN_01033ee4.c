#include "g1_net_symbols.h"
/* net-core FUN_01033ee4 @ 0x1033ee4  (parity 300 trials PROVEN) */

void FUN_01033ee4(void)
{
    unsigned int v;
    v = 1u << *(volatile unsigned char*)((unsigned long)&g_esb_ppi_ch_id_1) /*=0x2100645b*/;
    v |= 1u << *(volatile unsigned char*)((unsigned long)&g_esb_ppi_ch_id_5) /*=0x2100645f*/;
    v |= 1u << *(volatile unsigned char*)((unsigned long)&g_esb_ppi_ch_id_3) /*=0x2100645d*/;
    v |= 1u << *(volatile unsigned char*)((unsigned long)&g_154_dppi_channel_ack) /*=0x2100645c*/;
    v |= 1u << *(volatile unsigned char*)((unsigned long)&g_esb_ppi_ch_id_6) /*=0x21006460*/;
    v |= 1;
    *(volatile unsigned int*)(0x4100f000 + 0x508) = v;
}
