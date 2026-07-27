/* Reconstructed parse_ncs_notification @ 0x34980  (parity: 300/300 trials, PROVEN) */
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern int  FUN_0000eefe(int,int);
extern int  FUN_0004a3d0(int,int*);
extern int  FUN_00064b1c(int);
extern int  FUN_0007d224(void);
extern int  FUN_0008500c(void);
extern int FUN_0008503c(int, int);
extern void FUN_00086c78(int*,int,int);
extern void FUN_0008705a(int,int,int);
#define VI(a) (*(volatile int*)(a))

void parse_ncs_notification(int param_1, int *param_2){
  volatile int *lvl=(volatile int*)0x2000230cUL;
  volatile int *g8=(volatile int*)0x20007554UL;
  int iVar1,iVar2,iVar3,iVar4,iVar5,iVar6,iVar7,iVar8,iVar9;
  (void)param_1;
  iVar1 = FUN_0008500c();
  if (iVar1 == 0) {
    if (0 < *lvl) {
      if (*g8 != 0) { FUN_00019c70(0x000a838d,0x000a83e9); return; }
      DEBUG_PRINT(0x000a838d,0x000a83e9); return;
    }
    return;
  }
  iVar2 = FUN_0008503c(iVar1, 0x0009d79d);
  if (iVar2 == 0) {
    if (0 < *lvl) { if (*g8==0) DEBUG_PRINT(0x000a83aa,0x000a83e9); else FUN_00019c70(0x000a83aa,0x000a83e9); }
    FUN_00064b1c(iVar1);
    return;
  }
  iVar3 = FUN_0008503c(iVar2, 0x0009d759);
  iVar4 = FUN_0008503c(iVar2, 0x0009b257);
  iVar5 = FUN_0008503c(iVar2, 0x0009d76c);
  iVar6 = FUN_0008503c(iVar2, 0x0009d775);
  iVar7 = FUN_0008503c(iVar2, 0x000f3fde);
  iVar8 = FUN_0008503c(iVar2, 0x0009d790);
  iVar9 = FUN_0008503c(iVar2, 0x000a83ca);
  iVar2 = FUN_0008503c(iVar2, 0x000a83d1);
  FUN_00086c78(param_2,0,0x1b4);
  if (iVar3 != 0) {
    FUN_0008705a((int)(param_2+4), VI(iVar3+0x10), 0x1f);
    if (FUN_0000eefe(VI(iVar3+0x10), 0x000a81b7) == 0)
      *(volatile int*)(param_2+1) = FUN_0007d224();
  }
  if (iVar4 != 0) FUN_0008705a((int)(param_2+0x14), VI(iVar4+0x10), 0x1f);
  if (iVar6 != 0) FUN_0008705a((int)(param_2+0x24), VI(iVar6+0x10), 0xff);
  if (iVar5 != 0) FUN_0008705a((int)(param_2+0x1c), VI(iVar5+0x10), 0x1f);
  if (iVar7 != 0) FUN_0008705a((int)(param_2+100), VI(iVar7+0x10), 0x20);
  if (iVar8 != 0) FUN_0008705a((int)(param_2+0xc), VI(iVar8+0x10), 0x1f);
  if (iVar9 != 0) *(volatile int*)(param_2+2) = VI(iVar9+0x14);
  if (iVar2 != 0) *(volatile int*)(param_2+0x6c) = VI(iVar2+0x14);
  *(volatile int*)param_2 = FUN_0007d224();
  FUN_00064b1c(iVar1);
  FUN_0004a3d0(0x000a83d8, param_2);
}

