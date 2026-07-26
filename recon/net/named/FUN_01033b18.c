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
#include "../../headers/g1_nrf_regs.h"
/* net-core FUN_01033b18 @ 0x1033b18  (parity 300 trials PROVEN) */

extern __attribute__((noreturn)) void assert_post_action(unsigned int, unsigned int); /* FUN_01039bb0 */
extern void assert_print(unsigned int, unsigned int, unsigned int); /* FUN_01039bbe */

void FUN_01033b18(unsigned int param_1, int param_2)
{
  volatile unsigned char * const iVar3 = (volatile unsigned char *)G1_NRF_EGU0_NS_BASE;

  *(volatile unsigned int *)(iVar3 + 0x118) = 0;
  (void)*(volatile unsigned int *)(iVar3 + 0x118); /* read-back @ 0x41014118, raw 0x01033b28 */
  *(volatile unsigned int *)(iVar3 + 0x11c) = 0;
  (void)*(volatile unsigned int *)(iVar3 + 0x11c); /* read-back @ 0x4101411c, raw 0x01033b30 */

  volatile unsigned char * const pbc8 = (volatile unsigned char *)0x2100645c;
  unsigned char bVar2 = pbc8[0];
  unsigned int uVar7 = bVar2 | 0x80000000u;
  *(volatile unsigned int *)(iVar3 + 0x198) = uVar7;

  volatile unsigned char * const pbcc = (volatile unsigned char *)0x2100645b;
  unsigned int uVar9 = pbcc[0];
  unsigned int uVar8 = uVar9 | 0x80000000u;
  *(volatile unsigned int *)(iVar3 + 0x19c) = uVar8;

  volatile unsigned char * const pbd0 = (volatile unsigned char *)0x2100645a;
  unsigned char bVar1 = pbd0[0];

  volatile unsigned int *tbl800 = (volatile unsigned int *)(0x4100f800u + (unsigned int)bVar1 * 4);
  *tbl800 = (1u << uVar9) | *tbl800;

  *(volatile unsigned int *)(iVar3 + 0x9c) = uVar7;

  volatile unsigned char * const p8080 = (volatile unsigned char *)(G1_NRF_RADIO_NS_BASE + 0x80);
  *(volatile unsigned int *)(p8080 + (param_1 & 0x3f) * 4) = uVar8;

  if (uVar9 > 0x1f) {
    assert_print(0x0103d2a7, 0x0103e47c, 0x17d);
    assert_post_action(0x0103e47c, 0x17d);
  }

  volatile unsigned char * const pf080 = (volatile unsigned char *)(G1_NRF_DPPIC_NS_BASE + 0x80);
  unsigned int idx = ((unsigned int)bVar1 * 8 + 4) & 0xff;
  *(volatile unsigned int *)(pf080 + idx) = uVar8;

  volatile unsigned char * const pbe4 = (volatile unsigned char *)0x2100645d;
  *(volatile unsigned int *)(iVar3 + 0x98) = pbe4[0] | 0x80000000u;

  if (param_2 != 0) {
    volatile unsigned char * const p9000 = (volatile unsigned char *)G1_NRF_TIMER2_NS_BASE;
    *(volatile unsigned int *)(p9000 + 0x80) = uVar7;
  }

  volatile unsigned char * const pf000 = (volatile unsigned char *)G1_NRF_DPPIC_NS_BASE;
  *(volatile unsigned int *)(pf000 + 0x504) = (1u << bVar2) | (1u << uVar9);
}
