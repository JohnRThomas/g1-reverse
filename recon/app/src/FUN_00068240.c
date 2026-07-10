/* Reconstructed FUN_00068240 @ 0x68240  (parity: 300/300 trials, PROVEN) */

extern void *FUN_00086c78(void*, int, int);
extern unsigned int FUN_00068170(void*);

unsigned int FUN_00068240(unsigned int *param_1)
{
  unsigned char *puVar1;

  puVar1 = (unsigned char*)FUN_00086c78((void*)0x2000b424UL, 0, 0x20);
  *(volatile unsigned int*)(puVar1+4) = *param_1;
  *puVar1 = *((unsigned char*)param_1 + 4);
  *(unsigned char**)(puVar1+8) = puVar1+8;
  *(unsigned char**)(puVar1+0xc) = puVar1+8;
  *(unsigned char**)(puVar1+0x10) = puVar1+0x10;
  *(unsigned char**)(puVar1+0x14) = puVar1+0x10;
  *(unsigned char**)(puVar1+0x18) = puVar1+0x18;
  *(unsigned char**)(puVar1+0x1c) = puVar1+0x18;
  return FUN_00068170((void*)0x20002c3cUL);
}

