#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01033b18 @ 0x01033b18
 * public-name: FUN_01033b18
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103e47c                           @ 0x0103e47c
 *   g_net_radio_trx_ppi_ch_a                 @ 0x2100645a
 *   g_esb_ppi_ch_id_1                        @ 0x2100645b
 *   g_154_dppi_channel_ack                   @ 0x2100645c
 *   g_esb_ppi_ch_id_3                        @ 0x2100645d
 *   REG_41008080                             @ 0x41008080
 */
/* net-core FUN_01033b18 @ 0x1033b18  (parity 300 trials PROVEN) */

extern void FUN_01039bb0(unsigned int, unsigned int);
extern void FUN_01039bbe(unsigned int, unsigned int, unsigned int);

void FUN_01033b18(unsigned int param_1, int param_2)
{
  volatile unsigned char * const iVar3 = (volatile unsigned char *)0x41014000;

  *(volatile unsigned int *)(iVar3 + 0x118) = 0;
  *(volatile unsigned int *)(iVar3 + 0x11c) = 0;

  volatile unsigned char * const pbc8 = (volatile unsigned char *)((unsigned long)&g_154_dppi_channel_ack) /*=0x2100645c*/;
  unsigned char bVar2 = pbc8[0];
  unsigned int uVar7 = bVar2 | 0x80000000u;
  *(volatile unsigned int *)(iVar3 + 0x198) = uVar7;

  volatile unsigned char * const pbcc = (volatile unsigned char *)((unsigned long)&g_esb_ppi_ch_id_1) /*=0x2100645b*/;
  unsigned int uVar9 = pbcc[0];
  unsigned int uVar8 = uVar9 | 0x80000000u;
  *(volatile unsigned int *)(iVar3 + 0x19c) = uVar8;

  volatile unsigned char * const pbd0 = (volatile unsigned char *)((unsigned long)&g_net_radio_trx_ppi_ch_a) /*=0x2100645a*/;
  unsigned char bVar1 = pbd0[0];

  volatile unsigned int *tbl800 = (volatile unsigned int *)(0x4100f800u + (unsigned int)bVar1 * 4);
  *tbl800 = (1u << uVar9) | *tbl800;

  *(volatile unsigned int *)(iVar3 + 0x9c) = uVar7;

  volatile unsigned char * const p8080 = (volatile unsigned char *)REG_41008080 /*=0x41008080*/;
  *(volatile unsigned int *)(p8080 + (param_1 & 0x3f) * 4) = uVar8;

  if (uVar9 > 0x1f) {
    FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103e47c) /*=0x103e47c*/, 0x17d);
    FUN_01039bb0(((unsigned long)&rodata_103e47c) /*=0x103e47c*/, 0x17d);
  }

  volatile unsigned char * const pf080 = (volatile unsigned char *)0x4100f080;
  unsigned int idx = ((unsigned int)bVar1 * 8 + 4) & 0xff;
  *(volatile unsigned int *)(pf080 + idx) = uVar8;

  volatile unsigned char * const pbe4 = (volatile unsigned char *)((unsigned long)&g_esb_ppi_ch_id_3) /*=0x2100645d*/;
  *(volatile unsigned int *)(iVar3 + 0x98) = pbe4[0] | 0x80000000u;

  if (param_2 != 0) {
    volatile unsigned char * const p9000 = (volatile unsigned char *)0x41019000;
    *(volatile unsigned int *)(p9000 + 0x80) = uVar7;
  }

  volatile unsigned char * const pf000 = (volatile unsigned char *)0x4100f000;
  *(volatile unsigned int *)(pf000 + 0x504) = (1u << bVar2) | (1u << uVar9);
}
