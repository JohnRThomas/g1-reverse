/* Reconstructed FUN_00086c1e @ 0x86c1e  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_00051164(void);
extern void memcpy(void);

void FUN_00086c1e(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int uVar1 = param_1;
  unsigned int uVar2 = param_2;
  if (param_3 > param_4) goto call_again;
  goto check;
call_again: {
    unsigned long long uVar3 = FUN_00051164();
    uVar1 = (unsigned int)uVar3;
    uVar2 = (unsigned int)(uVar3 >> 32);
  }
check:
  if (uVar2 <= uVar1) {
    if (uVar1 < uVar2 + param_3) goto call_again;
    if (uVar2 != uVar1) goto do_tail;
  }
  if (uVar1 + param_3 <= uVar2) goto do_tail;
  goto call_again;
do_tail:
  memcpy();
}

