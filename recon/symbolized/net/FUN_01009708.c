#include "g1_net_symbols.h"
/* net-core FUN_01009708 @ 0x1009708  (parity 300 trials PROVEN) */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

static volatile u8 *const DAT_01009868 = (volatile u8*)((unsigned long)&g_net_bump_alloc_state) /*=0x21000ba8*/;
static volatile u32 *const DAT_0100986c = (volatile u32*)((unsigned long)&g_net_bump_alloc_cursor) /*=0x21000bac*/;
static volatile u32 *const DAT_01009870 = (volatile u32*)0x21000b7c;

extern void FUN_01008d00(u32,u32);
extern u32 FUN_010274d0(u8);

void FUN_01009708(u8 param_1, u8 *param_2)
{
  if (*DAT_01009868 != 1 && *DAT_01009868 != 3) FUN_01008d00(0x17,0x120);
  if (param_2[6] > 8) FUN_01008d00(0x17,0x122);
  if (param_2[7] != 0) {
    u32 iVar7 = *DAT_0100986c;
    u32 iVar1 = FUN_010274d0(param_2[7]);
    u8 bVar2 = param_2[6]; if (bVar2 < 2) bVar2 = 2;
    u8 bVar3 = param_2[6]; if (bVar3 < 2) bVar3 = 2;
    u32 uVar4 = (u32)(-(int)bVar3) & (iVar1 + iVar7 + bVar2 - 1);
    u16 hVar = *(u16*)(param_2 + 4);
    u32 uVar5 = (u32)(-(int)param_2[6]) & (param_2[6] + hVar - 1);
    if (uVar5 > 0xfffe) FUN_01008d00(0x17,0x12d);
    if (*DAT_01009868 == 3) {
      u32 iVar1b = FUN_010274d0(param_2[7]);
      u16 *puVar6 = (u16*)(uVar4 - iVar1b);
      if (DAT_01009870[param_1] != 0) FUN_01008d00(0x17,0x132);
      DAT_01009870[param_1] = (u32)puVar6;
      puVar6[0] = (u16)uVar5;
      *((u8*)(puVar6+1)) = param_2[7];
      *((u8*)puVar6+3) = 1;
      *((u8*)puVar6+4) = param_2[8];
      u32 param2_0 = *(u32*)param_2;
      puVar6[3] = (u16)(param2_0 >> 16);
      puVar6[4] = (u16)param2_0;
      for (u32 local_14 = 0; local_14 < param_2[7]; local_14++) {
        puVar6[local_14+5] = 0xfff0;
      }
    }
    *DAT_0100986c = param_2[7]*uVar5 + uVar4;
  }
}
