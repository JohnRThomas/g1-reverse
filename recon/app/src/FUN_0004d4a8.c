/* Reconstructed FUN_0004d4a8 @ 0x4d4a8  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_0004d490(void);
extern void FUN_0007e2ec(void*, int);
extern void FUN_0007e2fa(unsigned long, ...);

void FUN_0004d4a8(void)
{
  unsigned int uVar2;
  int *r4 = (int*)0x882a0UL;
  int *r6 = (int*)0x882b0UL;

  uVar2 = FUN_0004d490();

  for (;;) {
    if ((unsigned int)r4 > (unsigned int)r6) {
      FUN_0007e2fa((unsigned long)0x99cbdUL,(void*)0xf0cffUL,(void*)0xf0caeUL,0x1d1);
      FUN_0007e2fa((unsigned long)0xf0d20UL, 0, 0, 0);
      FUN_0007e2ec((void*)0xf0caeUL,0x1d1);
    }
    if ((unsigned int)r4 >= (unsigned int)r6) break;
    if (*(char*)(*(int*)((char*)r4+4) + 5) != 0 && *(void**)(*(int*)r4 + 4) != 0) {
      void (*fn)(void*, unsigned int) = *(void**)(*(int*)r4 + 4);
      fn(r4, uVar2);
    }
    r4 = (int*)((char*)r4 + 0x10);
  }
  return;
}

