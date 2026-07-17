/* readable reconstruction; identity: FUN_0101ad38 @ 0x0101ad38
 * public-name: FUN_0101ad38
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_radio_state_get               <= FUN_01019204 @ 0x01019204
 *   controller_radio_event_cleanup           <= FUN_01020634 @ 0x01020634
 * address symbols (name @ address):
 *   g_net_session_state_block                @ 0x210010a0
 *   g_net_session_queue_obj                  @ 0x210010f0
 */
/* net-core FUN_0101ad38 @ 0x101ad38  (parity 300 trials PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
static inline int isCurrentModePrivileged(void){return (__get_CONTROL() & 1u) == 0;}
static inline int isIRQinterruptsEnabled(void){return (int)__get_PRIMASK();}
static inline void disableIRQinterrupts(void){__disable_irq();}
static inline void enableIRQinterrupts(void){__enable_irq();}

extern void sdc_assertion_fail(unsigned int, unsigned int);
extern void FUN_010190d0(void);
extern unsigned char *controller_radio_state_get(void);
extern void FUN_0101920c(int, int);
extern void FUN_01019254(void);
extern void FUN_010196e0(void);
extern void FUN_0101dd0c(int);
extern void FUN_0101de60(int);
extern void controller_radio_event_cleanup(void);
extern void FUN_01022a84(void);
extern int FUN_01022ebc(unsigned char);
extern void FUN_010237b0(unsigned char);
extern void FUN_0102411c(unsigned char);

#define DAT_0101ae48 0x210010a0u
#define DAT_0101ae4c 0x210010f0u

unsigned int FUN_0101ad38(void)
{
  char cVar1;
  int bVar2;
  char *pcVar3;
  unsigned char *puVar4;
  int iVar5;
  unsigned int uVar6;

  pcVar3 = (char *)DAT_0101ae48;
  puVar4 = controller_radio_state_get();
  if ((*pcVar3 != 4) && (*pcVar3 != 5)) {
    return 0xc;
  }
  pcVar3[1] = 1;
  if (pcVar3[0x14] == 0) {
    FUN_010237b0(*puVar4);
    if (puVar4[3] != 0 || (puVar4[4] & 0x1f) != 0) {
      FUN_0101920c(3, 0);
    }
  } else {
    iVar5 = 0;
    bVar2 = isCurrentModePrivileged();
    if (bVar2) {
      iVar5 = isIRQinterruptsEnabled();
    }
    disableIRQinterrupts();
    if (((pcVar3[0x14] != 0) && (pcVar3[0x15] != 0)) &&
        (FUN_010190d0(), pcVar3[0x14] != 0)) {
      controller_radio_event_cleanup();
      FUN_01022a84();
      pcVar3[0x14] = 0;
      pcVar3[0x15] = 0;
    }
    if (iVar5 == 0) {
      enableIRQinterrupts();
    }
  }
  FUN_0102411c(*puVar4);
  if (pcVar3[0x2c] == 0) {
    if ((*pcVar3 == 5) && (*(volatile int *)(pcVar3 + 0x70) == 0)) {
      FUN_0101dd0c(*(volatile int *)(pcVar3 + 0x28) + 0x2d8);
    }
  } else {
    if (*pcVar3 != 5) {
      sdc_assertion_fail(0x21, 0x25b);
      __builtin_unreachable();
    }
    if (*(volatile int *)(pcVar3 + 0x70) != 0) {
      FUN_0101de60(DAT_0101ae4c);
      goto LAB_0101ad88;
    }
  }
  FUN_0101dd0c(DAT_0101ae4c);
LAB_0101ad88:
  pcVar3[1] = 0;
  if (pcVar3[0x2c] == 0) {
    uVar6 = 0;
  } else {
    uVar6 = 0xc;
  }
  FUN_01019254();
  pcVar3[0x2c] = 0;
  cVar1 = *pcVar3;
  pcVar3[2] = 0;
  pcVar3[0x28] = 0;
  pcVar3[0x29] = 0;
  pcVar3[0x2a] = 0;
  pcVar3[0x2b] = 0;
  if (cVar1 == 4) {
    FUN_010196e0();
  }
  *pcVar3 = 0;
  puVar4 = controller_radio_state_get();
  iVar5 = FUN_01022ebc(*puVar4);
  if (iVar5 != 0) {
    *puVar4 = 0x20;
    return uVar6;
  }
  sdc_assertion_fail(0x21, 0x396);
  __builtin_unreachable();
}
