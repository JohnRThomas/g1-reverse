/* Reconstructed FUN_0005de70 @ 0x5de70  (parity: 200/200 trials, PROVEN) */
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int undefined4;

extern int FUN_00052cdc(int a);
extern int FUN_0005503c(int a);
extern void bt_id_add(int a); /* SDK public wrapper; FUN_0005505c @ 0x0005505c */
extern void FUN_00056960(int a, u32 b, void *c);
extern void FUN_00056d1c(int a);
extern void FUN_0005daf0(int a, int event);
extern int FUN_0005e938(u32 a, void *b);
extern int FUN_0005e9d0(int a, u32 b, int c);
extern void FUN_0005ea18(int a);
extern void FUN_0007e2ec(u32 a, u32 b);
extern void FUN_0007e2fa(unsigned long, ...);
extern int FUN_00082ff6(void *a, int b);
extern int FUN_00083002(int a, int b);
extern void FUN_00083062(int a, void *b);
extern void FUN_00083074(u32 a, u32 b, void *c);
extern void FUN_00083090(int a, int b);
extern int FUN_00086be4(int a, void *b, int c);

undefined4 FUN_0005de70(int param_1, int param_2)
{
  char *pcVar6;
  int iVar5, iVar7, iVar1, iVar2;
  undefined4 uVar3;
  char *pcVar4;

  pcVar6 = *(char **)(param_2 + 0xc);
  *(volatile u8*)(long)(param_1 + 0xe9) = (u8)(*(volatile u8*)(long)(param_1 + 0xe9) & 0xfd);
  iVar5 = *(int *)(long)(param_1 + 0xf0);
  iVar7 = iVar5 + 0x90;

  if ((*pcVar6 != 0) && ((pcVar6[6] & 0xc0) != 0xc0)) {
    FUN_00052cdc((int)(long)pcVar6);
    FUN_00083074(0x00088180u, 0x1c40u, 0);
    FUN_00052cdc(iVar7);
    FUN_00083074(0x00088180u, 0x1c40u, 0);
    return 10;
  }

  iVar1 = FUN_00086be4(iVar7, pcVar6, 7);
  if (iVar1 == 0 || (iVar1 = FUN_0005e938(*(u8*)(long)(iVar5+8), pcVar6), iVar1 == 0)) {
LAB_df2c:
    iVar1 = FUN_00082ff6((void*)(long)(param_1+4), 0xd);
    if (iVar1 != 0) {
      iVar1 = FUN_0005e9d0(2, *(u8*)(long)(iVar5+8), iVar7);
      if (iVar1 == 0) {
        FUN_00052cdc(iVar7);
        FUN_00083074(0x00088180u, 0x1c40u, 0);
        goto LAB_df70;
      }
      if (*(char*)(long)(iVar5+3) == 0) {
        pcVar4 = (char*)(long)(iVar5 + 0x9e);
      } else {
        pcVar4 = (char*)(long)(iVar5 + 0x97);
      }
      if ((*pcVar4 == 1) && ((pcVar4[6] & 0xc0) == 0x40)) {
        *(u32*)(long)(iVar1+0x3a) = *(u32*)((long)pcVar4+1);
        *(u16*)(long)(iVar1+0x3e) = *(u16*)((long)pcVar4+5);
        if ((*(char*)(long)(iVar5+0x90) != 0) && ((*(u8*)(long)(iVar5+0x96) & 0xc0) != 0xc0)) {
          FUN_00056960(1, 0x000831e3u, 0);
          FUN_00083062(iVar1+1, pcVar6);
          FUN_00056d1c(iVar5);
        }
      }
      if ((int)((u32)(*(volatile u8*)(long)(param_1+0xe9)) << 0x1e) < 0) {
        FUN_0007e2fa(0x00099cbdu, 0x000f50d6u, 0x000f50a7u, 0xec9u);
        uVar3 = 0xec9;
        FUN_0007e2ec(0x000f50a7u, uVar3);
      }
      iVar5 = FUN_0005503c(iVar1);
      if (iVar5 != 0) {
        FUN_00083074(0x00088180u, 0x1080u, 0);
        return 3;
      }
      iVar5 = FUN_0005503c(iVar1);
      if (iVar5 != 0) {
        FUN_0007e2fa(0x00099cbdu, 0x000f512cu, 0x000f50a7u, 0xee5u);
        uVar3 = 0xee5;
        FUN_0007e2ec(0x000f50a7u, uVar3);
      }
      bt_id_add(iVar1);
    }
    if ((int)((u32)(*(volatile u8*)(long)(param_1+0xe9)) << 0x1d) < 0) {
      FUN_00083090(param_1, 10);
    }
    if (*(volatile u16*)(long)(param_1+0xe8) == 0) {
      FUN_0005daf0(param_1, 0);
    }
    uVar3 = 0;
  } else {
    iVar2 = FUN_00083002(param_1, iVar1);
    if (iVar2 != 0) {
      FUN_0005ea18(iVar1);
      goto LAB_df2c;
    }
LAB_df70:
    uVar3 = 8;
  }
  return uVar3;
}
