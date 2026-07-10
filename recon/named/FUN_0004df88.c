/* named: FUN_0004df88 */
/* Reconstructed FUN_0004df88 @ 0x4df88  (parity: 300/300 trials, PROVEN) */

extern int z_device_is_ready(unsigned int);
extern void printk(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
extern void assert_post_action(unsigned int,unsigned int);
void FUN_0004df88(void)
{
  int iVar1;
  iVar1 = z_device_is_ready(0x00087bc0UL);
  if (iVar1 == 0) {
    printk(0x00099cbdUL,0x000f0fafUL,0x000f0f71UL,0x7f,0);
    assert_post_action(0x000f0f71UL,0x7f);
  }
  return;
}

