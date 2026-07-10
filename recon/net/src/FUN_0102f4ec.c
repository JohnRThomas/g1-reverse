/* net-core FUN_0102f4ec @ 0x102f4ec  (parity 300 trials PROVEN) */

static void DataSynchronizationBarrier(int opt) { (void)opt; }

void FUN_0102f4ec(void)
{
  volatile unsigned int *p = (volatile unsigned int *)0xe000ed00;
  DataSynchronizationBarrier(0xf);
  p[3] = 0x05fa0004 | (p[3] & 0x700);
  DataSynchronizationBarrier(0xf);
  while (1) { }
}

