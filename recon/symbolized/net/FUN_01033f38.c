#include "g1_net_symbols.h"
/* net-core FUN_01033f38 @ 0x1033f38  (parity 300 trials PROVEN) */
extern int FUN_01034464(unsigned char);
extern int FUN_0103448c(unsigned char);
extern void FUN_01039bbe(int, int, unsigned int);
extern void FUN_01039bb0(int, unsigned int);

void FUN_01033f38(void)
{
  int r0, r4, r5;

  *(volatile int *)(REG_4100f000 /*=0x4100f000*/ + 0x508) = 1 << *(volatile unsigned char *)((uintptr_t)&g_esb_ppi_ch_id_3) /*=0x2100645d*/;
  *(volatile int *)(REG_41008000 /*=0x41008000*/ + 0x190) = 0;
  r0 = FUN_01034464(*(volatile unsigned char *)((uintptr_t)&g_esb_ppi_ch_id_6) /*=0x21006460*/);
  r5 = r0;
  if (r5 != 0x0bad0000) goto L_abort;

L_chain2:
  r4 = FUN_01034464(*(volatile unsigned char *)((uintptr_t)&g_esb_ppi_ch_id_5) /*=0x2100645f*/);
  if (r4 != r5) goto L_abort;

  r5 = FUN_01034464(*(volatile unsigned char *)((uintptr_t)&g_net_radio_trx_ppi_ch_e) /*=0x2100645e*/);
  if (r5 != r4) goto L_abort;

  r4 = FUN_01034464(*(volatile unsigned char *)((uintptr_t)&g_esb_ppi_ch_id_3) /*=0x2100645d*/);
  if (r4 != r5) goto L_abort;

  r5 = FUN_01034464(*(volatile unsigned char *)((uintptr_t)&g_154_dppi_channel_ack) /*=0x2100645c*/);
  if (r5 != r4) goto L_abort;

  r4 = FUN_01034464(*(volatile unsigned char *)((uintptr_t)&g_esb_ppi_ch_id_1) /*=0x2100645b*/);
  if (r4 != r5) goto L_abort;

  r0 = FUN_0103448c(*(volatile unsigned char *)((uintptr_t)&g_net_radio_trx_ppi_ch_a) /*=0x2100645a*/);
  if (r0 != r4) goto L_abort;

  return;

L_abort:
  FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, ((uintptr_t)&rodata_103e4f5) /*=0x103e4f5*/, 0x13b);
  FUN_01039bb0(((uintptr_t)&rodata_103e4f5) /*=0x103e4f5*/, 0x13b);
  goto L_chain2;
}

