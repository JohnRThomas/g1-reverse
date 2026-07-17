#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083bf0 @ 0x00083bf0
 * public-name: dev_write_config_word
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_write_config_word                    <= FUN_00083bf0 @ 0x00083bf0
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 *   k_is_in_isr                              <= FUN_00086406 @ 0x00086406
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 */
/* Reconstructed FUN_00083bf0 @ 0x83bf0  (parity: 300/300 trials, PROVEN) */
extern int dev_write_reg3(int,int,unsigned,unsigned);
extern int k_is_in_isr(void);
int dev_write_config_word(int param_1, unsigned param_2, int param_3){
  int iVar3 = *(int*)(param_1 + 4);
  unsigned uVar2;
  int iVar1;
  if (k_is_in_isr() != 0) return -0xb;
  if (param_2 > 4) return -0x16;
  uVar2 = 0;
  if ((param_3 & ((unsigned long)&rodata_10000) /*=0x10000*/) == 0){
    if (param_3 & 0x400) uVar2 = 6;
    else if (param_3 & 0x800) uVar2 = 7;
    else if (param_3 & 0x80000) uVar2 = 8;
    else { if ((param_3 & 0x20000) == 0) goto L_c36; uVar2 = 9; }
  }
  iVar1 = dev_write_reg3(*(int*)(iVar3+4), 6, param_2, uVar2);
  if (iVar1 < 0) return iVar1;
 L_c36:
  iVar1 = dev_write_reg3(*(int*)(iVar3+4), 6, (param_2+0x14)&0xff, (unsigned)(param_3>>1)&1);
  if (iVar1 < 0) return iVar1;
  iVar1 = dev_write_reg3(*(int*)(iVar3+4), 6, (param_2+0xa)&0xff, (unsigned)(param_3>>4)&1);
  if (iVar1 < 0) return iVar1;
  iVar1 = dev_write_reg3(*(int*)(iVar3+4), 6, (param_2+0xf)&0xff, (unsigned)(param_3>>5)&1);
  if (iVar1 < 0) return iVar1;
  iVar1 = dev_write_reg3(*(int*)(iVar3+4), 6, (param_2+5)&0xff, (unsigned)(param_3>>8)&1);
  if (iVar1 < 0) return iVar1;
  return dev_write_reg3(*(int*)(iVar3+4), 6, (param_2+0x19)&0xff, (unsigned)(param_3>>9)&1);
}
