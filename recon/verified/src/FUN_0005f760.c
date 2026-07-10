/* Reconstructed FUN_0005f760 @ 0x5f760  (parity: 200/200 trials, PROVEN) */
typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int undefined4;

extern u64 FUN_0000e244(int a, int b, u32 c, u32 d);
extern void FUN_0004d944(u32 a, u32 b, void *c, u32 d);
extern u64 FUN_0005f638(u32 a);
extern int FUN_00072880(u32 a);
extern int FUN_00072908(u32 a, void *b, u32 c, u32 d);
extern u64 FUN_00075174(void *a, int b, u32 c, u32 d);

undefined4 FUN_0005f760(undefined4 param_1, int *param_2)
{
  int iVar7, iVar5, iVar11;
  u32 uVar4, uVar6, uVar10;
  int bVar12;
  undefined4 uVar9;
  u64 r;
  int *puVar3i;

  FUN_00072908(0x200021d0u, param_2, 0xffffffffu, 0xffffffffu);
  iVar7 = 0x20002230;
  iVar5 = 0x5000e000;
  uVar10 = (u32)param_2[1];
  uVar9 = 0x000f5571u;
  iVar11 = 0x5000e000;

  if (uVar10 - 1 < 0xff) {
    uVar4 = 0;
    uVar6 = 0;
    do {
      if (((uVar10 >> (uVar4 & 0xff)) & 1) == 0) {
        *(volatile u32*)(long)(iVar5 + (uVar4 + 0x51) * 0x10) = 0;
      } else {
        u8 bVar1 = *(volatile u8*)(long)(iVar7 + uVar4);
        if (bVar1 == 0) {
          uVar9 = 0x000f558fu;
          goto LAB_f7c6;
        }
        bVar12 = *(u8*)((long)param_2 + 0x11);
        iVar11 = iVar5 + uVar4 * 0x10;
        if (bVar12 != 0) bVar12 = 1;
        *(volatile u32*)(long)(iVar11 + 0x518) =
            (*(volatile u32*)(long)(iVar11 + 0x518) & 0xfeffffffu) | ((u32)bVar12 << 0x18);
        *(volatile u32*)(long)(iVar5 + (uVar4 + 0x51) * 0x10) = (u32)bVar1;
        uVar6 = (uVar6 + 1) & 0xff;
      }
      iVar11 = 0x5000e000;
      uVar4 = uVar4 + 1;
    } while (uVar4 != 8);

    switch ((u32)*(u8*)(param_2 + 4)) {
      case 8: uVar9 = 0; break;
      default:
        uVar9 = 0x000f55a9u;
        uVar4 = (u32)*(u8*)(param_2 + 4);
        goto LAB_f7c6;
      case 10: uVar9 = 1; break;
      case 0xc: uVar9 = 2; break;
      case 0xe: uVar9 = 3; break;
    }
    *(volatile u32*)(0x5000e000L + 0x5f0) = (u32)uVar9;
    uVar4 = (u32)*(u8*)((long)param_2 + 0x11);
    if (1 < uVar6) {
      uVar9 = 0x000f55ceu;
      if (uVar4 != 0) goto LAB_f782;
LAB_f874:
      *(volatile u32*)(long)(iVar11 + 0x5f4) = uVar4;
      puVar3i = (int*)0x20002190L;
      iVar5 = 0x5000e000;
      uVar10 = uVar6 * 2;
      if (*param_2 != 0) {
        uVar10 = (u32)(*(volatile u16*)((long)*param_2 + 0xc)) * uVar10 + uVar10;
      }
      if ((u32)param_2[3] < uVar10) {
        FUN_0004d944(0x000880e0u, 0x2040u, 0, 0);
        uVar9 = 0xfffffff4u;
        goto LAB_f7d6;
      }
      *(volatile int*)(0x5000e000L + 0x62c) = param_2[2];
      *(volatile u32*)(long)(iVar5 + 0x630) = uVar6;
      iVar5 = param_2[1];
      iVar7 = param_2[2];
      iVar11 = param_2[3];
      puVar3i[0x1d] = *param_2;
      puVar3i[0x1e] = iVar5;
      puVar3i[0x1f] = iVar7;
      puVar3i[0x20] = iVar11;
      puVar3i[0x21] = param_2[4];
      puVar3i[0x1c] = 0;
      param_2 = (int *)(long)*param_2;
      if (param_2 == 0) {
LAB_f948:
        r = FUN_0005f638(0x20002190u);
        uVar9 = (u32)(r >> 32);
      } else {
        int iVar8;
        iVar5 = *param_2;
        iVar7 = param_2[1];
        iVar11 = param_2[2];
        iVar8 = param_2[3];
        puVar3i[0x22] = iVar5;
        puVar3i[0x23] = iVar7;
        puVar3i[0x24] = iVar11;
        puVar3i[0x25] = iVar8;
        puVar3i[0x1d] = (int)(long)(puVar3i + 0x22);
        *(volatile u16*)(long)(puVar3i + 0x26) = 0;
        if (iVar5 == 0) goto LAB_f948;
        *puVar3i = 0;
        {
          long long lVar2 = (long long)(u32)puVar3i[0x22] * 0x8000LL + (long long)0x000f423fL;
          r = FUN_0000e244((int)lVar2, (int)(lVar2>>32), 0x000f4240u, 0);
          r = FUN_00075174((void*)(puVar3i + 2), (int)(r>>32), 0, 0);
          uVar9 = (u32)(r>>32);
        }
      }
      iVar5 = FUN_00072908(0x200021e8u, (void*)(long)uVar9, 0xffffffffu, 0xffffffffu);
      if (iVar5 != 0) {
        puVar3i[0x1c] = iVar5;
      }
      uVar9 = (u32)puVar3i[0x1c];
      goto LAB_f7d6;
    }
    uVar9 = 0x000f5600u;
    if (uVar4 < 9) goto LAB_f874;
LAB_f7c6:
    FUN_0004d944(0x000880e0u, 0x1840u, 0, 0);
  } else {
LAB_f782:
    FUN_0004d944(0x000880e0u, 0x1040u, 0, 0);
  }
  uVar9 = 0xffffffeau;
LAB_f7d6:
  FUN_00072880(0x200021d0u);
  return uVar9;
}

