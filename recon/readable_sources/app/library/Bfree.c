#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_dtoa_bigint__param_0424                [param_0424; library]
 * Raw function identity: 0x00078654.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00078654 @ 0x00078654
 * public-name: Bfree
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __assert_func                            <= FUN_00076a94 @ 0x00076a94
 *   malloc                                   <= FUN_00076d6c @ 0x00076d6c
 *   Bfree                                    <= FUN_00078654 @ 0x00078654
 * address symbols (name @ address):
 *   rodata_f8bb7                             @ 0x000f8bb7
 *   rodata_f8cd5                             @ 0x000f8cd5
 */
/* Reconstructed FUN_00078654 @ 0x78654  (parity: 300/300 trials, PROVEN) */

extern unsigned int *malloc(int size);
extern unsigned int *__assert_func(int a,int b,int c,int d);

void Bfree(int param_1, unsigned int *param_2)
{
  unsigned int *puVar1;
  int iVar2;

  if (*(volatile int *)(param_1 + 0x24) == 0) {
    puVar1 = malloc(0x10);
    *(volatile unsigned int *)(param_1 + 0x24) = (unsigned int)puVar1;
    if (puVar1 == 0) {
      puVar1 = __assert_func(((unsigned long)&rodata_f8cd5) /*=0xf8cd5*/, 0x8a, 0, ((unsigned long)&rodata_f8bb7) /*=0xf8bb7*/);
    }
    puVar1[1] = 0;
    puVar1[2] = 0;
    *puVar1 = 0;
    puVar1[3] = 0;
  }
  if (param_2 != 0) {
    iVar2 = *(int *)(*(int *)(param_1 + 0x24) + 0xc);
    *param_2 = *(unsigned int *)(iVar2 + param_2[1] * 4);
    *(unsigned int **)(iVar2 + param_2[1] * 4) = param_2;
  }
}
