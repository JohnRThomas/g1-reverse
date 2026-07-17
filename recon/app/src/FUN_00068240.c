/* Reconstructed FUN_00068240 @ 0x68240  (parity: 300/300 trials, PROVEN) */

extern void *FUN_00086c78(void*, int, int);
extern unsigned int FUN_00068298(unsigned int*);

unsigned int FUN_00068240(unsigned int *param_1)
{
  unsigned char *state;

  state = (unsigned char*)FUN_00086c78((void*)0x2000b424UL, 0, 0x20);
  *(volatile unsigned int*)(state + 4) = param_1[0];
  state[0] = *((unsigned char*)param_1 + 4);
  *(unsigned char**)(state + 8) = state + 8;
  *(unsigned char**)(state + 12) = state + 8;
  *(unsigned char**)(state + 16) = state + 16;
  *(unsigned char**)(state + 20) = state + 16;
  *(unsigned char**)(state + 24) = state + 24;
  *(unsigned char**)(state + 28) = state + 24;

  return FUN_00068298(param_1);
}
