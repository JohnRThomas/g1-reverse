#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100aff4 @ 0x0100aff4
 * public-name: FUN_0100aff4
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_radio_request_configure       <= FUN_0101fdd0 @ 0x0101fdd0
 * address symbols (name @ address):
 *   g_net_radio_drv_ctx                      @ 0x21000c48
 *   g_ll_conn_trace_ctx_addr                 @ 0x21000cd0
 */
/* net-core FUN_0100aff4 @ 0x100aff4  (parity 300 trials PROVEN) */
extern void sdc_assertion_fail(unsigned int, unsigned int, ...);
extern void FUN_0100ac34(void);
extern int FUN_0100aeac(int);
extern void FUN_0100af3c(void);
extern void controller_radio_request_configure(int, unsigned int, unsigned char, unsigned char, int);

#define DAT_0100b10c ((unsigned long)&g_net_radio_drv_ctx) /*=0x21000c48*/
#define DAT_0100b110 ((unsigned long)&g_ll_conn_trace_ctx_addr) /*=0x21000cd0*/

typedef int (*fp0_t)(void);
typedef void (*fp1_t)(int);
typedef int (*fp2_t)(int);

void FUN_0100aff4(int param_1, int param_2)
{
  unsigned short uVar1;
  unsigned char uVar2;
  int iVar3;
  unsigned char *pbVar4;
  char cVar5;
  unsigned int uVar6;
  int iVar7;
  unsigned char uVar8;

  iVar3 = DAT_0100b10c;
  iVar7 = *(volatile int *)(DAT_0100b10c + 0x28);
  if (*(volatile char *)(DAT_0100b10c + 0x44) != 1) {
    sdc_assertion_fail(0x27, 0x46e);
    return;
  }
  if (*(volatile char *)(iVar7 + 0xb8) != 0) {
    uVar1 = *(volatile unsigned short *)(DAT_0100b10c + 0x32);
    *(volatile unsigned char *)(iVar7 + 0xb8) = 0;
    *(volatile unsigned short *)(iVar3 + 0x32) = uVar1 | 4;
    ((fp1_t)(*(volatile unsigned int *)(iVar3 + 0x34)))(4);
    if (*(volatile char *)(iVar3 + 0x24) != 0) {
      *(volatile unsigned char *)(iVar7 + 0xba) = 1;
    }
  }
  pbVar4 = *(unsigned char **)(iVar3 + 0x7c);
  if ((*pbVar4 & 3) == 3) {
    if (*(volatile char *)(iVar7 + 0xbe) == 0) {
      *(volatile unsigned short *)(iVar3 + 0x32) = *(volatile unsigned short *)(iVar3 + 0x32) | 2;
      ((fp1_t)(*(volatile unsigned int *)(iVar3 + 0x34)))(2);
      pbVar4 = *(unsigned char **)(iVar3 + 0x7c);
      if ((*pbVar4 & 3) != 3) goto LAB_0100b03e;
    }
    *(volatile unsigned char *)(iVar7 + 0xbe) = 3;
  } else {
LAB_0100b03e:
    if (pbVar4[1] == 0) {
      *(volatile unsigned char *)(iVar7 + 0xbe) = 1;
    } else {
      *(volatile unsigned char *)(iVar7 + 0xbe) = 2;
    }
  }
  if (*(volatile char *)(iVar7 + 0xcb) != 0) {
    uVar2 = *(volatile unsigned char *)(*(volatile int *)(iVar3 + 0x28) + 0x6f);
    cVar5 = *(volatile char *)(iVar3 + 0x24);
    if (cVar5 != 0) {
      cVar5 = 1;
    }
    *(volatile char *)(iVar3 + 0xa0) = cVar5;
    uVar6 = *(volatile unsigned int *)(iVar7 + 300);
    *(volatile unsigned int *)(iVar3 + 0x98) = *(volatile unsigned int *)(iVar7 + 0x128);
    *(volatile unsigned int *)(iVar3 + 0x9c) = uVar6;
    uVar8 = 1;
    switch (uVar2) {
    case 1:
      uVar8 = 0;
      break;
    case 2:
      break;
    case 4:
      uVar8 = 3;
      break;
    case 8:
      uVar8 = 2;
      break;
    default:
      sdc_assertion_fail(6, 0x3c5, *(volatile unsigned char *)(iVar3 + 0x7a));
      return;
    }
    controller_radio_request_configure(1, DAT_0100b110, *(volatile unsigned char *)(iVar3 + 0x7a), uVar8, 0);
  }
  if ((((param_2 == 1) && (param_1 == 0)) &&
       (iVar7 = ((fp2_t)(*(volatile unsigned int *)(iVar3 + 0xc0)))(0), iVar7 != 0)) &&
      ((*(volatile char *)(iVar3 + 0x3d) == 0) && (iVar3 = FUN_0100aeac(0), iVar3 == 0))) {
    FUN_0100af3c();
    return;
  }
  FUN_0100ac34();
  return;
}
