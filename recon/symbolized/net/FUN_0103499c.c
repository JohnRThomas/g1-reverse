#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103499c @ 0x0103499c
 * public-name: FUN_0103499c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_sdc_res_pool_slot_tbl                  @ 0x210006a8
 */
/* net-core FUN_0103499c @ 0x103499c  (parity 300 trials PROVEN) */

extern void FUN_0103b62e(void*, int, int);
extern unsigned int FUN_01034650(unsigned int);
extern void FUN_0102eb2c(int);

unsigned int FUN_0103499c(void)
{
    volatile unsigned char *base = (volatile unsigned char*)((unsigned long)&g_sdc_res_pool_slot_tbl) /*=0x210006a8*/;
    if (base[0x78] != 0) {
        return 0x0bad0005;
    }
    FUN_0103b62e((void*)(base + 0x10), 0, 0x60);
    unsigned int uVar4;
    for (uVar4 = 0; uVar4 != 8; uVar4++) {
        unsigned int r0 = FUN_01034650(uVar4 & 0xff);
        if (((r0 - 0x100u) >> 2) == 0x1f) {
            *(volatile unsigned int*)(r0 + 0x4100a000) = 0;
        }
    }
    volatile unsigned char *e4 = (volatile unsigned char*)0x4100a000;
    *(volatile unsigned int*)(e4 + 0x17c) = 0;
    FUN_0102eb2c(10);
    *(volatile unsigned int*)(e4 + 0x304) = 0x80000000;
    base[0x78] = 1;
    *(volatile unsigned int*)(base + 0x74) = 1;
    return 0x0bad0000;
}
