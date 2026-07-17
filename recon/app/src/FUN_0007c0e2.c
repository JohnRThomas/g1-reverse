/* Reconstructed FUN_0007c0e2 @ 0x7c0e2  (parity: 300/300 trials, PROVEN) */

extern int FUN_000181fc(void);
extern int FUN_00018e48(void *p);
extern void FUN_00072880(unsigned int a);

void FUN_0007c0e2(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  struct event_record {
    unsigned int value;
    unsigned int mode;
    unsigned int context;
  } event = { param_1, (param_2 & 0xffffff00u) | 2u, param_3 };
  int iVar1 = FUN_000181fc();
  int iVar2 = FUN_00018e48(&event);
  if (iVar2 == 0) {
    FUN_00072880((unsigned int)iVar1 + 0x200);
  }
}
