#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010128bc @ 0x010128bc
 * public-name: FUN_010128bc
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_work_submit                          <= FUN_0100ef88 @ 0x0100ef88
 *   sdc_hci_event_suppressed                 <= FUN_0101f888 @ 0x0101f888
 * address symbols (name @ address):
 *   rodata_1011869                           @ 0x01011869
 *   rodata_1011add                           @ 0x01011add
 */
/* net-core FUN_010128bc @ 0x10128bc  (parity 300 trials PROVEN) */
#define C_0101295c ((unsigned long)&rodata_1011869) /*=0x1011869*/
#define C_01012958 ((unsigned long)&rodata_1011add) /*=0x1011add*/

extern void sdc_work_submit(void *, int, int, int, unsigned int);
extern int sdc_hci_event_suppressed(void);

void FUN_010128bc(unsigned char *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned short uVar1;
  int uVar2;
  int iVar3;
  unsigned char cVar4;
  unsigned int uVar5;

  uVar5 = *(unsigned short *)(param_1 + 2);
  if ((int)(uVar5 << 0x1c) < 0) {
    *(volatile unsigned char *)(param_1 + 0x85) = 0x3c;
    uVar1 = **(unsigned short **)(param_1 + 0x1c);
    *(volatile unsigned char *)(param_1 + 0xa3) = 0xff;
    *(volatile unsigned short *)(param_1 + 0x86) = uVar1;
    *(volatile unsigned short *)(param_1 + 0xa4) = 0xffff;
    sdc_work_submit(param_1 + 0x7c, C_0101295c, 2, 0xffff, param_4);
    uVar5 = *(unsigned short *)(param_1 + 2);
  }
  if ((int)(uVar5 << 0x1f) < 0) {
    uVar1 = **(unsigned short **)(param_1 + 0x1c);
    iVar3 = sdc_hci_event_suppressed();
    if (iVar3 != 0) goto LAB_end;
    cVar4 = param_1[0xd];
    *(volatile unsigned short *)(param_1 + 0xb1) = uVar1;
    *(volatile unsigned char *)(param_1 + 0xb0) = *param_1;
    *(volatile unsigned char *)(param_1 + 0xaf) = 0x3c;
    uVar2 = C_01012958;
  } else {
    iVar3 = sdc_hci_event_suppressed();
    if (iVar3 != 0) goto LAB_end;
    cVar4 = param_1[0xd];
    *(volatile unsigned char *)(param_1 + 0xb0) = *param_1;
    *(volatile unsigned char *)(param_1 + 0xb1) = 0xff;
    *(volatile unsigned char *)(param_1 + 0xb2) = 0xff;
    *(volatile unsigned char *)(param_1 + 0xaf) = 0x3c;
    uVar2 = C_01012958;
  }
  if (cVar4 != 0) {
    cVar4 = param_1[0x40];
  }
  *(volatile unsigned char *)(param_1 + 0xb3) = cVar4;
  sdc_work_submit(param_1 + 0xa6, uVar2, 2, cVar4, param_4);
LAB_end:
  *(volatile unsigned char *)(param_1 + 0x79) = 1;
  return;
}
