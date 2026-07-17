#include "g1_net_symbols.h"
/* net-core FUN_010350a4 @ 0x10350a4  (parity 300 trials PROVEN) */
typedef void (*fnptr_t)(unsigned short, unsigned int);

void FUN_010350a4(void)
{
    unsigned int uVar3, uVar6 = 0;

    for (uVar3 = 0x40; uVar3 != 0x60; uVar3 += 4) {
        volatile unsigned int *slot = (volatile unsigned int *)(0x41019100u + uVar3);
        if (*slot != 0) {
            *slot = 0;
            uVar6 = uVar6 | (1u << ((uVar3 >> 2) & 0xff));
        }
    }

    volatile unsigned int *puVar2 = (volatile unsigned int *)((unsigned long)&g_net_gpiote_evt_handler_table) /*=0x21004af8*/;
    unsigned int uVar7 = *(volatile unsigned int *)(0x41019000u + 0x304);

    for (uVar3 = 0x40; uVar3 != 0x60; uVar3 += 4) {
        unsigned int uVar4 = 1u << ((uVar3 >> 2) & 0xff);
        if ((uVar7 & 0xff0000u & uVar4) != 0 && (uVar4 & uVar6) != 0) {
            unsigned int fn = puVar2[0];
            if (fn != 0) {
                fnptr_t pcVar5 = (fnptr_t)fn;
                pcVar5((unsigned short)((uVar3 + 0x100) & 0xffff), puVar2[1]);
            }
        }
    }
}
