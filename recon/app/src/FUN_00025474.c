/* Reconstructed FUN_00025474 @ 0x25474  (parity: 300/300 trials, PROVEN) */

extern int FUN_00025458(void);
extern int thunk_FUN_00074f68(void);

unsigned int FUN_00025474(void)
{
  volatile int *piVar1 = (volatile int *)0x20007a10UL;
  int iVar2 = FUN_00025458();
  unsigned int uVar3;
  if (iVar2 == 0) {
    iVar2 = thunk_FUN_00074f68();
    if (iVar2 - *piVar1 < 0) {
      thunk_FUN_00074f68();
    }
    uVar3 = 0;
  } else {
    iVar2 = thunk_FUN_00074f68();
    *piVar1 = iVar2;
    uVar3 = 1;
  }
  return uVar3;
}

