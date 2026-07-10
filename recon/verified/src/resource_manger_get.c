/* Reconstructed resource_manger_get @ 0x4588c  (parity: 120/120 trials, PROVEN) */
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
typedef long long code(int,...);
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

extern long long DEBUG_PRINT__impl(int, ...);
#define DEBUG_PRINT(...) DEBUG_PRINT__impl(0, ##__VA_ARGS__)
extern long long FUN_000167a8__impl(int, ...);
#define FUN_000167a8(...) FUN_000167a8__impl(0, ##__VA_ARGS__)
extern long long FUN_00019c70__impl(int, ...);
#define FUN_00019c70(...) FUN_00019c70__impl(0, ##__VA_ARGS__)
extern long long FUN_00045764__impl(int, ...);
#define FUN_00045764(...) FUN_00045764__impl(0, ##__VA_ARGS__)
extern long long FUN_000457b0__impl(int, ...);
#define FUN_000457b0(...) FUN_000457b0__impl(0, ##__VA_ARGS__)
extern long long FUN_000457f4__impl(int, ...);
#define FUN_000457f4(...) FUN_000457f4__impl(0, ##__VA_ARGS__)
extern long long FUN_00045840__impl(int, ...);
#define FUN_00045840(...) FUN_00045840__impl(0, ##__VA_ARGS__)
extern long long FUN_00086c78__impl(int, ...);
#define FUN_00086c78(...) FUN_00086c78__impl(0, ##__VA_ARGS__)

#define DAT_00045bac ((volatile int*)0x2000230cUL)
#define DAT_00045bb0 ((volatile int*)0x20007554UL)
#define DAT_00045bb4 (0xbc083UL)
#define DAT_00045bb8 (0xbbfeeUL)
#define DAT_00045bbc (0x2001ce57UL)
#define DAT_00045bc0 (0xa1ce0UL)
#define DAT_00045bc4 (0xa1be90UL)
#define DAT_00045bc8 (0x4f40b8UL)
#define DAT_00045bcc (0xa145c0UL)
#define DAT_00045bd0 (0xa141bcUL)
#define DAT_00045bd4 (0xa13ff8UL)
#define DAT_00045f24 (0x9f59f8UL)
#define DAT_00045f28 (0x4ed328UL)
#define DAT_00045f2c (0x4dd104UL)
#define DAT_00045f30 (0x9eba14UL)
#define DAT_00045f34 (0x2001ce57UL)
#define DAT_00045f38 (0x4f3bf0UL)
#define DAT_00045f3c (0x4d58f8UL)
#define DAT_00045f40 ((volatile int*)0x2000230cUL)
#define DAT_00045f44 ((volatile int*)0x20007554UL)
#define DAT_00045f48 (0xbc083UL)
#define DAT_00045f4c (0xbc006UL)
#define DAT_0004627c ((volatile int*)0x2000230cUL)
#define DAT_00046280 ((volatile int*)0x20007554UL)
#define DAT_00046284 (0xbc083UL)
#define DAT_00046288 (0xbc04cUL)
#define DAT_0004628c (0xc8162UL)
#define DAT_00046290 (0xc8f47UL)
#define DAT_00046294 (0xc8e7fUL)
#define DAT_00046298 (0xc8db7UL)
#define DAT_0004629c (0xc805eUL)
#define DAT_000462a0 (0xc87c7UL)
#define DAT_000462a4 (0xc8b5fUL)
#define DAT_000462a8 (0xc8c27UL)
#define DAT_000462ac (0xc8cefUL)
#define DAT_000462b0 (0xc89cfUL)
#define DAT_000462b4 (0xc8a97UL)
#define DAT_000462b8 (0xc88cbUL)
#define DAT_000462bc (0xbc613UL)
#define DAT_000462c0 (0xbc529UL)
#define DAT_000462c4 (0xbc43fUL)
#define DAT_000462c8 (0xbc355UL)
#define DAT_000462cc (0xbc26bUL)
#define DAT_000462d0 (0xbc181UL)
#define DAT_000462d4 (0xbc097UL)
#define DAT_000462d8 (0xca04fUL)
#define DAT_000462dc (0xc9f4bUL)
#define DAT_000462e0 (0xc9e47UL)
#define DAT_000462e4 (0xc9d43UL)
#define DAT_0004657c (0xc9c3fUL)
#define DAT_00046580 (0xc9b3bUL)
#define DAT_00046584 (0xc9a37UL)
#define DAT_00046588 (0xc9933UL)
#define DAT_0004658c (0xc982fUL)
#define DAT_00046590 (0xc972bUL)
#define DAT_00046594 (0xc9627UL)
#define DAT_00046598 (0xc9523UL)
#define DAT_0004659c (0xc941fUL)
#define DAT_000465a0 (0xc931bUL)
#define DAT_000465a4 (0xc9217UL)
#define DAT_000465a8 (0xc9113UL)
#define DAT_000465ac (0xc900fUL)
#define DAT_000465b0 (0xc7f5aUL)
#define DAT_000465b4 (0xc7e92UL)
#define DAT_000465b8 (0xc81a3UL)
#define DAT_000465bc (0xc7c22UL)
#define DAT_000465c0 (0xc7a90UL)
#define DAT_000465c4 (0xc7956UL)
#define DAT_000465c8 (0xc77c4UL)
#define DAT_000465cc (0xc768aUL)
#define DAT_000465d0 (0xc760aUL)
#define DAT_000465d4 (0xc758aUL)
#define DAT_000465d8 (0xc74c2UL)
#define DAT_000465dc (0xc73faUL)
#define DAT_000465e0 (0xc86c3UL)
#define DAT_000465e4 (0xc85fbUL)
#define DAT_000465e8 (0xc8533UL)
#define DAT_000465ec (0xc846bUL)
#define DAT_000465f0 (0xc83a3UL)
#define DAT_000465f4 (0xc82dbUL)
#define DAT_000465f8 (0xc739fUL)
#define DAT_000465fc (0xc736dUL)
#define DAT_00046600 (0xc733bUL)
#define DAT_00046604 (0xc7309UL)
#define DAT_00046608 (0xc72d7UL)
#define DAT_0004660c (0xc6df5UL)
#define DAT_00046610 (0xc6913UL)
#define DAT_00046614 (0xc6431UL)
#define DAT_00046618 (0xc5f4fUL)
#define DAT_0004661c (0xc5a6dUL)
#define DAT_00046620 (0xc558bUL)
#define DAT_00046624 (0xc50a9UL)
#define DAT_0004689c (0x0UL) /* unknown lit */
#define DAT_000468a0 (0x0UL) /* unknown lit */
#define DAT_000468a4 (0x0UL) /* unknown lit */
#define DAT_000468a8 (0x0UL) /* unknown lit */
#define DAT_000468ac (0x0UL) /* unknown lit */
#define DAT_000468b0 (0x0UL) /* unknown lit */
#define DAT_000468b4 (0x0UL) /* unknown lit */
#define DAT_000468b8 (0x0UL) /* unknown lit */
#define DAT_000468bc (0x0UL) /* unknown lit */
#define DAT_000468c0 (0x0UL) /* unknown lit */
#define DAT_000468c4 (0x0UL) /* unknown lit */
#define DAT_000468c8 (0x0UL) /* unknown lit */
#define DAT_000468cc (0x0UL) /* unknown lit */
#define DAT_000468d0 (0x0UL) /* unknown lit */
#define DAT_000468d4 (0x0UL) /* unknown lit */
#define DAT_000468d8 (0x0UL) /* unknown lit */
#define DAT_000468dc (0x0UL) /* unknown lit */
#define DAT_000468e0 (0x0UL) /* unknown lit */
#define DAT_000468e4 (0x0UL) /* unknown lit */
#define DAT_000468e8 (0x0UL) /* unknown lit */
#define DAT_000468ec (0x0UL) /* unknown lit */
#define DAT_000468f0 (0x0UL) /* unknown lit */
#define DAT_000468f4 (0x0UL) /* unknown lit */
#define DAT_000468f8 (0x0UL) /* unknown lit */
#define DAT_000468fc (0x0UL) /* unknown lit */
#define DAT_00046900 (0x0UL) /* unknown lit */
#define DAT_00046904 (0x0UL) /* unknown lit */
#define DAT_00046908 (0x0UL) /* unknown lit */
#define DAT_0004690c (0x0UL) /* unknown lit */
#define DAT_00046910 (0x0UL) /* unknown lit */
#define DAT_00046914 (0x0UL) /* unknown lit */
#define DAT_00046918 (0x0UL) /* unknown lit */
#define DAT_0004691c (0x0UL) /* unknown lit */
#define DAT_00046920 (0x0UL) /* unknown lit */
#define DAT_00046924 (0x0UL) /* unknown lit */
#define DAT_00046928 (0x0UL) /* unknown lit */
#define DAT_0004692c (0x0UL) /* unknown lit */
#define DAT_00046930 (0x0UL) /* unknown lit */
#define DAT_00046934 (0x0UL) /* unknown lit */
#define DAT_00046998 (0x0UL) /* unknown lit */
#define DAT_0004699c (0x0UL) /* unknown lit */
#define DAT_000469a0 (0x0UL) /* unknown lit */
#define DAT_000469a4 (0x0UL) /* unknown lit */


undefined4
resource_manger_get(uint param_1,uint param_2,uint *param_3,uint *param_4,int *param_5,undefined1 *param_6)

{
  uint uVar1;
  ulonglong uVar2;
  ushort uVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  code *pcVar10;
  ulonglong uVar11;
  undefined8 uVar12;
  undefined4 local_28;
  undefined4 local_24;
  
  uVar11 = CONCAT44(param_2,param_1);
  local_28 = param_1;
  local_24 = param_2;
  switch(param_1) {
  case 0:
    if ((int)param_2 < 0x2714) {
      uVar11 = FUN_00045840(param_2 & 0xffff,&local_28,&local_24);
      *param_5 = (int)uVar11;
      if ((int)uVar11 != 0) {
        *param_3 = local_28;
        *param_4 = local_24;
        return 0;
      }
    }
    if (0xff41 < param_2 - 0xa4) goto LAB_00045caa;
    iVar8 = FUN_000167a8();
    pcVar10 = *(code **)(iVar8 + 0x1030);
    uVar4 = FUN_000167a8();
    iVar9 = (param_2 - 0xa4) * 4;
    uVar5 = (*pcVar10)(uVar4,iVar9 + 0x140000,&local_24);
    iVar8 = DAT_00045bbc;
    if (uVar5 == 0) {
      uVar1 = local_24 >> 0x10;
      if (uVar1 == 0xffff) {
        if (param_2 - 0x1100 < 0xfa) {
          local_28 = uVar5;
          local_24 = uVar5;
          iVar8 = FUN_000167a8(0,0);
          pcVar10 = *(code **)(iVar8 + 0x1030);
          uVar4 = FUN_000167a8();
          iVar9 = (*pcVar10)(uVar4,DAT_00045bc4 + iVar9,&local_24);
          iVar8 = DAT_00045bbc;
          if (iVar9 != 0) goto LAB_00045902;
          uVar5 = ((*(volatile uint16_t*)((char*)&local_24 + 2)) & 0xff) << 8 | (uint)((*(volatile uint16_t*)((char*)&local_24 + 2)) >> 8);
          local_28 = CONCAT22((short)uVar5,(ushort)((local_24 & 0xff) << 8) | (ushort)local_24 >> 8)
          ;
          if ((*(volatile uint16_t*)((char*)&local_24 + 2)) != 0xffff) {
            FUN_00086c78(DAT_00045bbc,0,0x138);
            iVar9 = FUN_000167a8();
            pcVar10 = *(code **)(iVar9 + 0x1030);
            uVar4 = FUN_000167a8();
            param_2 = (*pcVar10)(uVar4,uVar5 * 0x138 + 0xa40000,iVar8,0x138);
LAB_000459fc:
            if (param_2 == 0) {
              uVar5 = 0x18;
              goto LAB_0004597a;
            }
            goto LAB_00045958;
          }
LAB_00045cb8:
          if (0x5d < param_2 - 0xff01) {
            if (0x2e < param_2 - 0x2010) goto LAB_00045b4e;
            uVar12 = FUN_000167a8(0,0);
            uVar2 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),(int)uVar12 + 0x1000);
            if (*(int *)((int)uVar12 + 0x1030) != 0) {
              iVar8 = FUN_000167a8();
              pcVar10 = *(code **)(iVar8 + 0x1030);
              uVar4 = FUN_000167a8();
              iVar9 = (*pcVar10)(uVar4,(param_2 - 0x2010) * 4 + 0x500000,&local_24);
              goto LAB_00045dfa;
            }
            goto LAB_00045e48;
          }
          uVar12 = FUN_000167a8(0,0);
          uVar2 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),(int)uVar12 + 0x1000);
          if (*(int *)((int)uVar12 + 0x1030) != 0) {
            iVar8 = FUN_000167a8();
            pcVar10 = *(code **)(iVar8 + 0x1030);
            uVar4 = FUN_000167a8();
            iVar9 = (*pcVar10)(uVar4,DAT_00045f30 + param_2 * 4,&local_24);
            iVar8 = DAT_00045f34;
            if (iVar9 != 0) goto LAB_00045902;
            uVar3 = (*(volatile uint16_t*)((char*)&local_24 + 2));
            uVar5 = (uint)(*(volatile uint16_t*)((char*)&local_24 + 2));
            if (uVar5 != 0xffff) {
              FUN_00086c78(DAT_00045f34,0,0x138);
              iVar9 = FUN_000167a8();
              pcVar10 = *(code **)(iVar9 + 0x1030);
              uVar4 = FUN_000167a8();
              param_2 = (*pcVar10)(uVar4,((uVar5 & 0xff) << 8 | (uint)(uVar3 >> 8)) * 0x138 +
                                         0xa40000,iVar8,0x138);
              goto LAB_000459fc;
            }
            uVar11 = 0;
            uVar2 = 0;
            if (0x19c < param_2 - 0x3231) goto LAB_00045c68;
            goto LAB_00045d4a;
          }
LAB_00045e4e:
          iVar8 = FUN_000167a8((int)uVar2,(int)(uVar2 >> 0x20));
          if (*(int *)(iVar8 + 0x1030) != 0) {
            iVar8 = FUN_000167a8();
            pcVar10 = *(code **)(iVar8 + 0x1030);
            uVar4 = FUN_000167a8();
            iVar9 = (*pcVar10)(uVar4,DAT_00045f3c + param_2 * 4,&local_24);
            iVar8 = DAT_00045f34;
            if (iVar9 != 0) goto LAB_00045902;
            uVar5 = ((*(volatile uint16_t*)((char*)&local_24 + 2)) & 0xff) << 8 | (uint)((*(volatile uint16_t*)((char*)&local_24 + 2)) >> 8);
            if ((*(volatile uint16_t*)((char*)&local_24 + 2)) != 0xffff) {
              FUN_00086c78(DAT_00045f34,0,0x138);
              iVar9 = FUN_000167a8();
              pcVar10 = *(code **)(iVar9 + 0x1030);
              uVar4 = FUN_000167a8();
LAB_00045db4:
              param_2 = (*pcVar10)(uVar4,uVar5 * 0xd0 + 0x520000,iVar8);
              goto LAB_00045e3c;
            }
          }
        }
        else {
          if (param_2 - 0x302e < 2) {
            uVar12 = FUN_000167a8(0,0);
            iVar8 = (int)((ulonglong)uVar12 >> 0x20);
            iVar6 = (int)uVar12 + 0x1000;
            if (*(int *)((int)uVar12 + 0x1030) != 0) {
              iVar8 = FUN_000167a8();
              pcVar10 = *(code **)(iVar8 + 0x1030);
              uVar4 = FUN_000167a8();
              iVar8 = (*pcVar10)(uVar4,DAT_00045bcc + iVar9,&local_24);
              if (iVar8 != 0) goto LAB_00045902;
              uVar5 = local_24 >> 0x10;
              if (uVar5 != 0xffff) goto LAB_00045a8a;
LAB_00045b4e:
              iVar6 = 0;
              uVar11 = 0;
              iVar8 = iVar6;
              if (0xfd < param_2 - 0x3001) goto LAB_00045caa;
            }
            uVar12 = FUN_000167a8(iVar6,iVar8);
            uVar2 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),(int)uVar12 + 0x1000);
            if (*(int *)((int)uVar12 + 0x1030) == 0) goto LAB_00045e48;
            iVar8 = FUN_000167a8();
            pcVar10 = *(code **)(iVar8 + 0x1030);
            uVar4 = FUN_000167a8();
            iVar9 = (*pcVar10)(uVar4,DAT_00045bc8 + param_2 * 4,&local_24);
LAB_00045dfa:
            iVar8 = DAT_00045f34;
            if (iVar9 != 0) goto LAB_00045902;
            uVar3 = (*(volatile uint16_t*)((char*)&local_24 + 2));
            uVar5 = (uint)(*(volatile uint16_t*)((char*)&local_24 + 2));
            uVar2 = 0;
            if (uVar5 == 0xffff) goto LAB_00045e48;
            FUN_00086c78(DAT_00045f34,0,0x138);
            iVar9 = FUN_000167a8();
            pcVar10 = *(code **)(iVar9 + 0x1030);
            uVar4 = FUN_000167a8();
            param_2 = (*pcVar10)(uVar4,((uVar5 & 0xff) << 8 | (uint)(uVar3 >> 8)) * 0xd0 + 0x520000,
                                 iVar8);
LAB_00045e3c:
            if (param_2 == 0) {
              uVar5 = 0x10;
LAB_0004597a:
              *param_3 = uVar5;
              *param_4 = 0x1a;
              *param_5 = iVar8;
              return 0;
            }
            goto LAB_00045958;
          }
          if (param_2 - 0x3131 < 0x5e) {
            uVar12 = FUN_000167a8(0,0);
            uVar11 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),(int)uVar12 + 0x1000);
            if (*(int *)((int)uVar12 + 0x1030) != 0) {
              iVar8 = FUN_000167a8();
              pcVar10 = *(code **)(iVar8 + 0x1030);
              uVar4 = FUN_000167a8();
              iVar8 = (*pcVar10)(uVar4,DAT_00045bd0 + iVar9,&local_24);
              if (iVar8 == 0) {
                uVar3 = (*(volatile uint16_t*)((char*)&local_24 + 2));
                uVar5 = (uint)(*(volatile uint16_t*)((char*)&local_24 + 2));
                if (uVar5 == 0xffff) goto LAB_00045b4e;
                FUN_00086c78(DAT_00045bbc,0,0x138);
                iVar8 = FUN_000167a8();
                pcVar10 = *(code **)(iVar8 + 0x1030);
                uVar4 = FUN_000167a8();
                param_2 = (*pcVar10)(uVar4,((uVar5 & 0xff) << 8 | (uint)(uVar3 >> 8)) * 0x138 +
                                           0xa40000,DAT_00045bbc,0x138);
                if (param_2 == 0) {
                  *param_3 = 0x18;
                  *param_4 = 0x1a;
                  *param_5 = DAT_00045bbc;
                  return 0;
                }
                goto LAB_00045958;
              }
              goto LAB_00045902;
            }
LAB_00045caa:
            if (param_2 - 0x3231 < 0x19d) {
LAB_00045d4a:
              uVar12 = FUN_000167a8((int)uVar11,(int)(uVar11 >> 0x20));
              uVar2 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),(int)uVar12 + 0x1000);
              if (*(int *)((int)uVar12 + 0x1030) == 0) goto LAB_00045e48;
              iVar8 = FUN_000167a8();
              pcVar10 = *(code **)(iVar8 + 0x1030);
              uVar4 = FUN_000167a8();
              iVar8 = DAT_00045f38;
            }
            else {
LAB_00045c26:
              uVar2 = uVar11;
              if (0x5177 < param_2 - 0x4e00) goto LAB_00045c68;
              uVar12 = FUN_000167a8((int)uVar11,(int)(uVar11 >> 0x20));
              uVar2 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),(int)uVar12 + 0x1000);
              if (*(int *)((int)uVar12 + 0x1030) == 0) goto LAB_00045e48;
              iVar8 = FUN_000167a8();
              pcVar10 = *(code **)(iVar8 + 0x1030);
              uVar4 = FUN_000167a8();
              iVar8 = DAT_00045f28;
            }
LAB_00045d74:
            iVar9 = (*pcVar10)(uVar4,iVar8 + param_2 * 4,&local_24);
            iVar8 = DAT_00045f34;
            if (iVar9 != 0) goto LAB_00045902;
            uVar3 = (*(volatile uint16_t*)((char*)&local_24 + 2));
            uVar5 = (uint)(*(volatile uint16_t*)((char*)&local_24 + 2));
            if (uVar5 != 0xffff) {
              FUN_00086c78(DAT_00045f34,0,0x138);
              iVar9 = FUN_000167a8();
              pcVar10 = *(code **)(iVar9 + 0x1030);
              uVar4 = FUN_000167a8();
              uVar5 = (uVar5 & 0xff) << 8 | (uint)(uVar3 >> 8);
              goto LAB_00045db4;
            }
          }
          else {
            if (param_2 - 0x3200 < 0x80) {
              uVar12 = FUN_000167a8(0,0);
              uVar11 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),(int)uVar12 + 0x1000);
              if (*(int *)((int)uVar12 + 0x1030) != 0) {
                iVar8 = FUN_000167a8();
                pcVar10 = *(code **)(iVar8 + 0x1030);
                uVar4 = FUN_000167a8();
                uVar11 = (*pcVar10)(uVar4,DAT_00045bd4 + iVar9,&local_24);
                if ((int)uVar11 != 0) goto LAB_00045902;
                uVar5 = local_24 >> 0x10;
                uVar11 = uVar11 & 0xffffffff00000000;
                if (uVar5 != 0xffff) {
LAB_00045a8a:
                  iVar8 = DAT_00045bbc;
                  FUN_00086c78(DAT_00045bbc,0,0x138);
                  iVar9 = FUN_000167a8();
                  pcVar10 = *(code **)(iVar9 + 0x1030);
                  uVar4 = FUN_000167a8();
                  param_2 = (*pcVar10)(uVar4,((uVar5 & 0xff) << 8 | uVar5 >> 8) * 0x138 + 0xa40000,
                                       iVar8,0x138);
                  goto LAB_000459fc;
                }
              }
              goto LAB_00045caa;
            }
            if (0x2bab < param_2 - 0xac00) goto LAB_00045cb8;
            uVar12 = FUN_000167a8(0,0);
            uVar2 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),(int)uVar12 + 0x1000);
            if (*(int *)((int)uVar12 + 0x1030) != 0) {
              iVar8 = FUN_000167a8();
              pcVar10 = *(code **)(iVar8 + 0x1030);
              uVar4 = FUN_000167a8();
              uVar11 = (*pcVar10)(uVar4,DAT_00045f24 + iVar9,&local_24);
              if ((int)uVar11 != 0) goto LAB_00045902;
              uVar5 = local_24 >> 0x10;
              if (uVar5 != 0xffff) goto LAB_00045a8a;
              uVar11 = uVar11 & 0xffffffff00000000;
              goto LAB_00045c26;
            }
LAB_00045c68:
            if (param_2 - 0xe001 < 0xfd) {
              iVar8 = FUN_000167a8((int)uVar2,(int)(uVar2 >> 0x20));
              if (*(int *)(iVar8 + 0x1030) != 0) {
                iVar8 = FUN_000167a8();
                pcVar10 = *(code **)(iVar8 + 0x1030);
                uVar4 = FUN_000167a8();
                iVar8 = DAT_00045f2c;
                goto LAB_00045d74;
              }
            }
            else {
LAB_00045e48:
              if (param_2 - 0xff01 < 0x9f) goto LAB_00045e4e;
            }
          }
        }
        if (*DAT_00045f40 < 3) {
          return 0xffffffff;
        }
        iVar8 = *DAT_00045f44;
        uVar4 = DAT_00045f4c;
        uVar7 = DAT_00045f48;
      }
      else {
        FUN_00086c78(DAT_00045bbc,0,0x138);
        iVar9 = FUN_000167a8();
        pcVar10 = *(code **)(iVar9 + 0x1030);
        uVar4 = FUN_000167a8();
        param_2 = (*pcVar10)(uVar4,uVar1 * 0xea + 0x200000,iVar8);
        if (param_2 == 0) {
          uVar5 = 0x12;
          goto LAB_0004597a;
        }
LAB_00045958:
        if (*DAT_00045bac < 1) {
          return 0xffffffff;
        }
        iVar8 = *DAT_00045bb0;
        uVar4 = DAT_00045bc0;
        uVar7 = DAT_00045bb4;
      }
      if (iVar8 == 0) {
        DEBUG_PRINT(uVar4,uVar7,param_2);
        return 0xffffffff;
      }
      FUN_00019c70();
      return 0xffffffff;
    }
LAB_00045902:
    if (*DAT_00045bac < 1) {
      return 0xffffffff;
    }
    iVar8 = *DAT_00045bb0;
    uVar4 = DAT_00045bb8;
    uVar7 = DAT_00045bb4;
    goto LAB_00045912;
  case 1:
    iVar8 = FUN_000457b0(param_2 & 0xffff,&local_28,&local_24);
    *param_5 = iVar8;
    if (iVar8 != 0) {
      *param_3 = local_28;
      *param_4 = local_24;
      return 0;
    }
    break;
  case 2:
    iVar8 = FUN_00045764(param_2 & 0xffff,&local_28,&local_24);
    *param_5 = iVar8;
    if (iVar8 != 0) {
      *param_3 = local_28;
      *param_4 = local_24;
      return 0;
    }
    break;
  case 3:
    iVar8 = FUN_000457f4(param_2 & 0xffff,&local_28,&local_24);
    *param_5 = iVar8;
    *param_3 = local_28;
    *param_4 = local_24;
    return 0;
  case 4:
    if (param_2 - 0x16 < 0x67) {
      switch(param_2) {
      case 0x16:
        *param_5 = DAT_000465b8;
        *param_3 = 0x18;
        *param_4 = 0x1a;
        return 0;
      case 0x17:
        *param_5 = DAT_0004628c;
        *param_3 = 10;
        *param_4 = 0xd;
        return 0;
      case 0x18:
        *param_5 = DAT_00046290;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x19:
        *param_5 = DAT_00046294;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x1a:
        *param_5 = DAT_00046298;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x1b:
        *param_5 = DAT_0004629c;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x1c:
        *param_5 = DAT_000462bc;
        *param_3 = 0x12;
        *param_4 = 0x1a;
        return 0;
      case 0x1d:
        *param_5 = DAT_000462c0;
        *param_3 = 0x12;
        *param_4 = 0x1a;
        return 0;
      case 0x1e:
        *param_5 = DAT_000462c4;
        *param_3 = 0x12;
        *param_4 = 0x1a;
        return 0;
      case 0x1f:
        *param_5 = DAT_000462c8;
        *param_3 = 0x12;
        *param_4 = 0x1a;
        return 0;
      case 0x20:
        *param_5 = DAT_000462cc;
        *param_3 = 0x12;
        *param_4 = 0x1a;
        return 0;
      case 0x21:
        *param_5 = DAT_000462d0;
        *param_3 = 0x12;
        *param_4 = 0x1a;
        return 0;
      case 0x22:
        *param_5 = DAT_000462d4;
        *param_3 = 0x12;
        *param_4 = 0x1a;
        return 0;
      case 0x23:
        *param_5 = DAT_000462d8;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x24:
        *param_5 = DAT_000462dc;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x25:
        *param_5 = DAT_000462e0;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x26:
        *param_5 = DAT_000462e4;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x27:
        *param_5 = DAT_0004657c;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x28:
        *param_5 = DAT_00046580;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x29:
        *param_5 = DAT_00046584;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x2a:
        *param_5 = DAT_00046588;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x2b:
        *param_5 = DAT_0004658c;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x2c:
        *param_5 = DAT_00046590;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x2d:
        *param_5 = DAT_00046594;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x2e:
        *param_5 = DAT_00046598;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x2f:
        *param_5 = DAT_0004659c;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x30:
        *param_5 = DAT_000465a0;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x31:
        *param_5 = DAT_000465a4;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x32:
        *param_5 = DAT_000465a8;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x33:
        *param_5 = DAT_000465ac;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      default:
        return 0xffffffff;
      case 0x36:
        *param_5 = DAT_000462ac;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x37:
        *param_5 = DAT_000462a8;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x38:
        *param_5 = DAT_000462a4;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x39:
        *param_5 = DAT_000462b4;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x3a:
        *param_5 = DAT_000462b0;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x3b:
        *param_5 = DAT_000462b8;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x3c:
        *param_5 = DAT_000462a0;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x3e:
        *param_5 = DAT_000465b0;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x3f:
        *param_5 = DAT_000465b4;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x41:
        *param_5 = DAT_000465bc;
        *param_3 = 0x30;
        *param_4 = 0x1a;
        return 0;
      case 0x42:
        *param_5 = DAT_000465e0;
        *param_3 = 0x14;
        *param_4 = 0x1a;
        return 0;
      case 0x43:
        *param_5 = DAT_000465e4;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x44:
        *param_5 = DAT_000465e8;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x45:
        *param_5 = DAT_000465ec;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x46:
        *param_5 = DAT_000465f0;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x47:
        *param_5 = DAT_000465f4;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x48:
        *param_5 = DAT_000465d8;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x49:
        *param_5 = DAT_000465dc;
        *param_3 = 0x14;
        *param_4 = 0x14;
        return 0;
      case 0x4a:
        *param_5 = DAT_000465c0;
        *param_3 = 0x192;
        *param_4 = 2;
        return 0;
      case 0x4b:
        *param_5 = DAT_000465c4;
        *param_3 = 0x13a;
        *param_4 = 2;
        return 0;
      case 0x4c:
        *param_5 = DAT_000465c8;
        *param_3 = 0x192;
        *param_4 = 2;
        return 0;
      case 0x4d:
        *param_5 = DAT_000465cc;
        *param_3 = 0x13a;
        *param_4 = 2;
        return 0;
      case 0x4e:
        *param_5 = DAT_000465d0;
        *param_3 = 2;
        *param_4 = 0x80;
        return 0;
      case 0x4f:
        *param_5 = DAT_000465d4;
        *param_3 = 2;
        *param_4 = 0x80;
        return 0;
      case 0x50:
        *param_5 = DAT_000465fc;
        *param_3 = 10;
        *param_4 = 10;
        return 0;
      case 0x51:
        *param_5 = DAT_00046600;
        *param_3 = 10;
        *param_4 = 10;
        return 0;
      case 0x52:
        *param_5 = DAT_00046604;
        *param_3 = 10;
        *param_4 = 10;
        return 0;
      case 0x53:
        *param_5 = DAT_00046608;
        *param_3 = 10;
        *param_4 = 10;
        return 0;
      case 0x54:
        *param_5 = DAT_000465f8;
        *param_3 = 0xe;
        *param_4 = 0xd;
        return 0;
      case 0x56:
        *param_5 = DAT_0004660c;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x57:
        *param_5 = DAT_00046610;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x58:
        *param_5 = DAT_00046614;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x59:
        *param_5 = DAT_00046618;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x5a:
        *param_5 = DAT_0004661c;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x5b:
        *param_5 = DAT_00046620;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x5c:
        *param_5 = DAT_00046624;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x5d:
        *param_5 = DAT_0004689c;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x5e:
        *param_5 = DAT_000468a0;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x5f:
        *param_5 = DAT_000468a4;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x60:
        *param_5 = DAT_000468a8;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x61:
        *param_5 = DAT_000468ac;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x62:
        *param_5 = DAT_000468b0;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 99:
        *param_5 = DAT_000468b4;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 100:
        *param_5 = DAT_000468b8;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x65:
        *param_5 = DAT_000468bc;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x66:
        *param_5 = DAT_000468c0;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x67:
        *param_5 = DAT_000468c4;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x68:
        *param_5 = DAT_000468c8;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x69:
        *param_5 = DAT_000468cc;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x6a:
        *param_5 = DAT_000468d0;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x6b:
        *param_5 = DAT_000468d4;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x6c:
        *param_5 = DAT_000468d8;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x6d:
        *param_5 = DAT_000468dc;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x6e:
        *param_5 = DAT_000468e0;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x6f:
        *param_5 = DAT_000468e4;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x70:
        *param_5 = DAT_000468e8;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x71:
        *param_5 = DAT_000468ec;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x72:
        *param_5 = DAT_000468f0;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x73:
        *param_5 = DAT_000468f4;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x74:
        *param_5 = DAT_000468f8;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x75:
        *param_5 = DAT_000468fc;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x76:
        *param_5 = DAT_00046900;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x77:
        *param_5 = DAT_00046904;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x78:
        *param_5 = DAT_00046908;
        *param_3 = 0x32;
        *param_4 = 0x32;
        return 0;
      case 0x7a:
        *param_5 = DAT_0004690c;
        *param_3 = 0x22;
        *param_4 = 1;
        return 0;
      case 0x7b:
        *param_5 = DAT_00046910;
        *param_3 = 0x2c;
        *param_4 = 1;
        return 0;
      case 0x7c:
        *param_5 = DAT_00046914;
        *param_3 = 0x19a;
        *param_4 = 1;
        return 0;
      }
    }
    if (*DAT_0004627c < 2) {
      return 0xffffffff;
    }
    iVar8 = *DAT_00046280;
    uVar4 = DAT_00046288;
    uVar7 = DAT_00046284;
LAB_00045912:
    if (iVar8 == 0) {
      DEBUG_PRINT(uVar4,uVar7);
    }
    else {
      FUN_00019c70();
    }
    break;
  case 5:
    switch(param_2) {
    case 1:
      *param_5 = DAT_00046918;
      *param_3 = 0x14;
      *param_4 = 0x1a;
      if (param_6 != (undefined1 *)0x0) {
        *param_6 = 0x2d;
      }
      break;
    case 2:
      iVar8 = DAT_0004691c;
      goto LAB_00046816;
    case 3:
      iVar8 = DAT_00046920;
LAB_00046816:
      *param_5 = iVar8;
      *param_3 = 0x14;
      *param_4 = 0x14;
      if (param_6 != (undefined1 *)0x0) {
        *param_6 = 0x16;
      }
      break;
    case 4:
      *param_5 = DAT_00046924;
      *param_3 = 0x14;
      *param_4 = 0x14;
      if (param_6 != (undefined1 *)0x0) {
        *param_6 = 0xf;
      }
      break;
    case 5:
      *param_5 = DAT_00046928;
      *param_3 = 0x14;
      goto LAB_00046850;
    case 6:
      *param_5 = DAT_0004692c;
      *param_3 = 0x14;
      *param_4 = 0x14;
      if (param_6 != (undefined1 *)0x0) {
        *param_6 = 10;
      }
      break;
    case 7:
      *param_5 = DAT_00046930;
      *param_3 = 0x16;
LAB_00046850:
      *param_4 = 0x14;
      if (param_6 != (undefined1 *)0x0) {
        *param_6 = 9;
      }
      break;
    case 8:
      *param_5 = DAT_00046934;
      *param_3 = 0x14;
      *param_4 = 0x14;
      if (param_6 != (undefined1 *)0x0) {
        *param_6 = 0x22;
      }
      break;
    case 9:
      *param_5 = DAT_00046998;
      *param_3 = 0x14;
      *param_4 = 0x14;
      if (param_6 != (undefined1 *)0x0) {
        *param_6 = 0x13;
      }
      break;
    case 10:
      *param_5 = DAT_0004699c;
      *param_3 = 0x14;
      *param_4 = 0x14;
      if (param_6 != (undefined1 *)0x0) {
        *param_6 = 0x11;
      }
      break;
    case 0xb:
      *param_5 = DAT_000469a0;
      *param_3 = 0x14;
      *param_4 = 0x14;
      if (param_6 != (undefined1 *)0x0) {
        *param_6 = 0x15;
      }
      break;
    case 0xc:
      *param_5 = DAT_000469a4;
      *param_3 = 0x14;
      *param_4 = 0x14;
      if (param_6 != (undefined1 *)0x0) {
        *param_6 = 0x1d;
      }
      break;
    default:
      goto switchD_0004589e_caseD_6;
    }
    return 0;
  }
switchD_0004589e_caseD_6:
  return 0xffffffff;
}


