/* Reconstructed send_event @ 0x276ec  (parity: 300/300 trials, PROVEN) */

extern int FUN_00017eec(void*, int);
extern int FUN_000181fc(void);
extern void FUN_0007cb8e(int);
extern void thunk_FUN_00072880(int);

void send_event(int param_1, unsigned int param_2, unsigned int param_3)
{
  int iVar3;
  unsigned char cVar1;
  unsigned char *pcVar2 = (unsigned char*)0x2000302eUL;
  unsigned char buf[8];

  iVar3 = FUN_000181fc();
  if ((unsigned int)(param_1 - 0xf0) > 2 || *pcVar2 == 0xff) {
    cVar1 = *(unsigned char*)(iVar3 + 0x248);
    *pcVar2 = (unsigned char)param_1;
    if (cVar1 != 0) {
      goto build;
    }
    if (*(int*)(iVar3 + 0x220) != 0) {
      goto build;
    }
    if (*(unsigned char*)(iVar3 + 0x248) != 0) {
      return;
    }
    thunk_FUN_00072880(iVar3 + 0x218);
    FUN_0007cb8e(1);
    return;
  build:
    buf[0] = 0xf5;
    buf[1] = (unsigned char)param_1;
    buf[2] = 0xcb;
    FUN_00017eec(buf, 3);
    *pcVar2 = 0xff;
    return;
  }
}

