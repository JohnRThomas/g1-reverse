#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005cc68 @ 0x0005cc68
 * public-name: smp_dhkey_generate
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   hci_le_generate_dhkey                    <= FUN_00055e74 @ 0x00055e74
 *   smp_dhkey_generate                       <= FUN_0005cc68 @ 0x0005cc68
 *   atomic_clear_bit_1                       <= FUN_0008304c @ 0x0008304c
 *   smp_log_message                          <= FUN_00083074 @ 0x00083074
 *   atomic_set_bit                           <= FUN_00083090 @ 0x00083090
 * address symbols (name @ address):
 *   ADDR_smp_dhkey_ready_cb_THUMB            @ 0x0008349d
 *   rodata_88180                             @ 0x00088180
 *   rodata_f4e47                             @ 0x000f4e47
 */
/* Reconstructed FUN_0005cc68 @ 0x5cc68  (parity: 300/300 trials, PROVEN) */

extern void atomic_set_bit(int a, int b);
extern int hci_le_generate_dhkey(int a, int b);
extern void atomic_clear_bit_1(volatile long*, int);
extern void smp_log_message(int a, int b, void *c);

int smp_dhkey_generate(int param_1)
{
  int iVar1;
  unsigned int local_18;
  unsigned int local_14;

  atomic_set_bit(param_1 + 4, 8);
  iVar1 = hci_le_generate_dhkey(param_1 + 0x57, ADDR_smp_dhkey_ready_cb_THUMB /*=0x8349d*/);
  if (iVar1 != 0) {
    atomic_clear_bit_1(param_1 + 4, 8);
    local_14 = ((unsigned long)&rodata_f4e47) /*=0xf4e47*/;
    local_18 = 2;
    smp_log_message(((unsigned long)&rodata_88180) /*=0x88180*/, 0x1040, &local_18);
    iVar1 = 8;
  }
  return iVar1;
}
