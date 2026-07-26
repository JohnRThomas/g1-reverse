/* readable reconstruction; identity: FUN_000658e8 @ 0x000658e8
 * public-name: gpiote_pin_channel_get
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_pin_idx                              <= FUN_00065434 @ 0x00065434
 *   pin_in_use_by_te                         <= FUN_00065460 @ 0x00065460
 *   gpiote_pin_channel_get                   <= FUN_000658e8 @ 0x000658e8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f6b00                             @ 0x000f6b00
 *   rodata_f6b7d                             @ 0x000f6b7d   [INLINED -- G6 literal batch]
 *   g_gpiote_cb                              @ 0x20002bc0
 */
/* Reconstructed FUN_000658e8 @ 0x658e8  (parity: 300/300 trials, PROVEN) */

extern unsigned long long get_pin_idx(unsigned int a);
extern int pin_in_use_by_te(void);
extern void assert_post_action(int a,int b);
extern void printk(int a,int b,int c,int d);

unsigned int gpiote_pin_channel_get(unsigned int param_1, int param_2)
{
  int iVar1;
  unsigned int uVar2;
  unsigned long long uVar3;

  if (param_2 == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"p_channel"), 0x000f6b00, 0x265);
    assert_post_action(0x000f6b00, 0x265);
  }
  iVar1 = pin_in_use_by_te();
  uVar2 = 0x0bad0004;
  if (iVar1 != 0) {
    uVar3 = get_pin_idx(param_1);
    uVar2 = 0x0bad0000;
    unsigned int lo = (unsigned int)uVar3;
    unsigned int hi = (unsigned int)(uVar3 >> 32);
    *(volatile unsigned char*)(unsigned long)hi = (unsigned char)((*(volatile unsigned short*)(0x20002bc0UL + (unsigned long)(lo+8)*2)) >> 0xd);
  }
  return uVar2;
}
