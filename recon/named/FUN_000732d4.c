/* readable reconstruction; identity: FUN_000732d4 @ 0x000732d4
 * public-name: FUN_000732d4
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f820f                             @ 0x000f820f
 *   rodata_f8230                             @ 0x000f8230
 *   rodata_f82df                             @ 0x000f82df
 */
/* Reconstructed FUN_000732d4 @ 0x732d4  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(void*, int);
extern void printk(void*, void*, void*, int);
extern void memset_bytes(int, int, int, unsigned int, unsigned int);

void FUN_000732d4(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int uVar1;

  if (param_1 == 0) {
    printk((void*)0x99cbdUL,(void*)0xf82dfUL,(void*)0xf820fUL,0x340);
    uVar1 = 0x340;
  } else {
    if (param_2 != 0) {
      memset_bytes(param_1,0,0x30,param_4,param_4);
      *(volatile int*)(param_1 + 4) = param_2;
      *(volatile unsigned int*)(param_1 + 0xc) = 0x100;
      return;
    }
    printk((void*)0x99cbdUL,(void*)0xf8230UL,(void*)0xf820fUL,0x341);
    uVar1 = 0x341;
  }
  assert_post_action((void*)0xf820fUL,uVar1);
}
