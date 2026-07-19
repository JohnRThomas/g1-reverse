#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005109c @ 0x0005109c
 * public-name: retarget_lock_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   retarget_lock_init                       <= FUN_0005109c @ 0x0005109c
 *   malloc                                   <= FUN_00076d6c @ 0x00076d6c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   kmutex_dlist_init                        <= FUN_000864c2 @ 0x000864c2
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f22d5                             @ 0x000f22d5
 *   rodata_f23d3                             @ 0x000f23d3
 *   rodata_f23d4                             @ 0x000f23d4
 *   rodata_f240f                             @ 0x000f240f
 */
/* Reconstructed FUN_0005109c @ 0x5109c  (parity: 300/300 trials, PROVEN) */

extern int malloc(int);
extern void assert_post_action(void*, unsigned int);
extern void printk(void*, void*, void*, int);
extern void kmutex_dlist_init(void);

void retarget_lock_init(int *param_1)
{
  int iVar1;
  unsigned int uVar2;

  if (param_1 == 0) {
    printk((void*)((unsigned long)&rodata_99cbd) /*=0x99cbd*/, (void*)((unsigned long)&rodata_f23d4) /*=0xf23d4*/, (void*)((unsigned long)&rodata_f22d5) /*=0xf22d5*/, 0x179);
    uVar2 = 0x179;
    assert_post_action((void*)((unsigned long)&rodata_f22d5) /*=0xf22d5*/, uVar2);
  }
  iVar1 = malloc(0x14);
  *param_1 = iVar1;
  if (iVar1 != 0) {
    kmutex_dlist_init();
    return;
  }
  printk((void*)((unsigned long)&rodata_99cbd) /*=0x99cbd*/, (void*)((unsigned long)&rodata_f23d3) /*=0xf23d3*/, (void*)((unsigned long)&rodata_f22d5) /*=0xf22d5*/, 0x181);
  printk((void*)((unsigned long)&rodata_f240f) /*=0xf240f*/, 0,0,0);
  uVar2 = 0x181;
  assert_post_action((void*)((unsigned long)&rodata_f22d5) /*=0xf22d5*/, uVar2);
}
