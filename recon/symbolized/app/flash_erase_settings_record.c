#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000230bc @ 0x000230bc
 * public-name: flash_erase_settings_record
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_settings_write_and_verify          <= FUN_00022658 @ 0x00022658
 *   flash_erase_settings_record              <= FUN_000230bc @ 0x000230bc
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed FUN_000230bc @ 0x230bc  (parity: 300/300 trials, PROVEN) */

extern unsigned int memset_bytes(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern void flash_settings_write_and_verify(unsigned int, unsigned int, unsigned int);

unsigned int flash_erase_settings_record(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int uVar1;

  uVar1 = memset_bytes(param_1 + 0x10c6,0xff,0xc0,param_1 + 0x10c6,param_4);
  flash_settings_write_and_verify(0x00135000UL,uVar1,0xc0);
  return 0;
}
