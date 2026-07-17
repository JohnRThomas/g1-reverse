/* readable reconstruction; identity: FUN_000113a8 @ 0x000113a8
 * public-name: printf_like
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   _ldiv5                                   <= FUN_0007e260 @ 0x0007e260
 *   _get_digit                               <= FUN_0007e290 @ 0x0007e290
 *   outs                                     <= FUN_0007e2be @ 0x0007e2be
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_f8a6a                             @ 0x000f8a6a
 *   rodata_f8a6b                             @ 0x000f8a6b
 */
/* Reconstructed printf_like @ 0x113a8  (parity: 120/120 trials, PROVEN) */
#include <stdint.h>
#pragma GCC diagnostic warning "-Wint-conversion"
#pragma GCC diagnostic warning "-Wimplicit-int"
#pragma GCC diagnostic warning "-Wimplicit-function-declaration"
#pragma GCC diagnostic warning "-Wint-to-pointer-cast"
#pragma GCC diagnostic warning "-Wpointer-to-int-cast"
#pragma GCC diagnostic warning "-Wincompatible-pointer-types"
#pragma GCC diagnostic warning "-Wdiscarded-qualifiers"
typedef uint8_t undefined1; typedef uint8_t byte; typedef uint8_t undefined; typedef uint8_t uchar;
typedef uint16_t undefined2; typedef uint16_t ushort; typedef uint16_t wchar_t;
typedef uint32_t undefined4; typedef uint32_t uint;
typedef int code(int,uint32_t);
typedef uint64_t undefined8; typedef uint64_t ulonglong;
typedef int64_t longlong; typedef int32_t int32; typedef unsigned int uint3;
static inline int CARRY4(uint a, uint b){return (a+b)<a;}
static inline int CARRY1(uint a, uint b){return ((a&0xff)+(b&0xff))>0xff;}
static inline int CARRY2(uint a, uint b){return ((a&0xffff)+(b&0xffff))>0xffff;}
static inline int SBORROW4(int a,int b){int r=(int)((uint)a-(uint)b);return (((a^b)&(a^r))<0);}
static inline int SBORROW1(int a,int b){signed char r=(signed char)(a-b);return ((((signed char)a^(signed char)b)&((signed char)a^r))<0);}
static inline int SBORROW2(int a,int b){short r=(short)(a-b);return ((((short)a^(short)b)&((short)a^r))<0);}
#define CONCAT11(a,b) ((ushort)(((ushort)(uint8_t)(a)<<8)|(uint8_t)(b)))
#define CONCAT22(a,b) ((uint)(((uint)(ushort)(a)<<16)|(ushort)(b)))
#define CONCAT44(a,b) ((ulonglong)(((ulonglong)(uint)(a)<<32)|(uint)(b)))
#define CONCAT13(a,b) ((uint)(((uint)(uint8_t)(a)<<24)|((uint)(b)&0xffffff)))
#define CONCAT31(a,b) ((uint)(((uint)(a)<<8)|(uint8_t)(b)))
#define CONCAT12(a,b) ((uint)(((uint)(uint8_t)(a)<<16)|(ushort)(b)))
#define CONCAT21(a,b) ((uint)(((uint)(ushort)(a)<<8)|(uint8_t)(b)))
#define CONCAT111(a,b,c) ((uint)(((uint)(uint8_t)(a)<<16)|((uint)(uint8_t)(b)<<8)|(uint8_t)(c)))
#define CONCAT411(a,b,c) ((ulonglong)(((ulonglong)(uint)(a)<<16)|((uint)(uint8_t)(b)<<8)|(uint8_t)(c)))
#define SUB84(x,o) ((uint)((ulonglong)(x)>>((o)*8)))
#define SUB82(x,o) ((ushort)((ulonglong)(x)>>((o)*8)))
#define SUB81(x,o) ((uint8_t)((ulonglong)(x)>>((o)*8)))
#define SUB41(x,o) ((uint8_t)((uint)(x)>>((o)*8)))
#define SUB42(x,o) ((ushort)((uint)(x)>>((o)*8)))
#define SUB21(x,o) ((uint8_t)((ushort)(x)>>((o)*8)))
#define SUBF(v,o,s) ((ulonglong)((ulonglong)(v)>>((o)*8)) & ((s)>=8?~0ULL:((1ULL<<((s)*8))-1)))
#define NAN (__builtin_nanf(""))
#define INFINITY (__builtin_inff())

extern long long strlen(int, ...);
extern long long FUN_0004bb64(int, ...);
extern long long FUN_0004bb90(int, ...);
extern long long _ldiv5(int, ...);
extern long long _get_digit(int, ...);
extern long long outs(int, ...);
extern long long memset_bytes(int, ...);
extern long long FUN_000870a6(int, ...);
static inline int SCARRY4(int a, int b) { int r = (int)((uint)a + (uint)b); return ((a ^ r) & (b ^ r)) < 0; }

#define DAT_00011dd0 (0x0UL)
#define DAT_00011dd8 (0xf8a6aUL)
#define DAT_00012074 ((volatile byte*)0xf0981UL)
#define DAT_00012078 (0xf8a6bUL)


byte * printf_like(code *param_1,undefined4 param_2,byte *param_3,uint *param_4)

{
  ulonglong uVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  char cVar6;
  ushort uVar7;
  ushort uVar8;
  undefined1 uVar9;
  byte bVar10;
  byte *pbVar11;
  uint uVar12;
  byte *pbVar13;
  uint uVar14;
  byte *pbVar15;
  uint uVar16;
  byte bVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  byte *pbVar21;
  undefined4 uVar22;
  int iVar23;
  byte *pbVar24;
  uint *puVar25;
  uint *puVar26;
  undefined4 *puVar27;
  byte *pbVar28;
  int iVar29;
  byte *pbVar30;
  bool bVar31;
  undefined8 uVar32;
  byte *local_90;
  byte *local_8c;
  byte *local_88;
  uint local_74;
  uint local_70;
  uint local_6c;
  undefined8 local_68;
  byte *local_60;
  uint local_5c;
  undefined2 local_58;
  undefined2 local_56;
  byte *local_54;
  byte *local_50;
  byte local_44 [25];
  byte abStack_2b [7];

  pbVar28 = (byte *)0x0;
  do {
    bVar10 = *param_3;
    if (bVar10 == 0) {
      return pbVar28;
    }
    local_88 = param_3 + 1;
    if (bVar10 != 0x25) {
LAB_000113cc:
      pbVar11 = (byte *)(*param_1)(bVar10,param_2);
      if ((int)pbVar11 < 0) {
        return pbVar11;
      }
      pbVar28 = pbVar28 + 1;
      goto switchD_0001194e_caseD_59;
    }
    memset_bytes(&local_60,0,0x18);
    local_60 = (byte *)0;
    local_5c = 0;
    local_58 = 0;
    local_56 = 0;
    local_54 = (byte *)0;
    local_50 = (byte *)0;
    if (param_3[1] == 0x25) {
      local_88 = param_3 + 2;
      local_56 = CONCAT11(0x25,(byte)local_56);
    }
    else {
      bVar31 = false;
      bVar2 = false;
      bVar3 = false;
      bVar4 = false;
      bVar5 = false;
      pbVar11 = param_3 + 1;
      while( true ) {
        while( true ) {
          while( true ) {
            while( true ) {
              pbVar15 = pbVar11 + 1;
              bVar10 = *pbVar11;
              if (bVar10 != 0x2b) break;
              bVar4 = true;
              pbVar11 = pbVar15;
            }
            if (0x2b < bVar10) break;
            if (bVar10 == 0x20) {
              bVar3 = true;
              pbVar11 = pbVar15;
            }
            else {
              if (bVar10 != 0x23) goto LAB_00011412;
              bVar2 = true;
              pbVar11 = pbVar15;
            }
          }
          if (bVar10 != 0x2d) break;
          bVar5 = true;
          pbVar11 = pbVar15;
        }
        if (bVar10 != 0x30) break;
        bVar31 = true;
        pbVar11 = pbVar15;
      }
LAB_00011412:
      if (bVar31) {
        local_58 = local_58 | 0x40;
      }
      if (bVar2) {
        local_58 = local_58 | 0x20;
      }
      if (bVar3) {
        local_58 = local_58 | 0x10;
      }
      if (bVar4) {
        local_58 = local_58 | 8;
      }
      if (bVar5) {
        local_58 = local_58 | 4;
      }
      if (((byte)local_58 & 0x44) == 0x44) {
        local_58 = local_58 & 0xffbf;
      }
      local_68 = CONCAT44((*(volatile uint32_t*)((char*)&local_68 + 4)),pbVar11);
      uVar9 = (*(volatile uint8_t*)((char*)&local_58 + 1));
      local_58 = local_58 | 0x80;
      if (bVar10 == 0x2a) {
        local_58 = CONCAT11(uVar9,(byte)local_58) | 0x100;
        pbVar15 = pbVar11 + 1;
      }
      else {
        pbVar30 = (byte *)FUN_0004bb64(&local_68);
        pbVar15 = (byte *)local_68;
        if ((byte *)local_68 != pbVar11) {
          local_58 = CONCAT11((*(volatile uint8_t*)((char*)&local_58 + 1)),
                              (byte)local_58 & 0xfd | (byte)(((uint)pbVar30 >> 0x1f) << 1));
          local_54 = pbVar30;
        }
      }
      bVar10 = (*(volatile uint8_t*)((char*)&local_58 + 1)) & 0xfd | (*pbVar15 == 0x2e) << 1;
      (*(volatile uint8_t*)((char*)&local_58 + 1)) = bVar10;
      if (*pbVar15 == 0x2e) {
        local_68 = CONCAT44((*(volatile uint32_t*)((char*)&local_68 + 4)),pbVar15 + 1);
        if (pbVar15[1] == 0x2a) {
          (*(volatile uint8_t*)((char*)&local_58 + 1)) = bVar10 | 4;
          pbVar15 = pbVar15 + 2;
        }
        else {
          local_50 = (byte *)FUN_0004bb64(&local_68);
          (*(volatile uint8_t*)((char*)&local_58 + 0)) =
               (byte)local_58 & 0xfd |
               (byte)((((uint)(byte)local_58 << 0x1e | (uint)local_50) >> 0x1f) << 1);
          pbVar15 = (byte *)local_68;
        }
      }
      bVar10 = *pbVar15;
      if (bVar10 == 0x6c) {
        if (pbVar15[1] != 0x6c) {
          iVar29 = 3;
          goto LAB_0001163e;
        }
        iVar29 = 4;
LAB_00011630:
        (*(volatile uint8_t*)((char*)&local_58 + 1)) = (*(volatile uint8_t*)((char*)&local_58 + 1)) & 0x87 | (byte)(iVar29 << 3);
        pbVar15 = pbVar15 + 2;
      }
      else {
        if (bVar10 < 0x6d) {
          if (bVar10 == 0x68) {
            if (pbVar15[1] == 0x68) {
              iVar29 = 1;
              goto LAB_00011630;
            }
            iVar29 = 2;
            goto LAB_0001163e;
          }
          if (bVar10 == 0x6a) {
            iVar29 = 5;
            goto LAB_0001163e;
          }
          if (bVar10 != 0x4c) goto LAB_000114ea;
          (*(volatile uint8_t*)((char*)&local_58 + 0)) = (byte)local_58 & 0xfd | 2;
          (*(volatile uint8_t*)((char*)&local_58 + 1)) = (*(volatile uint8_t*)((char*)&local_58 + 1)) & 0x87 | 0x40;
        }
        else {
          if (bVar10 == 0x74) {
            iVar29 = 7;
          }
          else {
            if (bVar10 != 0x7a) goto LAB_000114ea;
            iVar29 = 6;
          }
LAB_0001163e:
          (*(volatile uint8_t*)((char*)&local_58 + 1)) = (*(volatile uint8_t*)((char*)&local_58 + 1)) & 0x87 | (byte)(iVar29 << 3);
        }
        pbVar15 = pbVar15 + 1;
      }
LAB_000114ea:
      local_88 = pbVar15 + 1;
      bVar10 = *pbVar15;
      uVar18 = (uint)bVar10;
      local_56 = CONCAT11(bVar10,(byte)local_56);
      if (0x78 < uVar18) goto LAB_000116fc;
      if (uVar18 < 0x6e) {
        if (uVar18 < 0x6a) {
          if (0x57 < uVar18) {
            uVar19 = 1 << (uVar18 - 0x58 & 0xff);
            if ((uVar19 & 0xe200) != 0) goto LAB_0001151a;
            if ((uVar19 & 0x801) != 0) {
              uVar19 = (*(volatile uint8_t*)((char*)&local_58 + 1)) & 0x78;
              local_56 = local_56 & 0xfff8 | 2;
              if (uVar19 == 0x40) {
                (*(volatile uint8_t*)((char*)&local_58 + 0)) = (byte)local_58 | 1;
              }
              if (uVar18 == 99) {
                if (((*(volatile uint8_t*)((char*)&local_58 + 1)) & 0x78) != 0) {
                  uVar19 = 1;
                }
                goto LAB_00011744;
              }
              goto LAB_0001155a;
            }
            if ((uVar19 & 0x21000) != 0) {
              bVar17 = (byte)local_56 & 0xf8 | 1;
              goto LAB_000116ee;
            }
            goto LAB_000116fc;
          }
          if ((uVar18 != 0x41) && (2 < uVar18 - 0x45)) goto LAB_000116fc;
LAB_0001151a:
          uVar18 = (uint)((uVar18 & 0xdf) == 0x41) << 7;
          uVar19 = (*(volatile uint8_t*)((char*)&local_58 + 1)) & 0xffffff7f;
          uVar16 = uVar19 | uVar18;
          local_56 = local_56 & 0xfff8 | 4;
          bVar10 = (byte)uVar16;
          if ((int)(uVar16 << 0x18) < 0) {
            uVar19 = 1;
            (*(volatile uint8_t*)((char*)&local_58 + 1)) = bVar10;
            goto LAB_00011744;
          }
          if (((*(volatile uint8_t*)((char*)&local_58 + 1)) & 0x78) == 0x18) {
            (*(volatile uint8_t*)((char*)&local_58 + 1)) = (byte)uVar19 & 0x87 | (byte)uVar18;
          }
          else {
            bVar17 = (*(volatile uint8_t*)((char*)&local_58 + 1)) & 0x38;
            (*(volatile uint8_t*)((char*)&local_58 + 1)) = bVar10;
            if (bVar17 != 0) goto LAB_000116fc;
          }
        }
        else {
LAB_000116fc:
          (*(volatile uint8_t*)((char*)&local_58 + 0)) = (byte)local_58 | 1;
        }
LAB_0001155a:
        uVar19 = 0;
      }
      else {
        uVar18 = 1 << (uVar18 - 0x6e & 0xff);
        if ((uVar18 & 0x482) != 0) {
          bVar17 = (byte)local_56 & 0xf8 | 2;
LAB_000116ee:
          local_56 = CONCAT11(bVar10,bVar17);
          if (((*(volatile uint8_t*)((char*)&local_58 + 1)) & 0x78) == 0x40) goto LAB_000116fc;
          goto LAB_0001155a;
        }
        if ((uVar18 & 0x24) == 0) {
          if (-1 < (int)(uVar18 << 0x1f)) goto LAB_000116fc;
          local_56 = local_56 & 0xfff8 | 3;
          uVar19 = (uint)(((*(volatile uint8_t*)((char*)&local_58 + 1)) & 0x78) == 0x40);
        }
        else {
          uVar19 = (uint)(((*(volatile uint8_t*)((char*)&local_58 + 1)) & 0x78) != 0);
          local_56 = local_56 & 0xfff8 | 3;
        }
      }
LAB_00011744:
      local_58 = CONCAT11((*(volatile uint8_t*)((char*)&local_58 + 1)),
                          (byte)local_58 & 0xfd |
                          (byte)((uVar19 & 1 | ((uint)(byte)local_58 << 0x1e) >> 0x1f) << 1));
    }
    uVar18 = (uint)(*(volatile uint8_t*)((char*)&local_58 + 1));
    if ((int)(uVar18 << 0x1f) < 0) {
      local_90 = (byte *)*param_4;
      puVar26 = param_4 + 1;
      if ((int)local_90 < 0) {
        local_58 = local_58 | 4;
        local_90 = (byte *)-(int)local_90;
      }
    }
    else {
      puVar26 = param_4;
      local_90 = local_54;
      if (-1 < (char)(byte)local_58) {
        local_90 = (byte *)0xffffffff;
      }
    }
    if ((int)(uVar18 << 0x1d) < 0) {
      puVar25 = puVar26 + 1;
      pbVar11 = (byte *)*puVar26;
      puVar26 = puVar25;
      if ((int)pbVar11 < 0) {
        local_58 = local_58 & 0xfdff;
LAB_000115a8:
        pbVar11 = (byte *)0xffffffff;
      }
    }
    else {
      pbVar11 = local_50;
      if (-1 < (int)(uVar18 << 0x1e)) goto LAB_000115a8;
    }
    uVar8 = local_58;
    local_54 = (byte *)0x0;
    local_50 = (byte *)0x0;
    if ((((byte)local_56 & 7) == 4) && (-1 < (int)((uint)(*(volatile uint8_t*)((char*)&local_58 + 1)) << 0x1e))) {
      if ((short)local_58 < 0) {
        pbVar11 = (byte *)0xd;
      }
      else {
        pbVar11 = (byte *)0x6;
      }
    }
    bVar10 = (byte)local_56 & 7;
    uVar18 = ((uint)(*(volatile uint8_t*)((char*)&local_58 + 1)) << 0x19) >> 0x1c;
    if (bVar10 == 1) {
      switch(uVar18) {
      case 3:
      case 6:
      case 7:
        local_60 = (byte *)*puVar26;
        local_5c = (int)local_60 >> 0x1f;
LAB_0001181a:
        param_4 = puVar26 + 1;
        break;
      case 4:
      case 5:
switchD_000117ce_caseD_4:
        puVar27 = (undefined4 *)((int)puVar26 + 7U & 0xfffffff8);
        param_4 = puVar27 + 2;
        local_60 = (byte *)*puVar27;
        local_5c = puVar27[1];
        break;
      default:
        pbVar15 = (byte *)*puVar26;
        local_5c = (int)pbVar15 >> 0x1f;
        if (uVar18 == 1) {
          (*(volatile uint8_t*)((char*)&local_60 + 0)) = (char)pbVar15;
          local_5c = (int)(char)local_60 >> 0x1f;
          local_60 = (byte *)(int)(char)local_60;
        }
        else {
          local_60 = pbVar15;
          if (uVar18 == 2) {
            local_60 = (byte *)(int)(short)pbVar15;
            local_5c = ((int)pbVar15 << 0x10) >> 0x1f;
          }
        }
        param_4 = puVar26 + 1;
      }
    }
    else if (bVar10 == 2) {
      switch(uVar18) {
      case 3:
      case 6:
      case 7:
        param_4 = puVar26 + 1;
        local_60 = (byte *)*puVar26;
        local_5c = 0;
        break;
      case 4:
      case 5:
        goto switchD_000117ce_caseD_4;
      default:
        local_5c = 0;
        local_60 = (byte *)*puVar26;
        if (uVar18 == 1) {
          local_60 = (byte *)((uint)local_60 & 0xff);
          goto LAB_0001181a;
        }
        local_5c = 0;
        param_4 = puVar26 + 1;
        if (uVar18 == 2) {
          local_60 = (byte *)((uint)local_60 & 0xffff);
          goto LAB_0001185a;
        }
      }
    }
    else if (bVar10 == 4) {
      puVar27 = (undefined4 *)((int)puVar26 + 7U & 0xfffffff8);
      local_60 = (byte *)*puVar27;
      local_5c = puVar27[1];
      param_4 = puVar27 + 2;
    }
    else {
      param_4 = puVar26;
      if (bVar10 == 3) {
        local_60 = (byte *)*puVar26;
LAB_0001185a:
        param_4 = puVar26 + 1;
      }
    }
    pbVar15 = local_60;
    uVar19 = (uint)(byte)local_58;
    if ((local_58 & 3) != 0) {
      pbVar11 = (byte *)outs(param_1,param_2,param_3,local_88);
      if ((int)pbVar11 < 0) {
        return pbVar11;
      }
      pbVar28 = pbVar28 + (int)pbVar11;
      goto switchD_0001194e_caseD_59;
    }
    uVar16 = (uint)(*(volatile uint8_t*)((char*)&local_56 + 1));
    if (0x78 < uVar16) goto switchD_0001194e_caseD_59;
    if (uVar16 < 0x58) {
      if (uVar16 == 0x25) {
        bVar10 = 0x25;
        goto LAB_000113cc;
      }
      if ((0x24 < uVar16) && ((uVar16 == 0x41 || (uVar16 - 0x45 < 3))))
      goto switchD_0001194e_caseD_61;
      goto switchD_0001194e_caseD_59;
    }
    switch(uVar16) {
    case 0x58:
    case 0x6f:
    case 0x75:
    case 0x78:
      uVar18 = 0;
      goto LAB_00011aa2;
    case 0x61:
    case 0x65:
    case 0x66:
    case 0x67:
switchD_0001194e_caseD_61:
      if ((int)local_5c < 0) {
        uVar18 = 0x2d;
      }
      else if ((int)(uVar19 << 0x1c) < 0) {
        uVar18 = 0x2b;
      }
      else {
        uVar18 = ((uVar19 << 0x1b) >> 0x1f) << 5;
      }
      uVar12 = (local_5c << 1) >> 0x15;
      uVar20 = local_5c & 0xfffff;
      if (uVar12 == 0) {
        if (local_60 == (byte *)0x0 && uVar20 == 0) {
          bVar31 = false;
        }
        else {
          bVar31 = true;
        }
LAB_000118fc:
        local_6c = uVar20 << 0xb | (uint)local_60 >> 0x15;
        local_70 = (int)local_60 << 0xb;
        if (uVar16 == 0x46) {
          uVar16 = 0x66;
        }
        if ((uVar12 == 0 && local_70 == 0) && (local_6c == 0 && -1 < (int)uVar12)) {
          iVar29 = 0;
        }
        else {
          if (bVar31) {
            while( true ) {
              bVar31 = CARRY4(local_70,local_70);
              local_70 = local_70 * 2;
              local_6c = local_6c * 2 + (uint)bVar31;
              if ((int)local_6c < 0) break;
              uVar12 = uVar12 - 1;
            }
          }
          iVar29 = uVar12 - 0x3fe;
          local_6c = local_6c | 0x80000000;
        }
        bVar31 = false;
        pbVar15 = (byte *)0x0;
        uVar12 = local_70;
        uVar20 = local_6c;
        while (iVar29 + 2 < 0 != SCARRY4(iVar29,2)) {
          do {
            iVar23 = iVar29;
            uVar12 = uVar12 >> 1 | uVar20 << 0x1f;
            uVar20 = uVar20 >> 1;
            iVar29 = iVar23 + 1;
          } while (0x33333332 < uVar20);
          bVar31 = true;
          uVar1 = (ulonglong)uVar12;
          uVar12 = (uint)(uVar1 * 5);
          pbVar15 = pbVar15 + -1;
          uVar20 = (int)(uVar1 * 5 >> 0x20) + uVar20 * 5;
          iVar29 = iVar23 + 2;
        }
        if (bVar31) {
          local_70 = uVar12;
          local_6c = uVar20;
        }
        while (0 < iVar29) {
          bVar31 = 0xfffffffd < local_70;
          local_70 = local_70 + 2;
          local_6c = local_6c + bVar31;
          iVar29 = iVar29 + -1;
          pbVar15 = pbVar15 + 1;
          _ldiv5(&local_70);
          do {
            bVar31 = CARRY4(local_70,local_70);
            local_70 = local_70 * 2;
            local_6c = local_6c * 2 + (uint)bVar31;
            iVar29 = iVar29 + -1;
          } while (-1 < (int)local_6c);
        }
        uVar12 = -iVar29 + 4;
        uVar20 = local_6c >> (uVar12 & 0xff);
        uVar12 = local_70 >> (uVar12 & 0xff) | local_6c << (iVar29 + 0x1cU & 0xff) |
                 local_6c >> (-iVar29 - 0x1cU & 0xff);
        if ((uVar16 & 0xdf) == 0x47) {
          if (((int)(pbVar15 + 3) < 0 == SCARRY4((int)pbVar15,3)) && ((int)pbVar15 <= (int)pbVar11))
          {
            pbVar11 = pbVar11 + -(int)pbVar15;
            if ((int)((uint)(byte)local_58 << 0x1a) < 0) {
              local_8c = (byte *)0x0;
            }
            else {
              local_8c = pbVar11;
              if (pbVar11 != (byte *)0x0) {
                local_8c = (byte *)0x1;
              }
            }
            goto LAB_00011caa;
          }
          uVar16 = uVar16 - 2 & 0xff;
          if (((int)pbVar11 < 1) ||
             (pbVar11 = pbVar11 + -1, (int)((uint)(byte)local_58 << 0x1a) < 0)) {
            local_8c = (byte *)0x0;
          }
          else {
            local_8c = pbVar11;
            if (pbVar11 != (byte *)0x0) {
              local_8c = (byte *)0x1;
            }
          }
LAB_00011c54:
          pbVar30 = pbVar11 + 1;
LAB_00011cb4:
          if (0xf < (int)pbVar30) {
            pbVar30 = (byte *)0x10;
          }
        }
        else {
          local_8c = (byte *)0x0;
          if (uVar16 != 0x66) goto LAB_00011c54;
LAB_00011caa:
          pbVar30 = pbVar11 + (int)pbVar15;
          uVar16 = 0x66;
          if (-1 < (int)pbVar30) goto LAB_00011cb4;
          pbVar30 = (byte *)0x0;
        }
        local_68 = DAT_00011dd0;
        local_74 = 0x10;
        while( true ) {
          if (pbVar30 == (byte *)0x0) break;
          local_68 = CONCAT44((*(volatile uint32_t*)((char*)&local_68 + 4)) >> 1,
                              (uint)(byte *)local_68 >> 1 | (*(volatile uint32_t*)((char*)&local_68 + 4)) << 0x1f);
          pbVar30 = pbVar30 + -1;
          _ldiv5(&local_68);
        }
        uVar14 = (int)(byte *)local_68 + uVar12;
        local_6c = (*(volatile uint32_t*)((char*)&local_68 + 4)) + uVar20 + CARRY4((uint)(byte *)local_68,uVar12);
        local_70 = uVar14;
        if (0xfffffff < local_6c) {
          local_70 = uVar14 >> 1 | local_6c * -0x80000000;
          local_6c = local_6c >> 1;
          uVar14 = _ldiv5(&local_70);
          pbVar15 = pbVar15 + 1;
        }
        bVar10 = (byte)uVar14;
        pbVar24 = (byte *)(uVar19 & 0x20);
        if (uVar16 == 0x66) {
          if ((int)pbVar15 < 1) {
            uVar19 = 0x30;
            uVar32 = CONCAT44(0x30,uVar14);
            local_44[0] = 0x30;
            pbVar24 = pbVar15;
            if ((uVar8 & 0x20) == 0) {
              if ((int)pbVar11 < 1) goto LAB_0001206e;
              local_44[1] = 0x2e;
              uVar32 = CONCAT44(0x30,uVar14);
              if (pbVar15 != (byte *)0x0) goto LAB_00011d0e;
            }
            else {
              local_44[1] = 0x2e;
              uVar32 = CONCAT44(0x30,uVar14);
              if (pbVar15 != (byte *)0x0) {
                if ((int)pbVar11 < 1) {
                  pbVar30 = local_44 + 2;
                  goto LAB_00011dee;
                }
LAB_00011d0e:
                local_54 = (byte *)-(int)pbVar15;
                if ((int)pbVar11 <= -(int)pbVar15) {
                  local_54 = pbVar11;
                }
                pbVar11 = pbVar11 + -(int)local_54;
                uVar19 = (byte)local_56 & 0xffffffdf | (uint)(0 < (int)local_54) << 5;
                local_56 = CONCAT11((*(volatile uint8_t*)((char*)&local_56 + 1)),(char)uVar19);
                uVar32 = CONCAT44(uVar19,uVar14);
              }
            }
LAB_00011d30:
            local_44[1] = 0x2e;
            pbVar30 = local_44 + 2;
          }
          else {
            pbVar21 = local_44;
            do {
              uVar32 = CONCAT44(local_74,uVar14);
              pbVar30 = pbVar21;
              if ((int)local_74 < 1) break;
              uVar32 = _get_digit(&local_70,&local_74);
              uVar14 = (uint)uVar32;
              pbVar15 = pbVar15 + -1;
              pbVar30 = pbVar21 + 1;
              *pbVar21 = (byte)uVar32;
              pbVar21 = pbVar30;
            } while (pbVar15 != (byte *)0x0);
            uVar19 = (uint)((ulonglong)uVar32 >> 0x20);
            bVar10 = (byte)uVar32;
            local_54 = pbVar15;
            if ((uVar8 & 0x20) == 0) {
              if ((int)pbVar11 < 1) goto LAB_00011dee;
              uVar19 = 0x2e;
              *pbVar30 = 0x2e;
            }
            else {
              *pbVar30 = 0x2e;
            }
            uVar32 = CONCAT44(uVar19,(int)uVar32);
            pbVar30 = pbVar30 + 1;
            pbVar24 = (byte *)0x0;
          }
          while( true ) {
            uVar19 = (uint)((ulonglong)uVar32 >> 0x20);
            bVar10 = (byte)uVar32;
            if (((int)pbVar11 < 1) || ((int)local_74 < 1)) break;
            uVar32 = _get_digit(&local_70,&local_74);
            pbVar11 = pbVar11 + -1;
            *pbVar30 = (byte)uVar32;
            pbVar30 = pbVar30 + 1;
          }
        }
        else {
          uVar32 = _get_digit(&local_70,&local_74);
          local_44[0] = (byte)uVar32;
          if ((int)uVar32 != 0x30) {
            pbVar15 = pbVar15 + -1;
          }
          if (((uVar8 & 0x20) != 0) || (0 < (int)pbVar11)) {
            local_44[1] = 0x2e;
            pbVar24 = pbVar15;
            goto LAB_00011d30;
          }
LAB_0001206e:
          uVar19 = (uint)((ulonglong)uVar32 >> 0x20);
          bVar10 = (byte)uVar32;
          pbVar30 = local_44 + 1;
          pbVar24 = pbVar15;
        }
LAB_00011dee:
        if (local_8c != (byte *)0x0) {
          do {
            pbVar15 = pbVar30;
            pbVar30 = pbVar15 + -1;
          } while (pbVar15[-1] == 0x30);
          pbVar30 = pbVar15;
          pbVar11 = local_50;
          if (pbVar15[-1] == 0x2e) {
            pbVar30 = pbVar15 + -1;
          }
        }
        local_50 = pbVar11;
        if ((uVar16 & 0xdf) == 0x45) {
          if ((int)pbVar24 < 0) {
            pbVar24 = (byte *)-(int)pbVar24;
            bVar17 = 0x2d;
          }
          else {
            bVar17 = 0x2b;
          }
          if (99 < (int)pbVar24) {
            uVar19 = 100;
          }
          pbVar30[1] = bVar17;
          pbVar11 = pbVar24;
          if (99 < (int)pbVar24) {
            pbVar11 = pbVar24 + -(uVar19 * ((uint)pbVar24 / uVar19));
            bVar10 = (char)((uint)pbVar24 / uVar19) + 0x30;
          }
          if ((int)pbVar24 < 100) {
            pbVar15 = pbVar30 + 2;
          }
          else {
            pbVar15 = pbVar30 + 3;
          }
          if (99 < (int)pbVar24) {
            pbVar30[2] = bVar10;
          }
          *pbVar30 = (byte)uVar16;
          cVar6 = (char)((uint)pbVar11 / 10);
          pbVar30 = pbVar15 + 2;
          *pbVar15 = cVar6 + 0x30;
          pbVar15[1] = (char)pbVar11 + cVar6 * -10 + 0x30;
        }
        if ((int)local_54 < 1) {
          if ((int)local_50 < 1) {
            iVar29 = 0;
          }
          else {
            iVar29 = 1;
          }
        }
        else {
          iVar29 = 1;
        }
        local_56 = CONCAT11((*(volatile uint8_t*)((char*)&local_56 + 1)),(byte)local_56 & 0xbf | (byte)(iVar29 << 6));
        *pbVar30 = 0;
      }
      else {
        if (uVar12 != 0x7ff) {
          bVar31 = false;
          goto LAB_000118fc;
        }
        uVar20 = uVar20 | (uint)local_60;
        bVar10 = *(byte *)(DAT_00011dd8 + (uVar16 + 1 & 0xff)) & 3;
        if (uVar20 == 0) {
          if (bVar10 == 1) {
            local_44[0] = 0x49;
            pbVar11 = (byte *)0x4e;
          }
          else {
            local_44[0] = 0x69;
            pbVar11 = local_60;
          }
          local_44[1] = (byte)pbVar11;
          if (bVar10 == 1) {
            local_44[2] = 0x46;
          }
          else {
            local_44[1] = 0x6e;
            local_44[2] = 0x66;
          }
        }
        else {
          bVar31 = bVar10 != 1;
          if (bVar31) {
            uVar20 = 0x6e;
          }
          local_44[0] = (byte)uVar20;
          if (bVar31) {
            pbVar11 = (byte *)0x61;
          }
          else {
            local_44[0] = 0x4e;
            pbVar11 = local_60;
          }
          local_44[1] = (byte)pbVar11;
          local_44[2] = local_44[0];
          if (!bVar31) {
            local_44[1] = 0x41;
          }
        }
        local_58 = local_58 & 0xffbf;
        pbVar30 = local_44 + 3;
      }
      pbVar15 = local_44;
      goto LAB_00011b98;
    case 99:
      uVar18 = 0;
      local_44[0] = (byte)local_60;
      pbVar30 = local_44 + 1;
      iVar23 = 1;
      pbVar15 = local_44;
      goto LAB_000119fa;
    case 100:
    case 0x69:
      if ((int)(uVar19 << 0x1c) < 0) {
        uVar18 = 0x2b;
      }
      else {
        uVar18 = ((uVar19 << 0x1b) >> 0x1f) << 5;
      }
      if ((int)local_5c < 0) {
        uVar18 = 0x2d;
        bVar31 = local_60 != (byte *)0x0;
        local_60 = (byte *)-(int)local_60;
        local_5c = -local_5c - (uint)bVar31;
      }
LAB_00011aa2:
      pbVar15 = (byte *)FUN_0004bb90(local_60,local_5c,&local_58,local_44,abStack_2b);
LAB_00011ab6:
      if (-1 < (int)pbVar11) {
        local_58 = local_58 & 0xffbf;
        if (abStack_2b + -(int)pbVar15 < pbVar11) {
          local_54 = pbVar11 + -(int)(abStack_2b + -(int)pbVar15);
        }
      }
      if (pbVar15 != (byte *)0x0) {
        pbVar30 = abStack_2b;
LAB_00011b98:
        iVar23 = (int)pbVar30 - (int)pbVar15;
        if (uVar18 != 0) {
          iVar23 = iVar23 + 1;
        }
        goto LAB_000119fa;
      }
      break;
    case 0x6e:
      switch(uVar18) {
      case 0:
      case 3:
      case 6:
      case 7:
        *(byte **)local_60 = pbVar28;
        break;
      case 1:
        *local_60 = (byte)pbVar28;
        break;
      case 2:
        *(short *)local_60 = (short)pbVar28;
        break;
      case 4:
      case 5:
        *(byte **)local_60 = pbVar28;
        *(int *)(local_60 + 4) = (int)pbVar28 >> 0x1f;
      }
      break;
    case 0x70:
      if (local_60 == (byte *)0x0) {
        iVar23 = 5;
        pbVar15 = DAT_00012074 + -5;
        uVar18 = 0;
        pbVar30 = DAT_00012074;
        goto LAB_000119fa;
      }
      pbVar15 = (byte *)FUN_0004bb90(local_60,0,&local_58,local_44,abStack_2b);
      local_56 = local_56 & 0xef | 0x7810;
      uVar18 = 0;
      goto LAB_00011ab6;
    case 0x73:
      if ((int)pbVar11 < 0) {
        iVar29 = strlen(local_60);
      }
      else {
        iVar29 = FUN_000870a6(local_60,pbVar11);
        if (pbVar15 == (byte *)0x0) break;
      }
      uVar18 = 0;
      iVar23 = (int)(pbVar15 + iVar29) - (int)pbVar15;
      pbVar30 = pbVar15 + iVar29;
LAB_000119fa:
      pbVar11 = local_54;
      uVar8 = local_56 & 0x10;
      if ((local_56 & 0x10) == 0) {
        if ((int)((uint)(byte)local_56 << 0x1c) < 0) {
          iVar23 = iVar23 + 1;
        }
      }
      else {
        iVar23 = iVar23 + 2;
      }
      uVar7 = local_56 & 0x40;
      bVar31 = (local_56 & 0x40) != 0;
      pbVar24 = (byte *)((byte)local_56 & 0x40);
      if (bVar31) {
        pbVar24 = local_50;
      }
      pbVar21 = local_54 + iVar23;
      if (bVar31) {
        pbVar21 = pbVar21 + (int)pbVar24;
      }
      if (0 < (int)local_90) {
        pbVar24 = local_90 + -(int)pbVar21;
        uVar19 = (uint)(byte)local_58;
        local_90 = pbVar24;
        if (-1 < (int)(uVar19 << 0x1d)) {
          pbVar21 = pbVar24;
          if ((int)(uVar19 << 0x19) < 0) {
            if (uVar18 != 0) {
              pbVar13 = (byte *)(*param_1)(uVar18,param_2);
              if ((int)pbVar13 < 0) {
                return pbVar13;
              }
              pbVar28 = pbVar28 + 1;
              uVar18 = (uVar19 << 0x1d) >> 0x1f;
            }
            uVar22 = 0x30;
          }
          else {
            uVar22 = 0x20;
          }
          while (local_90 = pbVar21 + -1, 0 < (int)pbVar21) {
            pbVar13 = (byte *)(*param_1)(uVar22,param_2);
            pbVar21 = local_90;
            if ((int)pbVar13 < 0) {
              return pbVar13;
            }
          }
          pbVar28 = pbVar24 + ((int)pbVar28 - (int)pbVar21);
        }
      }
      if (uVar18 != 0) {
        pbVar24 = (byte *)(*param_1)(uVar18,param_2);
        if ((int)pbVar24 < 0) {
          return pbVar24;
        }
        pbVar28 = pbVar28 + 1;
      }
      iVar29 = DAT_00012078;
      if (uVar7 == 0) {
        if (((int)((uint)(byte)local_56 << 0x1b) < 0) || ((int)((uint)(byte)local_56 << 0x1c) < 0))
        {
          pbVar24 = (byte *)(*param_1)(0x30,param_2);
          if ((int)pbVar24 < 0) {
            return pbVar24;
          }
          pbVar28 = pbVar28 + 1;
        }
        pbVar24 = pbVar28;
        if (uVar8 != 0) {
          pbVar24 = (byte *)(*param_1)((*(volatile uint8_t*)((char*)&local_56 + 1)),param_2);
          if ((int)pbVar24 < 0) {
            return pbVar24;
          }
          pbVar28 = pbVar28 + 1;
          pbVar24 = pbVar28;
        }
        for (; 0 < (int)(pbVar11 + ((int)pbVar24 - (int)pbVar28)); pbVar28 = pbVar28 + 1) {
          pbVar21 = (byte *)(*param_1)(0x30,param_2);
          if ((int)pbVar21 < 0) {
            return pbVar21;
          }
        }
        pbVar11 = (byte *)outs(param_1,param_2,pbVar15,pbVar30);
        if ((int)pbVar11 < 0) {
          return pbVar11;
        }
        pbVar28 = pbVar11 + (int)pbVar28;
        pbVar11 = pbVar28;
      }
      else {
        pbVar24 = pbVar15;
        if ((short)local_58 < 0) {
          while( true ) {
            if (*pbVar24 == 0x70) break;
            pbVar11 = (byte *)(*param_1)(*pbVar24,param_2);
            pbVar24 = pbVar24 + 1;
            if ((int)pbVar11 < 0) {
              return pbVar11;
            }
          }
          iVar29 = (int)pbVar28 - (int)pbVar15;
        }
        else {
          while( true ) {
            if (-1 < (int)((uint)*(byte *)(iVar29 + (uint)*pbVar24) << 0x1d)) break;
            pbVar21 = (byte *)(*param_1)((uint)*pbVar24,param_2);
            pbVar24 = pbVar24 + 1;
            if ((int)pbVar21 < 0) {
              return pbVar21;
            }
          }
          pbVar21 = pbVar24 + ((int)pbVar28 - (int)pbVar15);
          pbVar28 = pbVar11;
          pbVar15 = pbVar11;
          if (-1 < (int)((uint)(byte)local_56 << 0x1a)) {
            while (pbVar15 = pbVar28 + -1, 0 < (int)pbVar28) {
              pbVar13 = (byte *)(*param_1)(0x30,param_2);
              pbVar28 = pbVar15;
              if ((int)pbVar13 < 0) {
                return pbVar13;
              }
            }
            pbVar21 = pbVar21 + ((int)pbVar11 - (int)pbVar28);
          }
          pbVar28 = pbVar24;
          if (*pbVar24 == 0x2e) {
            pbVar28 = (byte *)(*param_1)(0x2e,param_2);
            while( true ) {
              if ((int)pbVar28 < 0) {
      return pbVar28;
              }
              pbVar21 = pbVar21 + 1;
              if ((int)pbVar15 < 1) break;
              pbVar28 = (byte *)(*param_1)(0x30,param_2);
              pbVar15 = pbVar15 + -1;
            }
            pbVar24 = pbVar24 + 1;
            pbVar28 = pbVar24;
          }
          while( true ) {
            if (-1 < (int)((uint)*(byte *)(iVar29 + (uint)*pbVar24) << 0x1d)) break;
            pbVar11 = (byte *)(*param_1)((uint)*pbVar24,param_2);
            pbVar24 = pbVar24 + 1;
            if ((int)pbVar11 < 0) {
              return pbVar11;
            }
          }
          iVar29 = (int)pbVar21 - (int)pbVar28;
        }
        pbVar28 = local_50;
        for (pbVar11 = pbVar24 + iVar29; 0 < (int)(pbVar24 + iVar29 + ((int)pbVar28 - (int)pbVar11))
            ; pbVar11 = pbVar11 + 1) {
          pbVar15 = (byte *)(*param_1)(0x30,param_2);
          if ((int)pbVar15 < 0) {
            return pbVar15;
          }
        }
        pbVar28 = (byte *)outs(param_1,param_2,pbVar24,pbVar30);
        if ((int)pbVar28 < 0) {
          return pbVar28;
        }
        pbVar28 = pbVar28 + (int)pbVar11;
        pbVar11 = pbVar28;
      }
      for (; 0 < (int)(local_90 + ((int)pbVar11 - (int)pbVar28)); pbVar28 = pbVar28 + 1) {
        pbVar15 = (byte *)(*param_1)(0x20,param_2);
        if ((int)pbVar15 < 0) {
          return pbVar15;
        }
      }
    }
switchD_0001194e_caseD_59:
    param_3 = local_88;
  } while( true );
}
