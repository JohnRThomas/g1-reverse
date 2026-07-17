#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00068590 @ 0x00068590
 * public-name: lc3_get_bits_left
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lc3_get_bits_left                        <= FUN_00068590 @ 0x00068590
 */
/* Reconstructed FUN_00068590 @ 0x68590  (parity: 300/300 trials, PROVEN) */

unsigned lc3_get_bits_left(char *param_1){
  unsigned uVar1 = *(unsigned*)(param_1+0x30);
  unsigned uVar3 = *(unsigned*)(param_1+0x34);
  unsigned uVar2; int iVar6;
  if(*param_1==0){ iVar6=3; uVar3=uVar3+4; uVar2=uVar1-3; }
  else { iVar6=0; uVar2=uVar1; }
  if(uVar2 < uVar3){ iVar6 = iVar6 + (int)uVar3; }
  else { uVar1 = uVar3 - uVar2; }
  unsigned uVar4 = *(unsigned*)(param_1+8);
  if(uVar2 < uVar3){ uVar1 = (unsigned)iVar6 - uVar1; }
  if(uVar4==0){ iVar6=0x1a; }
  else { iVar6=0; do{ uVar4=uVar4>>1; iVar6++; } while(uVar4!=0); iVar6=0x1a-iVar6; }
  int iVar5 = *(int*)(param_1+0x14);
  if(*(int*)(param_1+0xc) >= 0){ iVar5=iVar5+1; }
  uVar1 = uVar1*8 - (unsigned)(iVar6 + iVar5*8 + *(int*)(param_1+0x20) + *(int*)(param_1+0x24));
  return uVar1 & ~((unsigned)((int)uVar1 >> 0x1f));
}
