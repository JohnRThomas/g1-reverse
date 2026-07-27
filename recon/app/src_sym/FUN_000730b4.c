/* Reconstructed FUN_000730b4 @ 0x730b4  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned long, ...);
extern int assert_post_action(unsigned int a, unsigned int b);
extern void memset_bytes(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void FUN_000730b4(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int r0 = (unsigned int)param_1;
  if (param_1 == 0) {
    printk(0x99cbd, 0xf824d, 0xf820f, 0x2b9);
    r0 = assert_post_action(0xf820f, 0x2b9);
  }
  memset_bytes(r0, 0, 0xf8, param_4, param_4);
}

