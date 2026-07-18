/* Reconstructed FUN_000836de @ 0x836de  (parity: 300/300 trials, PROVEN) */

extern void net_buf_alloc_len(int, unsigned int, unsigned int, unsigned int); /* FUN_0005eeb4 @ 0x0005eeb4 */

void FUN_000836de(int param_1, unsigned int unused_2,
                   unsigned int param_3, unsigned int param_4)
{
  unsigned int queue = *(volatile unsigned int *)(param_1 + 0x2c);
  unsigned int pending = *(volatile unsigned int *)(queue + 4);
  unsigned int item = *(volatile unsigned int *)pending;

  net_buf_alloc_len(param_1, item, param_3, param_4);
}
