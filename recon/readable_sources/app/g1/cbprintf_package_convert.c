#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_cbprintf_package_hdr__param_0128       [param_0128; library]
 * Raw function identity: 0x0004abc0.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0004abc0 @ 0x0004abc0
 * public-name: cbprintf_package_convert
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   cbprintf_package_convert                 <= FUN_0004abc0 @ 0x0004abc0
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   is_ptr                                   <= FUN_0007dc00 @ 0x0007dc00
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_88188                             @ 0x00088188
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f04ef                             @ 0x000f04ef
 *   rodata_f0584                             @ 0x000f0584   [INLINED -- G6 literal batch]
 *   rodata_f059f                             @ 0x000f059f
 *   rodata_f0642                             @ 0x000f0642   [INLINED -- G6 literal batch]
 *   rodata_f0661                             @ 0x000f0661
 */
/* Reconstructed FUN_0004abc0 @ 0x4abc0  (parity: 1/1 trials, PROVEN) */
typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned long uintptr_t;

extern int strlen(int);
extern void z_log_msg_runtime_create(unsigned int, unsigned int, unsigned int, unsigned int);
extern long long is_ptr(uint,uint);
extern void assert_post_action(uint,uint) __attribute__((noreturn));
extern void memcpy(int, int, int);

int cbprintf_package_convert(byte *param_1,int param_2,int (*param_3)(byte*,int,uint),
                 uint param_4,uint param_5,int param_6,uint param_7)
{
  byte bVar1, bVar2, bVar8;
  ushort sVar3;
  volatile byte *v1 = param_1;
  byte *pbVar4, *pbVar12, *pbVar13;
  int iVar5, iVar6, iVar15;
  uint uVar7, uVar10, uVar11, uVar14;
  uint uVar9;
  long long uVar17;
  uint local_78, local_68, local_64, local_5c, local_58, local_60;
  int local_74, local_6c;
  byte *local_70;
  int (*local_54)(byte*,int,uint);
  int bVar16;
  byte local_49;
  byte abStack_48[16];
  byte abStack_38[20];
  struct {
    uint type;
    uint label;
    uint context;
    uint value;
    ushort flags;
  } descriptor;

  local_60 = param_4;
  local_54 = param_3;
  if (param_1 == (byte *)0x0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"in_packaged != ((void *)0)") /*=0xf0584*/,((unsigned long)&rodata_f04ef) /*=0xf04ef*/,0x394);
    assert_post_action(((unsigned long)&rodata_f04ef) /*=0xf04ef*/,0x394);
  }
  bVar1 = v1[2];
  uVar14 = (uint)bVar1;
  local_68 = (param_5 >> 3) & 1;
  if (param_2 == 0) {
    bVar8 = v1[1];
    pbVar4 = param_1 + uVar14 + (uint)*v1 * 4;
    for (uVar10 = 0; uVar10 < bVar8; uVar10 = uVar10 + 1) {
      iVar15 = strlen(pbVar4 + 1);
      pbVar4 = pbVar4 + 1 + iVar15 + 1;
    }
    param_2 = (int)(pbVar4 - param_1);
  }
  local_64 = (uint)v1[3];
  uVar10 = uVar14;
  if ((uVar14 == 0) || (-1 < (int)(param_5 << 0x1f))) {
    if ((local_64 == 0) || (-1 < (int)(param_5 << 0x1e))) {
      if (local_54 == 0) {
        return param_2;
      }
      (*local_54)(param_1,param_2,local_60);
      return param_2;
    }
    local_58 = (uint)*v1;
    local_6c = local_58 << 2;
    local_5c = *(uint *)(param_1 + 4);
    pbVar4 = param_1 + local_58 * 4;
    if (local_54 == 0) {
      if (uVar14 == 0) {
        uVar10 = 0;
      }
      else {
        uVar10 = param_5 & 4;
        if (uVar10 != 0) {
          pbVar4 = pbVar4 + uVar14;
          uVar10 = 0;
        }
      }
      goto control_label_0004ac9c;
    }
    uVar11 = uVar14;
    if (uVar14 == 0) goto control_label_0004ada6;
    if ((param_5 & 4) == 0) {
      uVar10 = 0;
      uVar11 = 0;
      goto control_label_0004ada6;
    }
    pbVar13 = abStack_38;
    uVar10 = 0;
  }
  else {
    local_58 = (uint)*v1;
    local_5c = *(uint *)(param_1 + 4);
    local_6c = local_58 << 2;
    pbVar4 = param_1 + local_58 * 4;
    if (local_54 == 0) {
      uVar10 = 0;
      pbVar13 = pbVar4;
      while (pbVar4 + uVar14 != pbVar13) {
        iVar15 = strlen(*(void **)(param_1 + (uint)*pbVar13 * 4));
        if ((param_6 != 0) && (uVar10 < param_7)) {
          *(volatile short *)(uintptr_t)(param_6 + (int)(uVar10 * 2)) = (short)(iVar15 + 1);
          uVar10 = uVar10 + 1;
        }
        param_2 = param_2 + iVar15 + 1;
        pbVar13 = pbVar13 + 1;
      }
      pbVar4 = pbVar4 + uVar14;
control_label_0004ac9c:
      if ((param_5 & 5) == 0) {
        iVar15 = 2;
      }
      else {
        iVar15 = 1;
      }
      iVar6 = local_64 * 2;
      bVar16 = (param_5 & 2) != 0;
      pbVar13 = pbVar4;
control_label_0004acba:
      while(1) {
        if (pbVar13 == pbVar4 + iVar6) {
          return param_2;
        }
        pbVar12 = pbVar13 + 2;
        uVar14 = *(uint *)(param_1 + (uint)pbVar13[1] * 4);
        if ((0x879b0 <= uVar14) && (uVar14 < 0xf8d64)) break;
        if (local_68 != 0) {
          uVar17 = is_ptr(local_5c,*pbVar13);
          uVar9 = (uint)((unsigned long long)uVar17 >> 0x20);
          if ((int)uVar17 != 0) goto control_label_0004ace6;
        }
        pbVar13 = pbVar12;
        if (bVar16) {
control_label_0004ad68:
          iVar5 = strlen((void*)(uintptr_t)uVar14);
          if ((param_6 != 0) && (uVar10 < param_7)) {
            *(volatile short *)(uintptr_t)(param_6 + (int)(uVar10 * 2)) = (short)iVar5 + 1;
            uVar10 = uVar10 + 1;
          }
          param_2 = param_2 + iVar5;
          pbVar13 = pbVar12;
        }
      }
      if (local_68 != 0) {
        uVar17 = is_ptr(local_5c,*pbVar13);
        uVar9 = (uint)((unsigned long long)uVar17 >> 0x20);
        if ((int)uVar17 != 0) {
control_label_0004ace6:
          descriptor.type = 0x01000004;
          descriptor.label = ((unsigned long)&rodata_f059f) /*=0xf059f*/;
          descriptor.context = local_5c;
          descriptor.value = uVar9;
          descriptor.flags = 0x0200;
          z_log_msg_runtime_create(((unsigned long)&rodata_88188) /*=0x88188*/,0x2480,&descriptor,0);
          param_2 = param_2 + -2;
          pbVar13 = pbVar12;
          goto control_label_0004acba;
        }
      }
      if ((int)(param_5 << 0x1f) < 0) goto control_label_0004ad68;
      param_2 = param_2 - iVar15;
      pbVar13 = pbVar12;
      goto control_label_0004acba;
    }
    uVar11 = 0;
    pbVar13 = abStack_48;
  }
  memcpy(pbVar13,pbVar4,uVar14);
control_label_0004ada6:
  local_74 = local_64 << 1;
  local_70 = pbVar4 + uVar14 + local_64 * 2;
  local_78 = param_5 & 2;
  pbVar4 = pbVar4 + uVar14;
control_label_0004adbe:
  while(1) {
    do {
      if (pbVar4 == local_70) {
        local_5c = (uint)v1[1];
        bVar8 = 0;
        if (-1 < (int)(param_5 << 0x1e)) {
          bVar8 = (byte)(uVar11 >> 1);
        }
        if ((int)(param_5 << 0x1f) < 0) {
          bVar2 = 0;
        }
        else {
          bVar16 = (param_5 & 4) != 0;
          if (bVar16) {
            param_5 = uVar11;
          }
          bVar2 = (byte)param_5;
          if (!bVar16) {
            bVar2 = 0;
          }
        }
        v1[1] = (byte)((char)uVar10 + (char)v1[1]);
        v1[2] = bVar2;
        v1[3] = bVar8;
        iVar15 = (*local_54)(param_1,local_6c,local_60);
        if (iVar15 < 0) {
          return iVar15;
        }
        *v1 = (byte)local_58;
        v1[1] = (byte)local_5c;
        v1[2] = bVar1;
        v1[3] = (byte)local_64;
        iVar6 = (*local_54)(abStack_38,uVar11,local_60);
        if (iVar6 < 0) {
          return iVar6;
        }
        iVar5 = (*local_54)(pbVar4,((param_2 - (int)uVar14) - local_6c) - local_74,local_60);
        if (iVar5 < 0) {
          return iVar5;
        }
        uVar14 = 0;
        iVar5 = iVar6 + iVar15 + iVar5;
        while(1) {
          void *pv;
          if (uVar10 <= uVar14) {
            (*local_54)(0,0,local_60);
            return iVar5;
          }
          local_49 = abStack_48[uVar14];
          pv = *(void **)(param_1 + (uint)local_49 * 4);
          if (param_6 == 0) {
            sVar3 = 0;
          }
          else {
            sVar3 = *(ushort *)(uintptr_t)(param_6 + (int)(uVar14 * 2));
          }
          iVar15 = (*local_54)((byte*)&local_49,1,local_60);
          if (iVar15 < 0) break;
          if (sVar3 == 0) {
            sVar3 = (ushort)(strlen(pv) + 1);
          }
          iVar6 = (*local_54)((byte*)pv,sVar3,local_60);
          if (iVar6 < 0) {
            return iVar6;
          }
          iVar5 = iVar5 + iVar15 + iVar6;
          uVar14 = uVar14 + 1;
        }
        return iVar15;
      }
      pbVar13 = pbVar4 + 2;
      bVar8 = *pbVar4;
      bVar2 = pbVar4[1];
      pbVar4 = pbVar13;
      if ((0x879b0 <= *(uint *)(param_1 + (uint)bVar2 * 4)) &&
         (*(uint *)(param_1 + (uint)bVar2 * 4) < 0xf8d64)) goto control_label_0004aede;
    } while ((local_68 != 0) && (uVar17 = is_ptr(local_5c,bVar8), bVar8 = (byte)((unsigned long long)uVar17 >> 0x20), ((int)uVar17) != 0));
    if (local_78 != 0) {
      if (uVar10 < 0x10) goto control_label_0004af48;
      printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"scpy_cnt < sizeof(cpy_str_pos)") /*=0xf0642*/,((unsigned long)&rodata_f04ef) /*=0xf04ef*/,0x448);
      assert_post_action(((unsigned long)&rodata_f04ef) /*=0xf04ef*/,0x448);
    }
    if (0xf < uVar11) break;
    uVar7 = uVar11 + 1;
    abStack_38[uVar11] = bVar8;
    uVar11 = uVar11 + 2 & 0xff;
    abStack_38[uVar7 & 0xff] = bVar2;
  }
  printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f0661) /*=0xf0661*/,((unsigned long)&rodata_f04ef) /*=0xf04ef*/,1099);
  assert_post_action(((unsigned long)&rodata_f04ef) /*=0xf04ef*/,1099);
control_label_0004aede:
  if ((local_68 == 0) || (uVar17 = is_ptr(local_5c,bVar8), ((int)uVar17) == 0)) {
    if ((int)(param_5 << 0x1f) < 0) {
      if (0xf < uVar10) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"scpy_cnt < sizeof(cpy_str_pos)") /*=0xf0642*/,((unsigned long)&rodata_f04ef) /*=0xf04ef*/,0x43e);
        assert_post_action(((unsigned long)&rodata_f04ef) /*=0xf04ef*/,0x43e);
      }
control_label_0004af48:
      abStack_48[uVar10] = bVar2;
      uVar10 = uVar10 + 1 & 0xff;
    }
    else if ((int)(param_5 << 0x1d) < 0) {
      if (0xf < uVar11) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f0661) /*=0xf0661*/,((unsigned long)&rodata_f04ef) /*=0xf04ef*/,0x441);
        assert_post_action(((unsigned long)&rodata_f04ef) /*=0xf04ef*/,0x441);
      }
      abStack_38[uVar11] = bVar2;
      uVar11 = uVar11 + 1 & 0xff;
    }
  }
  goto control_label_0004adbe;
}
