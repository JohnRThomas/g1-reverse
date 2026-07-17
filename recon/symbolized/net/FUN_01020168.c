#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01020168 @ 0x01020168
 * public-name: FUN_01020168
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 * address symbols (name @ address):
 *   rodata_103c4d0                           @ 0x0103c4d0
 *   REG_41008000                             @ 0x41008000
 */
/* net-core FUN_01020168 @ 0x1020168  (parity 300 trials PROVEN) */

extern void sdc_assertion_fail(unsigned int a, unsigned int b);
extern void FUN_010216d4(unsigned int a, unsigned int b, int c, void *d);
extern void FUN_010215a8(int a);
extern unsigned int FUN_010218fc(void *a);

void FUN_01020168(unsigned int param_1)
{
  volatile unsigned char *iVar4 = (volatile unsigned char *)0x210015f0;
  volatile unsigned char *base230 = (volatile unsigned char *)REG_41008000 /*=0x41008000*/;
  volatile unsigned char *base234 = (volatile unsigned char *)0x01ff0000;
  volatile unsigned char *base238 = (volatile unsigned char *)((unsigned long)&rodata_103c4d0) /*=0x103c4d0*/;
  signed char cVar1;
  unsigned int uVar5;
  signed char local_14;
  unsigned char auStack_13[7];
  unsigned int r;

  *(volatile unsigned char *)(iVar4 + 0x18) = (unsigned char)param_1;

  switch (param_1) {
  case 1:
    *(volatile unsigned int *)(base230 + 0x510) = 3;
    break;
  case 2:
    *(volatile unsigned int *)(base230 + 0x510) = 4;
    *(volatile unsigned int *)(base230 + 0x588) = *(volatile unsigned int *)(base234 + 0x84);
    goto LAB_01020194;
  case 4:
    *(volatile unsigned int *)(base230 + 0x510) = 6;
    break;
  case 8:
    *(volatile unsigned int *)(base230 + 0x510) = 5;
    break;
  default:
    sdc_assertion_fail(0x3e, 0xd35);
    return;
  }
  *(volatile unsigned int *)(base230 + 0x588) = *(volatile unsigned int *)(base234 + 0x80);
LAB_01020194:
  uVar5 = (unsigned int)*(volatile unsigned char *)(iVar4 + 0x1a);
  cVar1 = *(volatile signed char *)(iVar4 + 8);
  *(volatile unsigned int *)(base230 + 0x508) = (unsigned int)*(volatile unsigned char *)(base238 + uVar5);
  *(volatile unsigned int *)(base230 + 0x554) = uVar5 & 0x7f;
  if (cVar1 == 1) {
    FUN_010216d4((unsigned int)*(volatile unsigned char *)(iVar4 + 10), uVar5,
                 (int)*(volatile signed char *)(iVar4 + 0x19), &local_14);
    FUN_010215a8((int)local_14);
    r = FUN_010218fc(auStack_13);
    if (r != 0) {
      sdc_assertion_fail(0x3e, 0x57e);
      return;
    }
  }
  *(volatile unsigned int *)(base230 + 0x200) |= 0x110;
  *(volatile unsigned int *)(base230 + 0x568) |= 0x60000;
}
