#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102b5bc @ 0x0102b5bc
 * public-name: FUN_0102b5bc
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103d18c                           @ 0x0103d18c
 *   rodata_103d19e                           @ 0x0103d19e
 *   rodata_103d1b8                           @ 0x0103d1b8
 *   g_zephyr_log_level                       @ 0x21000580
 *   g_net_ipc_msg_data                       @ 0x21004628
 *   g_net_ipc_msg_type                       @ 0x21004fa2
 */
/* net-core FUN_0102b5bc @ 0x102b5bc  (parity 300 trials PROVEN)
 * CFG_VERIFY_PREFIX_FIRST: the successful submission path busy-waits for an
 * asynchronous completion flag written by hardware/ISR code. */
#define P_0102b640 ((unsigned long)&g_net_ipc_msg_data) /*=0x21004628*/
#define C_0102b644 0xf0000010
#define P_0102b648 ((unsigned long)&g_net_ipc_msg_type) /*=0x21004fa2*/
#define C_0102b64c 0x418c0500
#define P_0102b650 ((unsigned long)&g_zephyr_log_level) /*=0x21000580*/
#define P_0102b654 ((unsigned long)&rodata_103d18c) /*=0x103d18c*/
#define P_0102b658 ((unsigned long)&rodata_103d19e) /*=0x103d19e*/
#define P_0102b65c ((unsigned long)&rodata_103d1b8) /*=0x103d1b8*/
#define P_0102b660 0x0102bf59

extern int FUN_0103037c(int);
extern int FUN_0102ca80(int, void *);
extern void FUN_01039722(int, int);
extern void FUN_0102bba8(int);

int FUN_0102b5bc(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int uVar1;
  int iVar2;
  int iVar3;
  unsigned int uStack_18;
  unsigned int local_14;
  volatile unsigned int local_10;
  int local_c;

  uVar1 = C_0102b644;
  *(volatile unsigned int *)P_0102b640 = param_2;
  *(volatile unsigned char *)P_0102b648 = (unsigned char)param_1;
  iVar2 = C_0102b64c;
  *(volatile unsigned int *)(iVar2 + 0x18) = uVar1;
  *(volatile unsigned int *)(iVar2 + 0xc) = 0xf0000000;
  uStack_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  iVar2 = FUN_0103037c(0);
  if (iVar2 == 0) {
    if (0 < *(volatile int *)P_0102b650) {
      FUN_01039722(P_0102b654, 0);
    }
    iVar3 = -6;
  } else {
    local_14 = 0;
    local_c = 0;
    local_10 = 1;
    iVar3 = FUN_0102ca80(iVar2, &uStack_18);
    iVar2 = local_c;
    if (iVar3 < 0) {
      if (0 < *(volatile int *)P_0102b650) {
        FUN_01039722(P_0102b658, iVar3);
      }
    } else {
      while ((local_10 & 3) != 0) { }
      if (local_c != 0) {
        if (0 < *(volatile int *)P_0102b650) {
          FUN_01039722(P_0102b65c, local_c);
        }
        if (iVar2 < 0) {
          return iVar2;
        }
      }
      FUN_0102bba8(P_0102b660);
      iVar3 = 0;
    }
  }
  return iVar3;
}
