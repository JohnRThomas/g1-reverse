/* Reconstructed FUN_0002542c @ 0x2542c  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007c830(unsigned int);
void FUN_0002542c(void)
{
  unsigned int *puVar1 = (unsigned int *)0x20007a34UL /* device_info.gap_1030+8 */;
  FUN_0007c830(0x20007a34UL /* device_info.gap_1030+8 */);
  *(volatile unsigned int *)0x20007a24UL /* device_info.gap_101C+12 */ = *(volatile unsigned int *)puVar1;
}

