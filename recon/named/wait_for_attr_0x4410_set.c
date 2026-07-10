/* named: wait_for_attr_0x4410_set */
/* Reconstructed wait_for_attr_0x4410_set @ 0x7cf70  (parity: 300/300 trials, PROVEN) */

extern int attr_store_get(int a, int *b);
extern void attr_store_retry_delay(int a);
int wait_for_attr_0x4410_set(void)
{
  int iVar1;
  unsigned char cVar2 = 0x65;
  int local_c = 0;
  while (1) {
    iVar1 = attr_store_get(0x4410, &local_c);
    if (iVar1 < 0) return -1;
    if ((local_c & 1) != 0) break;
    cVar2 = cVar2 - 1;
    attr_store_retry_delay(1);
    if (cVar2 == 0) return -2;
  }
  return 0;
}

