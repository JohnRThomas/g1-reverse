#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01017344 @ 0x01017344
 * public-name: FUN_01017344
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_ble_address_equal                    <= FUN_0100aa3c @ 0x0100aa3c
 *   controller_resolved_address_matches      <= FUN_0100aaac @ 0x0100aaac
 *   sdc_llcp_procedure_slot_get              <= FUN_0100ca68 @ 0x0100ca68
 *   sdc_llcp_get_active_link_index           <= FUN_0100d760 @ 0x0100d760
 *   sdc_packet_header_decode                 <= FUN_01019f9c @ 0x01019f9c
 *   sdc_llcp_release_rx_context              <= FUN_0101fca8 @ 0x0101fca8
 *   sdc_llcp_stop_rx_timeout                 <= FUN_010208b0 @ 0x010208b0
 *   controller_random_window_step            <= FUN_010295d6 @ 0x010295d6
 * address symbols (name @ address):
 *   g_net_ble_pending_channel_idx            @ 0x2100001c
 *   g_sdc_ll_ctx_param                       @ 0x21001019
 */
/* net-core FUN_01017344 @ 0x1017344  (parity 300 trials PROVEN) */
extern int sdc_ble_address_equal(unsigned char, unsigned int, unsigned char, unsigned int);
extern int controller_resolved_address_matches(int, int);
extern int sdc_llcp_procedure_slot_get(unsigned int);
extern unsigned int FUN_0100cb10(void);
extern int FUN_0100cbbc(unsigned int);
extern unsigned char sdc_llcp_get_active_link_index(void);
extern void FUN_010166c0(int, unsigned char*);
extern void sdc_packet_header_decode(unsigned char*, void*);
extern void FUN_0101b54c(int);
extern void sdc_llcp_release_rx_context(void);
extern void sdc_llcp_stop_rx_timeout(void);
extern void controller_random_window_step(unsigned int, int);

#define DAT_01017458 ((unsigned long)&g_net_ble_pending_channel_idx) /*=0x2100001c*/
#define DAT_0101745c G1N_21000f90
#define DAT_01017460 ((unsigned long)&g_sdc_ll_ctx_param) /*=0x21001019*/
#define DAT_01017464 G1N_21000fd6
#define DAT_01017468 G1N_21001014

struct S1017344 {
  char local_40;
  unsigned char local_3f;
  unsigned int local_3c;
  int local_38;
  unsigned char pad[5];
  unsigned char local_2f;
  char local_2e;
};

unsigned char FUN_01017344(unsigned char *param_1)
{
  unsigned char bVar1;
  int bVar2;
  int iVar3;
  unsigned char uVar4;
  int iVar5;
  unsigned int uVar6;
  int iVar7;
  unsigned int uVar8;
  struct S1017344 L;

  uVar4 = sdc_llcp_get_active_link_index();
  bVar1 = *param_1;
  *(volatile unsigned char *)DAT_01017458 = uVar4;
  if ((((bVar1 & 0xf) == 8) &&
       (sdc_packet_header_decode(param_1, &L.local_40), iVar3 = DAT_0101745c, L.local_40 == 0)) &&
      ((L.local_3f & 3) == 3)) {
    if (*(volatile char *)(DAT_0101745c + 0x4d) == 0) {
      bVar1 = *(volatile unsigned char *)(DAT_0101745c + 0x78);
    } else {
      bVar1 = *(volatile unsigned char *)(DAT_0101745c + 0x7b);
    }
    uVar8 = (unsigned int)bVar1;
    if ((*(volatile char *)(DAT_0101745c + 0x7c) == 0) || (uVar6 = FUN_0100cb10(), uVar6 == 0xff)) {
      bVar2 = 0;
    } else {
      *(volatile char *)(iVar3 + 0x79) = (char)uVar6;
      bVar2 = uVar6 == uVar8;
    }
    iVar5 = sdc_ble_address_equal(L.local_2f, L.local_3c, *(volatile unsigned char *)(iVar3 + 0x90), DAT_01017460);
    if ((iVar5 == 0) && (!bVar2)) {
      return 1;
    }
    uVar4 = *(volatile unsigned char *)(iVar3 + 0x45);
    iVar5 = DAT_01017464;
    if ((*(volatile char *)(iVar3 + 0x7d) != 0) &&
        (iVar7 = FUN_0100cbbc(uVar8), iVar5 = DAT_01017464, iVar7 != 0)) {
      uVar4 = 1;
      iVar5 = iVar7;
    }
    if ((L.local_2e == 1) && ((*(volatile unsigned char *)(L.local_38 + 5) & 0xc0) == 0x40)) {
      iVar5 = sdc_ble_address_equal(1, L.local_38, uVar4, iVar5);
      if (iVar5 != 0) goto LAB_010173d0;
      if (uVar8 == 0xff) {
        return 1;
      }
      iVar5 = sdc_llcp_procedure_slot_get(uVar8);
      if (iVar5 == 0) {
        return 1;
      }
      iVar5 = controller_resolved_address_matches(iVar5, L.local_38);
    } else {
      iVar5 = sdc_ble_address_equal(L.local_2e, L.local_38, uVar4, iVar5);
    }
    if (iVar5 != 0) {
LAB_010173d0:
      controller_random_window_step(DAT_01017468, 1);
      if (*(volatile char *)(iVar3 + 0x7c) != 0) {
        sdc_llcp_stop_rx_timeout();
        sdc_llcp_release_rx_context();
        *(volatile unsigned char *)(iVar3 + 0x7c) = 0;
      }
      FUN_010166c0(1, param_1);
      FUN_0101b54c(3);
      return 0;
    }
  }
  return 1;
}
