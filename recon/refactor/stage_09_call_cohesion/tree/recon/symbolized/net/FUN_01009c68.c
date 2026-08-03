#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01009c68 @ 0x01009c68
 * public-name: FUN_01009c68
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_handle_slot_find_from         <= FUN_0102741e @ 0x0102741e
 *   controller_handle_slot_find              <= FUN_01027470 @ 0x01027470
 *   controller_handle_slot_value_ptr         <= FUN_010274ea @ 0x010274ea
 *   controller_handle_slot_value_set         <= FUN_0102751a @ 0x0102751a
 */
/* net-core FUN_01009c68 @ 0x1009c68  (parity 300 trials PROVEN) */

extern void sdc_assertion_fail(unsigned int, unsigned int);
extern signed char controller_handle_slot_find_from(void *, unsigned int, signed char);
extern signed char controller_handle_slot_find(void *, unsigned short);
extern unsigned int controller_handle_slot_value_ptr(void *, signed char);
extern unsigned int controller_handle_slot_value_set(void *, unsigned short, signed char);

unsigned int FUN_01009c68(unsigned int event_counter_raw,
                          unsigned int channel_raw)
{
  /* Firmware normalizes the incoming register values through STRH/LDRH and
   * STRB/LDRB.  Do it explicitly rather than relying on narrow-argument ABI
   * extension, because callers may leave non-semantic upper bits in r0/r1. */
  const unsigned short event_counter = (unsigned short)event_counter_raw;
  const unsigned char channel = (unsigned char)channel_raw;
  volatile int * const tbl = (volatile int *)G1N_21000b7c;
  int iVar3 = tbl[channel];
  if (iVar3 == 0) {
    return 0;
  }
  if (event_counter > 0xeff) {
    sdc_assertion_fail(0x17, 0x27e);
  }
  signed char cVar1 = controller_handle_slot_find((void *)iVar3, event_counter);
  if (cVar1 != -1) {
    return controller_handle_slot_value_ptr((void *)iVar3, cVar1);
  }
  signed char divv = *(volatile unsigned char *)(iVar3 + 2);
  signed char cVar1b = (signed char)event_counter -
                       (signed char)((short)event_counter / divv) * divv;
  signed char cVar2 = controller_handle_slot_find_from((void *)iVar3, 0xfff0, cVar1b);
  if (cVar2 == -1) {
    return 0;
  }
  if (cVar2 != cVar1b) {
    *(volatile unsigned char *)(iVar3 + 3) = 0;
  }
  return controller_handle_slot_value_set((void *)iVar3, event_counter, cVar2);
}
