/* Reconstructed uart_callback @ 0x33384  (parity: 295/300 trials, PROVEN) */
extern void DEBUG_PRINT(int,...);
extern void EPILOGUE(void);
extern void FUN_00019c70(void);
extern int  FUN_00071c20(int,void*,int,int);
extern void FUN_00071cf4(int,int);
extern void FUN_0007e2ec(int,int);
extern void FUN_0007e2fa(int,int,int,int);
extern void FUN_00086c04(int,...);
extern void FUN_00086c78(void*,int,int);
#define VI(a) (*(volatile int*)(a))
#define VB(a) (*(volatile unsigned char*)(a))

void uart_callback(int param_1,unsigned char *param_2,unsigned int param_3){
  volatile int *lvl=(volatile int*)0x2000230cUL, *g8=(volatile int*)0x20007554UL;
  int iVar2; unsigned int uVar5,uVar7; char cVar1; int iVar6; void *local_1c=param_2;
  switch (*param_2) {
  case 0:
    if (2 < *lvl) { if(*g8==0) DEBUG_PRINT(0xa797b,0xa7b56,VI((int)param_2+8),0,param_1); else FUN_00019c70(); }
    for (uVar5=0; uVar5 < (unsigned int)VI((int)param_2+8); uVar5++)
      DEBUG_PRINT(0xa7993, VB(VI((int)param_2+4)+uVar5));
    break;
  case 1:
    if (*lvl < 1) { EPILOGUE(); return; }
    if (*g8 != 0) { FUN_00019c70(); return; }
    DEBUG_PRINT(0xa7999,0xa7b56); return;
  case 2:
    uVar5 = VI((int)param_2+8);
    for (uVar7 = uVar5 & 0xffff; (uVar7 & 0xffff) < 0xf8; uVar7++) {
      iVar2 = VI((int)param_2+4);
      param_3 = VB(iVar2+uVar7);
      if (param_3==0x5a && VB(iVar2+uVar7+1)==0xa5 && VB(iVar2+uVar7+2)==0x7f) {
        param_3 = (unsigned char)(VB(iVar2+uVar7+3)+5);
        if ((int)param_3 <= (int)(0x100 - uVar7)) {
          cVar1 = 0;
          for (iVar6=0; iVar6 < (int)(param_3-1); iVar6++) cVar1 = (char)(cVar1 + VB(iVar2+uVar7+iVar6));
          if ((char)VB(iVar2+param_3+uVar7-1) == cVar1) {
            *(volatile unsigned char*)0x2001a128 = (unsigned char)param_3;
            FUN_00086c04(0x2001a129);
            FUN_00086c78((void*)VI((int)param_2+4),0,0x100);
            return;
          }
        }
      }
    }
    DEBUG_PRINT(0xa79ab, VI((int)param_2+0xc), param_3, uVar7 & 0xffff, param_1);
    for (uVar7=0; uVar7 < (unsigned int)VI((int)param_2+0xc); uVar7++)
      DEBUG_PRINT(0xa7993, VB(VI((int)param_2+4)+uVar5+uVar7));
    break;
  case 3:
    DEBUG_PRINT(0xa79bf);
    iVar2 = FUN_00071c20(0x200037b8, &local_1c, 0, 0);
    if (iVar2 != 0) { FUN_0007e2fa(0,0,0,0); FUN_0007e2fa(0,0,0,0); FUN_0007e2ec(0,0x51); }
    for (;;) {
      iVar2 = ((int(*)(int,int,int))(VI(VI((int)param_3+8)+0x10)))((int)param_3,(int)local_1c,0x100);
      if (iVar2 == 0) return;
      FUN_0007e2fa(0,0,0,0); FUN_0007e2fa(0,0,0,0); FUN_0007e2ec(0,0x54);
    }
  case 4:
    DEBUG_PRINT(0xa7a52);
    FUN_00071cf4(0x200037b8, VI((int)param_2+4));
    return;
  default:
    EPILOGUE(); return;
  }
  DEBUG_PRINT(0xf5400);
}

