/* Reconstructed FUN_00077d54 @ 0x77d54  (parity: 300/300 trials, PROVEN) */
extern void FUN_00076bcc(int);
extern void FUN_00076cec(void*,void*);
extern void FUN_00076d8c(void*);
int FUN_00077d54(int *param_1, int *param_2){
  int iVar4 = *(volatile int*)0x20002d20UL;
  if (iVar4 != 0 && *(int*)(iVar4+0x18) == 0) FUN_00076bcc(iVar4);
  if (param_2 == (int*)0x0009871c) param_2 = *(int**)(iVar4+4);
  else if (param_2 == (int*)0x000986fc) param_2 = *(int**)(iVar4+8);
  else if (param_2 == (int*)0x000986dc) param_2 = *(int**)(iVar4+0xc);
  volatile unsigned short *P0c = (volatile unsigned short*)((char*)param_2 + 0xc);
  volatile int *pv = (volatile int*)param_2;
  int s = *(short*)((char*)param_2 + 0xc);
  if ((s & 8) == 0){
    if ((s & 0x10) == 0){
      *(volatile int*)param_1 = 9;
      *P0c = (unsigned short)(s | 0x40);
      return -1;
    }
    if (s & 4){
      if (param_2[0xd] != 0){
        if ((int*)param_2[0xd] != param_2 + 0x11) FUN_00076d8c(param_1);
        pv[0xd] = 0;
      }
      *P0c = *P0c & 0xffdb;
      pv[1] = 0;
      pv[0] = param_2[4];
    }
    *P0c = *P0c | 8;
  }
  if (param_2[4] == 0 && (*P0c & 0x280) != 0x200)
    FUN_00076cec(param_1, param_2);
  {
    int s2 = *(short*)((char*)param_2+0xc);
    if (s2 & 1){
      pv[2] = 0;
      pv[6] = -param_2[5];
    } else {
      pv[2] = (s2 & 2) ? 0 : param_2[5];
    }
    if (param_2[4] != 0) return 0;
    if ((s2 & 0x80) == 0) return 0;
    *P0c = (unsigned short)(s2 | 0x40);
    return -1;
  }
}

