#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01008ddc @ 0x01008ddc
 * public-name: FUN_01008ddc
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_layout_count_table                 @ 0x21000a30
 */
/* net-core FUN_01008ddc @ 0x1008ddc  (parity 300 trials PROVEN) */
extern unsigned int g1_irq_lock(void);
extern void g1_irq_unlock(unsigned int key);

#define P_01008e6c ((unsigned long)&g_net_layout_count_table) /*=0x21000a30*/
#define C_01008e70 0x0100957d

extern int FUN_0102575c(void);
extern unsigned int FUN_010246cc(void);
extern void FUN_010093ac(int);
extern void FUN_01025a84(void *, int, int);
extern void FUN_0100a790(void);

int FUN_01008ddc(int param_1)
{
  int iVar3;
  unsigned int uVar5;
  int uVar4;

  if (param_1 == 0) {
    return -0x16;
  }
  iVar3 = FUN_0102575c();
  if (iVar3 == 0) {
    return -1;
  }
  uVar5 = FUN_010246cc();
  if (500 < uVar5) {
    return -1;
  }
  *(volatile int *)(P_01008e6c + 0x14) = param_1;
  FUN_010093ac(C_01008e70);
  *(volatile unsigned char *)(P_01008e6c + 0x2c) = 0;
  *(volatile unsigned char *)(P_01008e6c + 0x2d) = 0;
  *(volatile unsigned char *)(P_01008e6c + 0x1f) = 0;
  *(volatile unsigned char *)(P_01008e6c + 0x20) = 0;
  *(volatile unsigned int *)(P_01008e6c + 0x24) = 0;
  *(volatile unsigned char *)(P_01008e6c + 0x1e) = 0;
  FUN_01025a84((void *)P_01008e6c, 0, 0x1e);
  *(volatile unsigned char *)(P_01008e6c + 5) = 0x1b;
  *(volatile unsigned short *)(P_01008e6c + 0) = 0x101;
  *(volatile unsigned short *)(P_01008e6c + 6) = 0x31b;
  *(volatile unsigned char *)(P_01008e6c + 2) = 1;
  *(volatile unsigned short *)(P_01008e6c + 8) = 0x302;
  *(volatile unsigned char *)(P_01008e6c + 0x14) = 1;
  *(volatile unsigned short *)(P_01008e6c + 0xa) = 0x1f;
  *(volatile unsigned short *)(P_01008e6c + 0xc) = 0x208;
  *(volatile unsigned short *)(P_01008e6c + 0x10) = 0x4901;

  iVar3 = (int)g1_irq_lock();
  FUN_0100a790();
  g1_irq_unlock((unsigned int)iVar3);
  uVar4 = 0;
  return uVar4;
}
