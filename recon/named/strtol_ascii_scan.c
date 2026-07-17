/* readable reconstruction; identity: FUN_00077c1c @ 0x00077c1c
 * public-name: strtol_ascii_scan
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strtol_ascii_scan                        <= FUN_00077c1c @ 0x00077c1c
 * address symbols (name @ address):
 *   g_libc_heap_ctrl                         @ 0x20002d20
 */
/* Reconstructed FUN_00077c1c @ 0x77c1c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern unsigned FUN_00077b38(int, unsigned char*, void*, unsigned);
unsigned strtol_ascii_scan(unsigned char *param_1, void *param_2, unsigned param_3)
{
  return FUN_00077b38(*(volatile int*)0x20002d20, param_1, param_2, param_3);
}
