#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102dea0 @ 0x0102dea0
 * public-name: FUN_0102dea0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103c900                           @ 0x0103c900
 *   g_net_periodic_work_obj                  @ 0x2100086c
 *   g_net_periodic_work_ptr                  @ 0x2100465c
 */
/* net-core FUN_0102dea0 @ 0x102dea0  (parity 300 trials PROVEN) */

extern void FUN_0102cbd8(unsigned int, unsigned int);
void FUN_0102dea0(void)
{
    unsigned int uVar1 = ((unsigned long)&g_net_periodic_work_obj) /*=0x2100086c*/;
    volatile unsigned int * const p = (volatile unsigned int * const)((unsigned long)&g_net_periodic_work_ptr) /*=0x2100465c*/;
    FUN_0102cbd8(uVar1, ((unsigned long)&rodata_103c900) /*=0x103c900*/);
    *p = uVar1;
}
