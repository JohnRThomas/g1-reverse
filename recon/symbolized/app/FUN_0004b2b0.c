#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004b2b0 @ 0x0004b2b0
 * public-name: FUN_0004b2b0
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   chunk_size                               <= FUN_0007de18 @ 0x0007de18
 *   set_chunk_used                           <= FUN_0007de24 @ 0x0007de24
 *   mem_to_chunkid                           <= FUN_0007de5c @ 0x0007de5c
 *   split_chunks                             <= FUN_0007df98 @ 0x0007df98
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f0692                             @ 0x000f0692
 *   rodata_f075e                             @ 0x000f075e
 *   rodata_f0779                             @ 0x000f0779
 */
/* Reconstructed FUN_0004b2b0 @ 0x4b2b0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int chunk_size(int,int);
extern int set_chunk_used(int,int,int);
extern int mem_to_chunkid(int,int);
extern int FUN_0007de70(int,int);
extern int FUN_0007df24(int,int);
extern int split_chunks(int,int,int);
extern int FUN_0007e022(int,int);
extern void assert_post_action(int,int);
extern int printk(int,int,int,int,int);
extern int FUN_0007e12a(void);

int FUN_0004b2b0(int *param_1, unsigned int param_2, unsigned int param_3, int param_4){
  int iVar7 = *param_1;
  unsigned int uVar4 = *(volatile unsigned int*)(iVar7+8);
  unsigned int uVar3 = (uVar4 < 0x8000u) ? 4u : 8u;
  unsigned int uVar5 = (param_2 - 1) & param_2;
  unsigned int uVar8 = 0;
  unsigned int n = param_2;
  if (uVar5 != 0) {
    uVar8 = (0u - param_2) & param_2;
    if (uVar8 <= uVar3) uVar3 = uVar8;
    if (((uVar5 - 1) & uVar5) != 0) {
      printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f075e) /*=0xf075e*/,((unsigned long)&rodata_f0692) /*=0xf0692*/,0x144,param_4);
      printk(((unsigned long)&rodata_f0779) /*=0xf0779*/,0,0,0,0);
      assert_post_action(((unsigned long)&rodata_f0692) /*=0xf0692*/,0x144);
      uVar8 = uVar5;
    } else {
      n = uVar5;
    }
    if (param_3 == 0) return 0;
  } else {
    if (n <= uVar3) return FUN_0007e12a();
    uVar8 = 0;
    if (param_3 == 0) return 0;
  }
  /* common */
  if (!(uVar4 > (param_3 >> 3))) return 0;
  {
    int r3 = (int)(param_3 + n);
    (void)FUN_0007de70((int)uVar4, r3 - (int)uVar3);
    unsigned int df = (unsigned int)FUN_0007df24(iVar7, 0);
    if (df == 0) return 0;
    unsigned int c = (*(volatile unsigned int*)(iVar7+8) < 0x8000u) ? 4u : 8u;
    unsigned int iVar6 = n * ((uVar8 + df*8u + c + (unsigned int)iVar7 + (n - 1)) / n) - uVar8;
    unsigned int u5 = (unsigned int)mem_to_chunkid(iVar7, (int)iVar6);
    unsigned int uv3 = (unsigned int)(((int)((param_3 + iVar6 + 7) & 0xfffffff8u) - iVar7) >> 3);
    if (df < u5) { split_chunks(iVar7,(int)df,(int)u5); FUN_0007e022(iVar7,(int)df); }
    int iVar2 = chunk_size(iVar7,(int)u5);
    if (uv3 < (unsigned int)(iVar2 + (int)u5)) { split_chunks(iVar7,(int)u5,(int)uv3); FUN_0007e022(iVar7,(int)uv3); }
    set_chunk_used(iVar7,(int)u5,1);
    return (int)iVar6;
  }
}
