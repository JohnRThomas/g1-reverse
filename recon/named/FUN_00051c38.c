/* readable reconstruction; identity: FUN_00051c38 @ 0x00051c38
 * public-name: FUN_00051c38
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f2561                             @ 0x000f2561
 *   rodata_f25c5                             @ 0x000f25c5
 *   rodata_f25e2                             @ 0x000f25e2
 */
/* Reconstructed FUN_00051c38 @ 0x51c38  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int) __attribute__((noreturn));

void FUN_00051c38(void)
{
  unsigned int uVar1;

  uVar1 = 0x000f2561UL;
  printk(0x00099cbdUL,0x000f25c5UL,0x000f2561UL,0x71);
  printk(0x000f25e2UL,0,0,0);
  assert_post_action(uVar1,0x71);
}
