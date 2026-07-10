/* net-core FUN_01016160 @ 0x1016160  (parity 300 trials PROVEN) */

static volatile int * const DAT_0101616c = (volatile int *)0x21000f68;
int FUN_01016160(void)
{
  int v = DAT_0101616c[2];
  if (v != 0) v = 1;
  return v;
}

