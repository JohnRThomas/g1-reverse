/* named: nrfx_gppi_task_endpoint_setup */
/* Reconstructed nrfx_gppi_task_endpoint_setup @ 0x64f78  (parity: 300/300 trials, PROVEN) */

extern void printk(int a, int b, int c, int d, int e);
extern unsigned int assert_post_action(int a, int b);
void nrfx_gppi_task_endpoint_setup(unsigned int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int val = param_1;
  if (param_2 == 0) {
    printk(0x00099cbdUL, 0x000f6a4aUL, 0x000f6a09UL, 0x4a, param_4);
    val = assert_post_action(0x000f6a09UL, 0x4a);
  }
  *(volatile unsigned int *)(param_2 + 0x80) = val | 0x80000000UL;
}

