#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00078ac8 @ 0x00078ac8
 * public-name: bigint_diff
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   libc_fatal_error_and_abort               <= FUN_00076a94 @ 0x00076a94
 *   Balloc                                   <= FUN_000785d4 @ 0x000785d4
 *   bigint_diff                              <= FUN_00078ac8 @ 0x00078ac8
 *   bignum_compare_abs                       <= FUN_000875ae @ 0x000875ae
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 *   rodata_f8c42                             @ 0x000f8c42
 *   rodata_f8cd5                             @ 0x000f8cd5
 */
/* Reconstructed FUN_00078ac8 @ 0x78ac8  (parity: 1/300 trials, PROVEN) */
#include <stdint.h>
extern int libc_fatal_error_and_abort(unsigned a, unsigned b, int c, unsigned d);
extern int Balloc(int a, unsigned b);
extern int bignum_compare_abs(int,int,int,int,int,int,int);

int bigint_diff(int param_1,int param_2,int param_3,int param_4)
{
  int iVar1;
  int iVar2;
  int iVar3;
  unsigned uVar4;
  unsigned uVar5;
  unsigned *puVar6;
  unsigned uVar7;
  unsigned *puVar8;
  int *piVar9;
  unsigned *puVar10;
  unsigned *puVar11;
  int iVar12;
  unsigned *puVar13;
  unsigned *puVar14;
  int bVar15;

  iVar1 = bignum_compare_abs(param_2,param_3,param_3,param_4,param_1,param_2,param_3);
  bVar15 = iVar1 < 0;
  if (iVar1 == 0) {
    iVar2 = Balloc(param_1,0);
    iVar3 = iVar2;
    if (iVar2 != 0) goto LAB_00078af6;
    uVar4 = 0x232;
  }
  else {
    if (bVar15) {
      iVar1 = 1;
      param_4 = param_2;
      param_2 = param_3;
    }
    if (!bVar15) {
      iVar1 = 0;
      param_4 = param_3;
    }
    iVar3 = Balloc(param_1,*(unsigned *)(param_2 + 4));
    if (iVar3 != 0) {
      iVar12 = *(int *)(param_2 + 0x10);
      iVar2 = *(int *)(param_4 + 0x10);
      *(int *)(iVar3 + 0xc) = iVar1;
      puVar6 = (unsigned *)(param_2 + 0x10);
      puVar10 = (unsigned *)(param_4 + 0x14) + iVar2;
      puVar13 = (unsigned *)(param_2 + 0x14 + iVar12 * 4);
      iVar1 = 0;
      puVar11 = (unsigned *)(iVar3 + 0x14);
      puVar8 = (unsigned *)(param_4 + 0x14);
      do {
        puVar14 = puVar8 + 1;
        puVar6 = puVar6 + 1;
        uVar7 = ((*puVar6 & 0xffff) - (*puVar8 & 0xffff)) + iVar1;
        iVar2 = ((*puVar6 >> 0x10) - (*puVar8 >> 0x10)) + ((int)uVar7 >> 0x10);
        iVar1 = iVar2 >> 0x10;
        *puVar11 = uVar7 & 0xffff | iVar2 * ((unsigned long)&rodata_10000) /*=0x10000*/;
        puVar11 = puVar11 + 1;
        puVar8 = puVar14;
      } while (puVar14 < puVar10);
      iVar2 = ((int)puVar10 + (-0x15 - param_4) & 0xfffffffcU) + 4;
      if (puVar10 < (unsigned *)(param_4 + 0x15)) {
        iVar2 = 4;
      }
      puVar8 = (unsigned *)(iVar2 + iVar3 + 0x14);
      puVar10 = (unsigned *)(param_2 + 0x14 + iVar2);
      puVar11 = puVar8;
      for (puVar6 = puVar10; puVar6 < puVar13; puVar6 = puVar6 + 1) {
        uVar7 = *puVar6;
        uVar5 = uVar7 + iVar1;
        iVar2 = (uVar7 >> 0x10) + ((int)((uVar7 & 0xffff) + iVar1) >> 0x10);
        iVar1 = iVar2 >> 0x10;
        *puVar11 = uVar5 & 0xffff | iVar2 * ((unsigned long)&rodata_10000) /*=0x10000*/;
        puVar11 = puVar11 + 1;
      }
      uVar7 = (int)puVar13 + (3 - (int)puVar10) & 0xfffffffc;
      if (puVar13 < (unsigned *)((int)puVar10 + -3)) {
        uVar7 = 0;
      }
      piVar9 = (int *)((int)puVar8 + uVar7);
      while (piVar9 = piVar9 + -1, *piVar9 == 0) {
        iVar12 = iVar12 + -1;
      }
      *(int *)(iVar3 + 0x10) = iVar12;
      return iVar3;
    }
    uVar4 = 0x240;
    iVar3 = 0;
  }
  iVar2 = libc_fatal_error_and_abort(((unsigned long)&rodata_f8cd5) /*=0xf8cd5*/,uVar4,iVar3,((unsigned long)&rodata_f8c42) /*=0xf8c42*/);
LAB_00078af6:
  *(int *)(iVar2 + 0x10) = 1;
  *(int *)(iVar2 + 0x14) = iVar1;
  return iVar3;
}
