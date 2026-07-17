/* readable reconstruction; identity: FUN_0102bbec @ 0x0102bbec
 * public-name: FUN_0102bbec
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d279                           @ 0x0103d279
 *   rodata_103d2a7                           @ 0x0103d2a7
 */
/* net-core FUN_0102bbec @ 0x102bbec  (parity 300 trials PROVEN) */
#include <stdint.h>
typedef uint8_t  byte;
typedef uint32_t uint;
typedef uint32_t undefined4;

extern int  FUN_0102a268(uint);
extern void FUN_0103b614(void*, uint);
extern void assert_print(uint, uint, uint);
extern void FUN_01039bb0(uint, uint);

#define DAT_0102beb0 0x0103be64u
#define DAT_0102beb4 0x0103ed24u
#define DAT_0102beb8 0x0103d279u
#define DAT_0102bebc 0x0103d2a7u
#define DAT_0102bfdc 0x0103d279u
#define DAT_0102bfe0 0x0103d2a7u

byte * FUN_0102bbec(undefined4 *param_1, byte *param_2, uint param_3, uint param_4, uint *param_5)
{
  int bVar1;
  byte bVar2;
  char cVar3;
  byte *pbVar4;
  byte *pbVar5;
  undefined4 uVar6;
  byte bVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint *puVar11;
  undefined4 *puVar12;
  uint *puVar13;
  uint uVar14;
  int iVar15;
  undefined4 *puVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint local_68;
  int local_54;

  byte local_48[16];
  byte abStack_38[20];

  uVar9 = param_3 & 4;
  local_54 = ((param_3 << 0x1a) >> 0x1d) + 1;
  if (((uintptr_t)param_1 & 3u) != 0) {
    return (byte *)0xfffffff2;
  }
  if (param_1 == (undefined4 *)0x0) {
    puVar11 = (uint *)(((uintptr_t)param_2 & 7u) + 4u);
    param_2 = (byte *)(8u - ((uintptr_t)param_2 & 7u));
  }
  else {
    puVar11 = param_1 + 1;
    if ((uintptr_t)param_2 < 8u) {   /* capacity is carried in pointer-width r1 */
      return (byte *)0xffffffe4;
    }
  }
  iVar15 = 0;
  uVar17 = 4;
  pbVar4 = (byte *)(param_4 - 1);
  uVar14 = 0;
  bVar7 = 0xff;
  uVar18 = 0;
  uVar10 = 4;
  cVar3 = '\0';
  local_68 = param_4;
LAB_0102bc4a:
  if (param_1 != (undefined4 *)0x0) {
    *puVar11 = local_68;
  }
  if ((local_54 < 1) && ((local_68 < DAT_0102beb0 || (DAT_0102beb4 <= local_68)))) {
    uVar19 = (uint)((uintptr_t)puVar11 - (uintptr_t)param_1);
    bVar2 = (byte)(uVar19 >> 2);
    if ((int)(param_3 << 0x1e) < 0) {
      bVar1 = 0;
      goto LAB_0102be18;
    }
    if (uVar14 < 0x10) {
      if (param_1 == (undefined4 *)0x0) {
LAB_0102bec0:
        param_2 = (byte *)((uintptr_t)param_2 + 2u);
        if (uVar9 == 0) {
          iVar8 = FUN_0102a268(local_68);
          param_2 = (byte *)((uintptr_t)param_2 + (uintptr_t)iVar8);
        }
      }
      else {
        local_48[uVar14] = bVar2;
        abStack_38[uVar14] = bVar7;
LAB_0102be4e:
        cVar3 = cVar3 + '\x01';
      }
LAB_0102be94:
      uVar14 = uVar14 + 1;
LAB_0102be96:
      puVar11 = puVar11 + 1;
      uVar19 = uVar18;
switchD_0102bcaa_caseD_4c:
      while (1) {
        while (1) {
          while (1) {
            pbVar5 = pbVar4;
            pbVar4 = pbVar5 + 1;
            bVar2 = *pbVar4;
            if (bVar2 == 0) {
              uVar10 = (uint)((uintptr_t)puVar11 - (uintptr_t)param_1);
              if (uVar10 < 0x400) {
                if (param_1 == (undefined4 *)0x0) {
                  return (byte *)((uintptr_t)param_2 + (uVar10 - 8u));
                }
                *param_1 = 0;
                *(char *)param_1 = (char)(uVar10 >> 2);
                if (uVar9 == 0) {
                *((char *)param_1 + 1) = cVar3;
                }
                else {
                  *((char *)param_1 + 3) = cVar3;
                }
                *((char *)param_1 + 2) = (char)iVar15;
                if (iVar15 != 0) {
                  pbVar4 = local_48;
                  for (uVar10 = 0; uVar14 != uVar10; uVar10 = uVar10 + 1) {
                    puVar13 = puVar11;
                    if ((int)((uint)*pbVar4 << 0x18) < 0) {
                      if ((uintptr_t)param_2 <
                          (uintptr_t)puVar11 + 1u - (uintptr_t)param_1) {
                        return (byte *)0xffffffe4;
                      }
                      puVar13 = (uint *)((byte *)puVar11 + 1);
                      *(byte *)puVar11 = *pbVar4 & 0x7f;
                    }
                    pbVar4 = pbVar4 + 1;
                    puVar11 = puVar13;
                  }
                }
                uVar10 = 0;
                pbVar4 = local_48;
                do {
                  if (uVar14 == uVar10) {
                    return (byte *)((uintptr_t)puVar11 - (uintptr_t)param_1);
                  }
                  if ((iVar15 == 0) || (-1 < (char)*pbVar4)) {
                    if (uVar9 == 0) {
                      local_68 = param_1[*pbVar4];
                      param_1[*pbVar4] = 0;
                      iVar8 = FUN_0102a268(local_68);
                      iVar8 = iVar8 + 1;
                    }
                    else {
                      *(byte *)puVar11 = abStack_38[uVar10];
                      iVar8 = 0;
                      puVar11 = (uint *)((byte *)puVar11 + 1);
                    }
                    if ((uintptr_t)param_2 < 1u - (uintptr_t)param_1 +
                        (uintptr_t)iVar8 + (uintptr_t)puVar11) {
                      return (byte *)0xffffffe4;
                    }
                    *(byte *)puVar11 = *pbVar4;
                    FUN_0103b614((byte *)puVar11 + 1, local_68);
                    puVar11 = (uint *)((byte *)puVar11 + 1 + iVar8);
                  }
                  uVar10 = uVar10 + 1;
                  pbVar4 = pbVar4 + 1;
                } while (1);
              }
              assert_print(DAT_0102bfe0, DAT_0102bfdc, 0x2d1);
              uVar6 = 0x2d1;
              goto LAB_0102be2e;
            }
            if (uVar19 != 0) break;
            if (bVar2 == 0x25) {
              uVar19 = 1;
              bVar7 = bVar7 + 1;
              goto switchD_0102bcaa_caseD_74;
            }
          }
          if (0x7a < bVar2) goto switchD_0102bcaa_caseD_4d;
          if (0x4b < bVar2) goto switchD_0102bcaa_switchD;
          if (0x47 < bVar2) goto switchD_0102bcaa_caseD_4d;
          if (bVar2 < 0x2a) break;
          uVar18 = 1u << (uint)(byte)(bVar2 - 0x2a);
          if ((uVar18 & 0xffda) == 0) {
            if ((uVar18 & 0x38800000) != 0) goto switchD_0102bcaa_caseD_61;
            uVar18 = uVar18 & 1;
            uVar19 = uVar18;
            if (uVar18 != 0) {
              uVar19 = 0;
              goto LAB_0102bd08;
            }
          }
        }
        if (bVar2 == 0x25) break;
        if (0x25 < bVar2) goto switchD_0102bcaa_caseD_4d;
        if (bVar2 != 0x20) {
          uVar19 = (uint)(bVar2 == 0x23);
        }
      }
      bVar7 = bVar7 - 1;
      goto switchD_0102bcaa_caseD_4d;
    }
  }
  else {
    if (-1 < (int)(param_3 << 0x1e)) goto LAB_0102be96;
    bVar1 = 1;
    uVar19 = (uint)((uintptr_t)puVar11 - (uintptr_t)param_1);
    bVar2 = (byte)(uVar19 >> 2);
LAB_0102be18:
    if (0x1ff < uVar19) {
      assert_print(DAT_0102bebc, DAT_0102beb8, 0x27b);
      uVar6 = 0x27b;
      goto LAB_0102be2e;
    }
    if (uVar14 < 0x10) {
      if (param_1 == (undefined4 *)0x0) {
        if (!bVar1) goto LAB_0102bec0;
        param_2 = (byte *)((uintptr_t)param_2 + 1u);
      }
      else {
        local_48[uVar14] = bVar2;
        abStack_38[uVar14] = bVar7;
        if (!bVar1) goto LAB_0102be4e;
        local_48[uVar14] = bVar2 | 0x80;
        iVar15 = iVar15 + 1;
      }
      goto LAB_0102be94;
    }
  }
  assert_print(DAT_0102bebc, DAT_0102beb8, 0x280);
  uVar6 = 0x280;
LAB_0102be2e:
  FUN_01039bb0(DAT_0102beb8, uVar6);
switchD_0102bcaa_switchD:
  switch (bVar2) {
  case 0x4c:
  case 0x68:
  case 0x6c:
    goto switchD_0102bcaa_caseD_4c;
  default:
switchD_0102bcaa_caseD_4d:
    uVar19 = 0;
    goto switchD_0102bcaa_caseD_4c;
  case 0x58:
  case 99:
  case 100:
  case 0x69:
  case 0x6f:
  case 0x75:
  case 0x78:
    if (*pbVar5 == 0x6c) {
      uVar19 = 0;
      if (pbVar5[-1] != 0x6c) break;
      uVar10 = 8;
      goto LAB_0102bd5c;
    }
    uVar19 = 0;
    uVar18 = uVar19;
    goto LAB_0102bd08;
  case 0x61:
  case 0x65:
  case 0x66:
  case 0x67:
switchD_0102bcaa_caseD_61:
    puVar16 = (undefined4 *)(((uintptr_t)param_5 + 7u) & ~(uintptr_t)7u);
    puVar12 = (undefined4 *)(((uintptr_t)puVar11 + 7u) & ~(uintptr_t)7u);
    param_5 = (uint *)(puVar16 + 2);
    uVar6 = puVar16[1];
    if (param_1 != (undefined4 *)0x0) {
      if ((uintptr_t)param_2 < 8u - (uintptr_t)param_1 + (uintptr_t)puVar12) {
        return (byte *)0xffffffe4;
      }
      *puVar12 = *puVar16;
      puVar12[1] = uVar6;
    }
    uVar19 = 0;
    puVar11 = (uint *)(puVar12 + 2);
  case 0x6a:
    uVar10 = 8;
    uVar17 = uVar10;
    goto switchD_0102bcaa_caseD_4c;
  case 0x6e:
  case 0x70:
    uVar19 = 0;
    break;
  case 0x73:
    break;
  case 0x74:
  case 0x7a:
switchD_0102bcaa_caseD_74:
    uVar10 = 4;
    uVar17 = uVar10;
    goto switchD_0102bcaa_caseD_4c;
  }
  uVar10 = 4;
LAB_0102bd5c:
  uVar17 = uVar10;
  uVar18 = 0;
LAB_0102bd08:
  puVar11 = (uint *)(((uintptr_t)puVar11 + (uVar17 - 1u)) &
                     ~((uintptr_t)uVar17 - 1u));
  if (param_1 == (undefined4 *)0x0) {
    if (uVar19 != 0) goto LAB_0102bdf8;
    if (uVar10 != 4) {
      if (uVar10 != 8) goto LAB_0102beda;
      param_5 = (uint *)(((uintptr_t)param_5 + 7u) & ~(uintptr_t)7u);
      goto LAB_0102bdd4;
    }
  }
  else {
    if ((uintptr_t)param_2 < (uintptr_t)uVar10 - (uintptr_t)param_1 +
        (uintptr_t)puVar11) {
      return (byte *)0xffffffe4;
    }
    if (uVar19 != 0) goto LAB_0102bdf8;
    if (uVar10 != 4) {
      if (uVar10 != 8) {
LAB_0102beda:
        assert_print(DAT_0102bfe0, DAT_0102bfdc, 0x2c5);
        uVar6 = 0x2c5;
        goto LAB_0102be2e;
      }
      param_5 = (uint *)(((uintptr_t)param_5 + 7u) & ~(uintptr_t)7u);
      uVar10 = param_5[1];
      *puVar11 = *param_5;
      puVar11[1] = uVar10;
LAB_0102bdd4:
      param_5 = param_5 + 2;
      uVar10 = 8;
      puVar11 = puVar11 + 2;
      uVar19 = uVar18;
      goto switchD_0102bcaa_caseD_4c;
    }
    *puVar11 = *param_5;
  }
  param_5 = param_5 + 1;
  uVar10 = 4;
  puVar11 = puVar11 + 1;
  uVar19 = uVar18;
  goto switchD_0102bcaa_caseD_4c;
LAB_0102bdf8:
  local_54 = local_54 + -1;
  local_68 = *param_5;
  param_5 = param_5 + 1;
  goto LAB_0102bc4a;
}
