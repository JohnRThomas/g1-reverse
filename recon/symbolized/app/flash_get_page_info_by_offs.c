#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083a92 @ 0x00083a92
 * public-name: flash_get_page_info_by_offs
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_get_page_info                      <= FUN_00083a2c @ 0x00083a2c
 *   flash_get_page_info_by_offs              <= FUN_00083a92 @ 0x00083a92
 */
/* Reconstructed FUN_00083a92 @ 0x83a92  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern uint32_t flash_get_page_info(int,int,int,int);
uint32_t flash_get_page_info_by_offs(int param_1,int param_2,int param_3){
  return flash_get_page_info(param_1,param_2,0,param_3);
}
