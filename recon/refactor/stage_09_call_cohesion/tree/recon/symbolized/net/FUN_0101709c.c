#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101709c @ 0x0101709c
 * public-name: FUN_0101709c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_llcp_note_unsupported_pdu            <= FUN_01020500 @ 0x01020500
 * address symbols (name @ address):
 *   g_net_ble_pending_channel_idx            @ 0x2100001c
 */
/* net-core FUN_0101709c @ 0x101709c  (parity 300 trials PROVEN) */

extern void FUN_01016828(void);
extern unsigned int FUN_01017018(unsigned int, unsigned int);
extern int FUN_01019aa0(void *, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, int, int);
extern void FUN_01019660(void);
extern void FUN_010196e0(void);
extern void FUN_01019aa0_unused(void);
extern void sdc_llcp_note_unsupported_pdu(void);

unsigned int FUN_0101709c(char *param_1, unsigned int param_2)
{
  volatile unsigned char * const iVar4 = (volatile unsigned char *)G1N_21000f90;
  volatile signed char * const p714c = (volatile signed char *)((unsigned long)&g_net_ble_pending_channel_idx) /*=0x2100001c*/;

  if (iVar4[0x82] == 0) {
    return 0;
  }
  if (iVar4[0xa8] == 0) {
    unsigned char uVar7 = (*(volatile unsigned char *)param_1 == 0) ? 1 : 2;
    iVar4[0xa8] = uVar7;
  }

  int iVar8;
  unsigned char t70 = iVar4[0x70];
  if (t70 == 8) {
    iVar8 = 3;
  } else if (t70 == 9) {
    iVar8 = 2;
  } else {
    iVar8 = 1;
  }

  signed char cVar3 = *p714c;
  if (cVar3 == 0x7f) {
    FUN_01016828();
    for (;;) { FUN_01016828(); }
  }

  unsigned char uVar7b = iVar4[0x79];
  unsigned char uVar2 = iVar4[0x8f];
  *p714c = 0x7f;

  int iVar5 = FUN_01019aa0((void *)param_1, param_2, G1N_21000fd6, iVar4[0xb9], uVar2, uVar7b, (int)cVar3, iVar8);

  if (iVar5 == 0) {
    if (iVar8 == 2) {
      return 0;
    }
  } else {
    unsigned char bVar1 = ((volatile unsigned char *)param_1)[1];
    if ((bVar1 & 0x10) == 0) {
      FUN_01019660();
      return bVar1 & 0x10;
    }
    unsigned int uVar6 = FUN_01017018(2, *(volatile unsigned int *)(param_1 + 0x18));
    if (uVar6 != 0) {
      iVar4[0x88] = 0;
      sdc_llcp_note_unsupported_pdu();
      return uVar6;
    }
  }
  FUN_010196e0();
  return 0;
}
