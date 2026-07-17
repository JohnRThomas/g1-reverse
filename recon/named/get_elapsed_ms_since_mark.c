/* readable reconstruction; identity: FUN_00024d2c @ 0x00024d2c
 * public-name: get_elapsed_ms_since_mark
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_elapsed_ms_since_mark                <= FUN_00024d2c @ 0x00024d2c
 * address symbols (name @ address):
 *   g_elapsed_time_mark                      @ 0x20007a28
 */
/* Reconstructed FUN_00024d2c @ 0x24d2c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int thunk_FUN_00074f68(void);
int get_elapsed_ms_since_mark(void)
{
  int iVar1;
  iVar1 = thunk_FUN_00074f68();
  return iVar1 - *(volatile int32_t*)0x20007a28UL;
}
