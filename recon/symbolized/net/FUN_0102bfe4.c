#include "g1_net_symbols.h"
/* net-core FUN_0102bfe4 @ 0x102bfe4  (parity 300 trials PROVEN) */
typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned long long u64;
typedef int (*codefn)(uint, uint, uint);

extern void FUN_01039bbe(uint a, uint b, uint c);
extern void FUN_01039bb0(uint a, uint b);
extern int  FUN_0102a268(uint p);
extern u64  FUN_010396d0(uint a, uint b);
extern void FUN_0102e284(uint a, uint b, void *c, int d);
extern void FUN_0103b614(void *d, void *s, uint n);

int FUN_0102bfe4(byte *param_1, int param_2, codefn param_3, uint param_4,
                 uint param_5, int param_6, uint param_7)
{
  volatile byte *header = param_1;
  byte bVar1, bVar2, bVar9;
  unsigned short sVar3;
  byte *pbVar4, *pbVar6, *pbVar14, *local_6c;
  int iVar5, iVar7, iVar16;
  uint uVar8, uVar10, uVar11, uVar12, uVar13, uVar15;
  uint local_58, local_60, local_64, local_74, local_78;
  int local_68, local_70;
  uint local_5c;
  codefn local_54;
  byte local_49;
  byte abStack_48[16];
  byte abStack_38[20];
  u64 r;

  local_5c = param_4;
  local_54 = param_3;
  if (param_1 == (byte *)0) {
    FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d279) /*=0x103d279*/, 0x394);
    uVar10 = 0x394;
LAB_0102c006:
    FUN_01039bb0(((unsigned long)&rodata_103d279) /*=0x103d279*/, uVar10);
    /* FUN_01039bb0 is noreturn on HW; harness oracles it as returning, so
       control falls through into the body just as the original bytes do. */
  }
  bVar1 = param_1[2];
  uVar15 = (uint)bVar1;
  local_64 = (param_5 << 0x1c) >> 0x1f;
  if (param_2 == 0) {
    bVar9 = param_1[1];
    pbVar4 = param_1 + uVar15 + (uint)param_1[0] * 4;
    for (uVar12 = 0; uVar12 < bVar9; uVar12 = uVar12 + 1) {
      iVar16 = FUN_0102a268((uint)(pbVar4 + 1));
      pbVar4 = pbVar4 + 1 + iVar16 + 1;
    }
    param_2 = (int)pbVar4 - (int)param_1;
  }
  local_60 = (uint)param_1[3];
  uVar12 = uVar15;
  if ((uVar15 == 0) || (-1 < (int)(param_5 << 0x1f))) {
    if ((local_60 == 0) || (-1 < (int)(param_5 << 0x1e))) {
      if (local_54 == (codefn)0) return param_2;
      (*local_54)((uint)param_1, (uint)param_2, local_5c);
      return param_2;
    }
    local_6c = (byte *)(uint)param_1[0];
    local_68 = (int)local_6c << 2;
    local_58 = *(uint *)(param_1 + 4);
    pbVar4 = param_1 + (int)local_6c * 4;
    if (local_54 == (codefn)0) {
      if (uVar15 == 0) {
        uVar12 = 0;
      } else {
        uVar12 = param_5 & 4;
        if (uVar12 != 0) { pbVar4 = pbVar4 + uVar15; uVar12 = 0; }
      }
      goto LAB_0102c0b6;
    }
    uVar13 = uVar15;
    if (uVar15 == 0) goto LAB_0102c1c4;
    if ((param_5 & 4) == 0) { uVar12 = 0; uVar13 = 0; goto LAB_0102c1c4; }
    pbVar6 = abStack_38;
    uVar12 = 0;
  } else {
    local_58 = *(uint *)(param_1 + 4);
    local_6c = (byte *)(uint)param_1[0];
    local_68 = (int)local_6c << 2;
    pbVar4 = param_1 + (int)local_6c * 4;
    if (local_54 == (codefn)0) {
      uVar12 = 0;
      pbVar6 = pbVar4;
      while (pbVar4 + uVar15 != pbVar6) {
        iVar16 = FUN_0102a268(*(uint *)(param_1 + (uint)*pbVar6 * 4));
        if ((param_6 != 0) && (uVar12 < param_7)) {
          *(short *)(param_6 + uVar12 * 2) = (short)(iVar16 + 1);
          uVar12 = uVar12 + 1;
        }
        param_2 = param_2 + iVar16 + 1;
        pbVar6 = pbVar6 + 1;
      }
      pbVar4 = pbVar4 + uVar15;
LAB_0102c0b6:
      if ((param_5 & 5) == 0) iVar16 = 2; else iVar16 = 1;
      iVar7 = local_60 * 2;
      local_54 = (codefn)(unsigned long)(param_5 & 2);
      pbVar6 = pbVar4;
LAB_0102c0d4:
      while (1) {
        if (pbVar6 == pbVar4 + iVar7) return param_2;
        pbVar14 = pbVar6 + 2;
        uVar15 = *(uint *)(param_1 + (uint)pbVar6[1] * 4);
        if ((0x0103be64 <= uVar15) && (uVar15 < 0x0103ed24)) break;
        if (local_64 != 0) {
          r = FUN_010396d0(local_58, (uint)*pbVar6);
          uVar10 = (uint)(r >> 32);
          if ((int)r != 0) goto LAB_0102c100;
        }
        pbVar6 = pbVar14;
        if (local_54 != (codefn)0) goto LAB_0102c182;
        continue;
LAB_0102c182:
        iVar5 = FUN_0102a268(uVar15);
        if ((param_6 != 0) && (uVar12 < param_7)) {
          *(short *)(param_6 + uVar12 * 2) = (short)iVar5 + 1;
          uVar12 = uVar12 + 1;
        }
        param_2 = param_2 + iVar5;
        pbVar6 = pbVar14;
        continue;
      }
      /* in-range break */
      if (local_64 != 0) {
        r = FUN_010396d0(local_58, (uint)*pbVar6);
        uVar10 = (uint)(r >> 32);
        if ((int)r != 0) {
LAB_0102c100:
          {
            struct { uint m0; uint m4; uint m8; uint mc; unsigned short m10; } blk;
            blk.m0 = 0x01000004;
            blk.m4 = ((unsigned long)&rodata_103d2bf) /*=0x103d2bf*/;
            blk.m8 = local_58;
            blk.mc = uVar10;
            blk.m10 = 0x200;
            FUN_0102e284(((unsigned long)&rodata_103c04c) /*=0x103c04c*/, 0x2480, &blk, 0);
          }
          param_2 = param_2 + -2;
          pbVar6 = pbVar14;
          goto LAB_0102c0d4;
        }
      }
      if ((int)(param_5 << 0x1f) < 0) { pbVar6 = pbVar14; goto LAB_0102c182; }
      param_2 = param_2 - iVar16;
      pbVar6 = pbVar14;
      goto LAB_0102c0d4;
    }
    uVar13 = 0;
    pbVar6 = abStack_48;
  }
  FUN_0103b614(pbVar6, pbVar4, uVar15);
LAB_0102c1c4:
  local_70 = local_60 << 1;
  local_74 = param_5 & 2;
  uVar11 = (uint)local_6c;
  pbVar6 = pbVar4 + uVar15;
  local_6c = pbVar4 + uVar15 + local_60 * 2;
LAB_0102c1dc:
  if (pbVar6 == local_6c) {
    local_58 = (uint)param_1[1];
    bVar9 = 0;
    if (-1 < (int)(param_5 << 0x1e)) bVar9 = (byte)(uVar13 >> 1);
    if ((int)(param_5 << 0x1f) < 0) {
      bVar2 = 0;
    } else {
      int bv = ((param_5 & 4) != 0);
      if (bv) param_5 = uVar13;
      bVar2 = (byte)param_5;
      if (!bv) bVar2 = 0;
    }
    header[1] = (byte)((char)uVar12 + header[1]);
    header[2] = bVar2;
    header[3] = bVar9;
    local_64 = uVar11;
    iVar16 = (*local_54)((uint)param_1, (uint)local_68, local_5c);
    if (iVar16 < 0) return iVar16;
    header[0] = (byte)local_64;
    header[1] = (byte)local_58;
    header[2] = bVar1;
    header[3] = (byte)local_60;
    iVar7 = (*local_54)((uint)abStack_38, uVar13, local_5c);
    if (iVar7 < 0) return iVar7;
    iVar5 = (*local_54)((uint)pbVar6, (uint)(((param_2 - uVar15) - local_68) - local_70), local_5c);
    if (iVar5 < 0) return iVar5;
    uVar15 = 0;
    iVar5 = iVar7 + iVar16 + iVar5;
    while (1) {
      if (uVar12 <= uVar15) { (*local_54)(0, 0, local_5c); return iVar5; }
      local_49 = abStack_48[uVar15];
      uVar10 = *(uint *)(param_1 + (uint)local_49 * 4);
      if (param_6 == 0) sVar3 = 0; else sVar3 = *(unsigned short *)(param_6 + uVar15 * 2);
      iVar16 = (*local_54)((uint)&local_49, 1, local_5c);
      if (iVar16 < 0) return iVar16;
      if (sVar3 == 0) { sVar3 = (unsigned short)(FUN_0102a268(uVar10) + 1); }
      iVar7 = (*local_54)(uVar10, (uint)sVar3, local_5c);
      if (iVar7 < 0) return iVar7;
      iVar5 = iVar5 + iVar16 + iVar7;
      uVar15 = uVar15 + 1;
    }
  }
  pbVar4 = pbVar6 + 2;
  bVar9 = *pbVar6;
  bVar2 = pbVar6[1];
  pbVar6 = pbVar4;
  if ((0x0103be64 <= *(uint *)(param_1 + (uint)bVar2 * 4)) &&
      (*(uint *)(param_1 + (uint)bVar2 * 4) < 0x0103ed24)) goto LAB_0102c2fc;
  if (local_64 != 0) {
    local_78 = uVar11;
    r = FUN_010396d0(local_58, (uint)bVar9);
    iVar16 = (int)r;
    uVar11 = local_78;
    bVar9 = (byte)(r >> 32);
    if (iVar16 != 0) goto LAB_0102c1dc;
  }
  if (local_74 != 0) {
    if (uVar12 < 0x10) goto LAB_0102c366;
    FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d279) /*=0x103d279*/, 0x448);
    uVar10 = 0x448;
    goto LAB_0102c006;
  }
  if (0xf < uVar13) {
    FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d279) /*=0x103d279*/, 1099);
    uVar10 = 1099;
    goto LAB_0102c006;
  }
  uVar8 = uVar13 + 1;
  abStack_38[uVar13] = bVar9;
  uVar13 = uVar13 + 2 & 0xff;
  abStack_38[uVar8 & 0xff] = bVar2;
  goto LAB_0102c1dc;
LAB_0102c2fc:
  {
    int push_ok = (local_64 == 0);
    if (!push_ok) {
      local_78 = uVar11;
      r = FUN_010396d0(local_58, (uint)bVar9);
      iVar16 = (int)r;
      uVar11 = local_78;
      push_ok = (iVar16 == 0);
    }
    if (push_ok) {
      if ((int)(param_5 << 0x1f) < 0) {
        if (0xf < uVar12) {
          FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d279) /*=0x103d279*/, 0x43e);
          uVar10 = 0x43e;
          goto LAB_0102c006;
        }
LAB_0102c366:
        abStack_48[uVar12] = bVar2;
        uVar12 = uVar12 + 1 & 0xff;
      } else if ((int)(param_5 << 0x1d) < 0) {
        if (0xf < uVar13) {
          FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d279) /*=0x103d279*/, 0x441);
          uVar10 = 0x441;
          goto LAB_0102c006;
        }
        abStack_38[uVar13] = bVar2;
        uVar13 = uVar13 + 1 & 0xff;
      }
    }
  }
  goto LAB_0102c1dc;
}
