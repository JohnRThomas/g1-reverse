/* readable reconstruction; identity: FUN_010225ac @ 0x010225ac
 * public-name: FUN_010225ac
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_libc_tz_calc_state                     @ 0x210016f0
 */
/* net-core FUN_010225ac @ 0x10225ac  (parity 300 trials PROVEN) */
typedef unsigned char byte;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef long long longlong;
typedef unsigned long long ulonglong;

#define CARRY4(a,b) ((uint)((uint)(a)+(uint)(b)) < (uint)(a))

extern int FUN_010244cc(uint,void*,void*);
extern longlong FUN_0102445c(void);
extern int FUN_01024644(void);
extern uint FUN_010245d8(int);
extern int FUN_01024ad0(void);
extern int FUN_010246d8(void);
extern int FUN_01021df0(undefined4,void*,uint,uint,undefined1);
extern int FUN_01024524(int,int,void*,void*,void*);

void FUN_010225ac(uint param_1,uint param_2,char *param_3,uint *param_4,undefined1 param_5)
{
  ushort uVar1;
  undefined2 uVar2;
  char cVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int bVar10;
  longlong lVar11;
  undefined1 uStack_35;
  int local_34;
  uint local_30;
  uint uStack_2c;

  uVar1 = *(ushort *)(param_3 + 8);
  uVar2 = *(undefined2 *)(param_3 + 10);
  cVar3 = *param_3;
  *(volatile uint *)((char *)param_4 + 0x10) = 0;
  *(volatile uint *)((char *)param_4 + 0xc) = 0;
  *(volatile undefined2 *)((char *)param_4 + 0x10) = uVar2;
  *(volatile uint *)((char *)param_4 + 0x8) = 0;
  *(volatile uint *)((char *)param_4 + 0x14) = 0;
  *(volatile ushort *)((char *)param_4 + 0xe) = uVar1;
  *(volatile char *)((char *)param_4 + 0x12) = cVar3;
  *(volatile uint *)((char *)param_4 + 0x0) = 0;
  *(volatile uint *)((char *)param_4 + 0x4) = 0;
  if (cVar3 != '\0') {
    FUN_010244cc(0x1e847fff - (uint)uVar1,&local_34,param_4 + 3);
    sVar4 = *(short *)((int)param_4 + 0xe);
    FUN_010244cc((unsigned short)sVar4,&local_30,&uStack_35);
    iVar5 = FUN_01024644();
    uVar7 = FUN_010245d8(iVar5);
    if (*(char *)(0x210016f0 + 0x4a) == ' ') {
      uVar8 = param_1 + 0xb;
      uVar9 = param_2 + (0xfffffff4 < param_1);
      if ((sVar4 != 0) && (iVar5 = FUN_01024ad0(), iVar5 == 0)) {
        iVar5 = FUN_010246d8();
        if (iVar5 == 0x356) {
          uVar8 = param_1 + 0x27;
          uVar9 = param_2 + (0xffffffd8 < param_1);
        }
        else if (iVar5 == 0x5f5) {
          uVar8 = param_1 + 0x3d;
          uVar9 = param_2 + (0xffffffc2 < param_1);
        }
        else if (iVar5 == 0x18c) {
          uVar8 = param_1 + 0x18;
          uVar9 = param_2 + (0xffffffe7 < param_1);
        }
      }
      if (local_30 < uVar7) {
        bVar10 = CARRY4(uVar7 - local_30,uVar8);
        uVar8 = (uVar7 - local_30) + uVar8;
        uVar9 = uVar9 + bVar10;
      }
    }
    else {
      uVar7 = *(uint *)(0x210016f0 + 0x10) + 7;
      uVar8 = uVar7 + *(uint *)(0x210016f0 + 0x18);
      uVar9 = *(int *)(0x210016f0 + 0x14) + (uint)(0xfffffff8 < *(uint *)(0x210016f0 + 0x10)) +
              (uint)CARRY4(uVar7,*(uint *)(0x210016f0 + 0x18));
    }
    iVar5 = *(int *)(param_3 + 4);
    if (param_3[0xb] == '\0') {
      iVar6 = 0x7a;
    }
    else {
      iVar6 = 0x60;
    }
    *param_4 = uVar8;
    param_4[1] = uVar9;
    uVar7 = FUN_010245d8(iVar6 + (uint)*(ushort *)((int)param_4 + 0xe) + (uint)(byte)param_4[3] +
                                 iVar5 + 2);
    param_4[2] = uVar7;
    iVar5 = FUN_01021df0(*(undefined4 *)(param_3 + 0x10),param_4,param_1,param_2,param_5);
    if (iVar5 == 0) {
      *param_4 = param_1;
      param_4[1] = param_2;
    }
    return;
  }
  lVar11 = FUN_0102445c();
  uVar8 = *(uint *)(param_3 + 0x10);
  uVar7 = *(uint *)(param_3 + 0x14);
  uVar9 = (uint)(lVar11 + (ulonglong)(uint)0x0f424000 >> 0x20);
  if ((uVar7 <= uVar9 && (uint)((uint)(lVar11 + (ulonglong)(uint)0x0f424000) <= uVar8) <= uVar7 - uVar9)
     && (uVar9 = (uint)((ulonglong)(lVar11 + 0x2f) >> 0x20),
        uVar9 < uVar7 || uVar7 - uVar9 < (uint)((uint)(lVar11 + 0x2f) <= uVar8))) {
    uVar9 = *(ushort *)(param_3 + 8) + 1;
    if (uVar7 == 0 && (uVar9 <= uVar8) <= uVar7) {
      iVar5 = 0;
      iVar6 = 0;
    }
    else {
      iVar5 = uVar8 - uVar9;
      iVar6 = uVar7 - (uVar8 < uVar9);
    }
    FUN_01024524(iVar5,iVar6,&local_34,&local_30,param_4 + 3);
    if (param_3[0xb] == '\0') {
      iVar5 = 0x7a;
    }
    else {
      iVar5 = 0x60;
    }
    iVar5 = FUN_010245d8(iVar5 + local_34 + 2 + *(int *)(param_3 + 4) +
                                 (uint)*(ushort *)(param_3 + 8));
    *param_4 = local_30;
    param_4[1] = uStack_2c;
    param_4[2] = iVar5 - local_30 & 0xffffff;
    return;
  }
  *param_4 = param_1 - 1;
  param_4[1] = (param_2 - 1) + (uint)(param_1 != 0);
  param_4[2] = 1000;
  return;
}
