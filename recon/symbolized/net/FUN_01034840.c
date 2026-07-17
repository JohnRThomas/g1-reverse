#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01034840 @ 0x01034840
 * public-name: FUN_01034840
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_sdc_res_pool_slot_tbl                  @ 0x210006a8
 */
/* net-core FUN_01034840 @ 0x1034840  (parity 300 trials PROVEN) */
extern unsigned long long FUN_010344a8(void);
extern int FUN_010344d4(unsigned int);
extern unsigned long long FUN_010344ec(unsigned int);
extern int FUN_01034508(unsigned int);
extern void FUN_0103a924(unsigned int, int, int, int, int, int, unsigned char *);

#define DAT_01034934 ((unsigned long)&g_sdc_res_pool_slot_tbl) /*=0x210006a8*/
#define DAT_01034938 0x0bad0000u
#define DAT_0103493c 0x0bad0004u

unsigned int FUN_01034840(unsigned int param_1, unsigned int param_2,
                           unsigned char *param_3, unsigned int param_4)
{
  unsigned char bVar1;
  unsigned char bVar2;
  unsigned char bVar3;
  int iVar4;
  unsigned int uVar5;
  int iVar6;
  int iVar7;
  unsigned short uVar8;
  unsigned long long uVar9;
  unsigned long long uVar10;
  unsigned char *pbVar11;
  unsigned int uStack_1c;

  (void)param_2;
  pbVar11 = param_3;
  uStack_1c = param_4;
  uVar9 = FUN_010344a8();
  if ((int)(uVar9 >> 0x20) != 0) {
    iVar4 = FUN_01034508(param_1);
    if ((iVar4 == 0) && (iVar4 = FUN_010344d4(param_1), iVar4 != 0)) {
      return DAT_0103493c;
    }
    uVar10 = FUN_010344ec(param_1);
    iVar4 = (int)(uVar10 >> 0x20);
    if (((int)uVar10 != 0) && (*(char *)(long)(iVar4 + 1) == '\x01')) {
      return DAT_0103493c;
    }
    uStack_1c = (uStack_1c & 0xff000000u) | (1u << 24) | (uStack_1c & 0x00ffffffu);
    /* CONCAT13(1, low3bytes(uStack_1c)) : top byte = 1, low 3 bytes preserved */
    uStack_1c = (uStack_1c & 0x00ffffffu) | (1u << 24);
    FUN_0103a924(param_1, (int)(long)&uStack_1c + 3, iVar4 + 1, iVar4 + 2, iVar4, 0, pbVar11);
    iVar4 = (int)uVar9 + 8;
    *(unsigned short *)(DAT_01034934 + iVar4 * 2) = *(unsigned short *)(DAT_01034934 + iVar4 * 2) | 3;
  }
  uVar5 = DAT_01034938;
  if ((param_3 != (unsigned char *)0) &&
      (iVar6 = FUN_01034508(param_1), iVar4 = DAT_01034934, uVar5 = DAT_0103493c, iVar6 != 0)) {
    iVar6 = (int)uVar9 + 8;
    bVar1 = *param_3;
    iVar7 = (unsigned int)bVar1 * 4;
    uVar8 = *(unsigned short *)(DAT_01034934 + iVar6 * 2) & 0x1fdf;
    *(volatile unsigned int *)(long)(iVar7 + 0x4100a510) = 0;
    *(unsigned short *)(iVar4 + iVar6 * 2) = uVar8;
    *(volatile unsigned int *)(long)(iVar7 + 0x4100a510) = 0;
    bVar2 = param_3[1];
    uVar5 = DAT_01034938;
    if (bVar2 != 0) {
      bVar3 = param_3[2];
      *(volatile unsigned int *)(long)(iVar7 + 0x4100a510) =
          *(volatile unsigned int *)(long)(iVar7 + 0x4100a510) & 0xffecc0ffu;
      *(volatile unsigned int *)(long)(iVar7 + 0x4100a510) =
          ((param_1 & 0x3f) << 8) | ((unsigned int)(bVar2 & 3) << 0x10) |
          *(volatile unsigned int *)(long)(iVar7 + 0x4100a510) | ((unsigned int)(bVar3 & 1) << 0x14);
      *(unsigned short *)(iVar4 + iVar6 * 2) = uVar8 | ((unsigned short)bVar1 << 0xd) | 0x20;
      uVar5 = DAT_01034938;
    }
  }
  return uVar5;
}
