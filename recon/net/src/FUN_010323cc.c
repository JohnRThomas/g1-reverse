/* net-core FUN_010323cc @ 0x10323cc — true CFG extent 38 bytes (ends 0x10323f2) */
/* net-core FUN_010323cc @ 0x10323cc  (parity 300 trials PROVEN) */
/* net-core FUN_010323cc @ 0x10323cc  (parity 300 trials PROVEN) */
/* net-core FUN_010323cc @ 0x10323cc  (parity 300 trials PROVEN) */

extern unsigned int FUN_0102665c(int, void*);
extern void FUN_0103b614(int, void*, unsigned int);
unsigned int FUN_010323cc(int param_1, unsigned char *param_2)
{
  volatile unsigned char *p = (volatile unsigned char*)0x210051ae;
  if (p[0] != 0) {
    FUN_0103b614(param_1, (void*)(p+1), (unsigned int)p[2] + 2);
    p[0] = 0;
    param_2[0] = 4;
    return 0;
  }
  return FUN_0102665c(param_1, (void*)param_2);
}



