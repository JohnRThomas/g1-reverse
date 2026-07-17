#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102ec10 @ 0x0102ec10
 * public-name: FUN_0102ec10
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103cb30                           @ 0x0103cb30
 */
/* net-core FUN_0102ec10 @ 0x102ec10  (parity 300 trials PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

#define BASE 0x21004b28u
#define LITP ((unsigned long)&rodata_103cb30) /*=0x103cb30*/
#define SCB  0xe000ed00u

unsigned int FUN_0102ec10(unsigned int param_1)
{
    unsigned int iVar4 = *(volatile unsigned int *)(BASE + 8);
    unsigned int uVar3 = *(volatile unsigned int *)LITP;

    *(volatile unsigned int *)(iVar4 + 0x8c) = param_1;
    *(volatile unsigned int *)(iVar4 + 0x90) = uVar3;
    *(volatile unsigned int *)(SCB + 4) = *(volatile unsigned int *)(SCB + 4) | 0x10000000;
    __set_BASEPRI(0);
    __ISB();
    return *(volatile unsigned int *)(*(volatile unsigned int *)(BASE + 8) + 0x90);
}
