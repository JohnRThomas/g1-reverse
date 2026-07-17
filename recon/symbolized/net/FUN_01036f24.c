#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01036f24 @ 0x01036f24
 * public-name: FUN_01036f24
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_ctx_active_count                   @ 0x21004b64
 */
/* net-core FUN_01036f24 @ 0x1036f24  (parity 300 trials PROVEN) */

extern void FUN_010380d8(unsigned int a);
extern int FUN_01036e90(unsigned int a);
extern void FUN_01037f8c(unsigned int a, unsigned int b, int lo, int hi);

void FUN_01036f24(unsigned int param_1)
{
    unsigned char bVar1 = *(volatile unsigned char *)(0x21004b28 + 0x10);
    unsigned int iVar3 = (unsigned int)bVar1 * 0x18 + 0x210044d8;
    int iVar2;
    int v;
    FUN_010380d8(iVar3);
    *(volatile unsigned char *)(0x21006462 + bVar1) = 0;
    iVar2 = FUN_01036e90(param_1);
    if (iVar2 != 0) {
        v = *(volatile int *)((unsigned long)&g_net_ctx_active_count) /*=0x21004b64*/ - 1;
        FUN_01037f8c(iVar3, 0x010376cd, v, v >> 0x1f);
    }
}
