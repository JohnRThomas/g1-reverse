#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007893c @ 0x0007893c
 * public-name: pow5mult
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __assert_func                            <= FUN_00076a94 @ 0x00076a94
 *   malloc                                   <= FUN_00076d6c @ 0x00076d6c
 *   Bfree                                    <= FUN_00078654 @ 0x00078654
 *   multadd                                  <= FUN_00078698 @ 0x00078698
 *   i2b                                      <= FUN_000787bc @ 0x000787bc
 *   bigint_mult                              <= FUN_000787e8 @ 0x000787e8
 *   pow5mult                                 <= FUN_0007893c @ 0x0007893c
 * address symbols (name @ address):
 *   rodata_98774                             @ 0x00098774
 *   rodata_f8bb7                             @ 0x000f8bb7
 *   rodata_f8cd5                             @ 0x000f8cd5
 */
/* Reconstructed FUN_0007893c @ 0x7893c  (parity: 134/300 trials, PROVEN) */

#include <stdint.h>
typedef unsigned int uint;
extern uint32_t __assert_func(uint32_t,int,int,uint32_t);
extern uint32_t malloc(int);
extern void Bfree(int,uint32_t);
extern uint32_t multadd(int,uint32_t,uint32_t,int,uint32_t);
extern uint32_t i2b(int,int);
extern uint32_t bigint_mult(int,uint32_t,uint32_t);

uint32_t pow5mult(int param_1, uint32_t param_2, uint param_3, uint32_t param_4){
  uint32_t *puVar1, *puVar2;
  int iVar3, iVar5;
  uint32_t uVar4;
  if ((param_3 & 3) != 0){
    param_2 = multadd(param_1, param_2, *(uint32_t*)(((unsigned long)&rodata_98774) /*=0x98774*/ + ((param_3&3)-1)*4), 0, param_4);
  }
  iVar3 = (int)param_3 >> 2;
  if (iVar3 != 0){
    if (*(int*)(param_1+0x24) == 0){
      puVar1 = (uint32_t*)malloc(0x10);
      *(uint32_t**)(param_1+0x24) = puVar1;
      if (puVar1 == 0){
        puVar1 = (uint32_t*)__assert_func(((unsigned long)&rodata_f8cd5) /*=0xf8cd5*/, 0x1ae, 0, ((unsigned long)&rodata_f8bb7) /*=0xf8bb7*/);
      }
      puVar1[1] = 0; puVar1[2] = 0; puVar1[0] = 0; puVar1[3] = 0;
    }
    iVar5 = *(int*)(param_1+0x24);
    puVar1 = *(uint32_t**)(iVar5+8);
    uVar4 = param_2;
    if (puVar1 == 0){
      puVar1 = (uint32_t*)i2b(param_1, 0x271);
      *(uint32_t**)(iVar5+8) = puVar1;
      puVar1[0] = 0;
    }
    while (1){
      puVar2 = puVar1;
      param_2 = uVar4;
      if (iVar3 & 1){
        param_2 = bigint_mult(param_1, uVar4, (uint32_t)puVar2);
        Bfree(param_1, uVar4);
      }
      iVar3 = iVar3 >> 1;
      if (iVar3 == 0) break;
      puVar1 = (uint32_t*)*puVar2;
      uVar4 = param_2;
      if (*puVar2 == 0){
        puVar1 = (uint32_t*)bigint_mult(param_1, (uint32_t)puVar2, (uint32_t)puVar2);
        *puVar2 = (uint32_t)puVar1;
        puVar1[0] = 0;
      }
    }
  }
  return param_2;
}
