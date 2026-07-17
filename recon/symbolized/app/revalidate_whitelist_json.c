#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000355b4 @ 0x000355b4
 * public-name: revalidate_whitelist_json
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   convert_app_whitelist_to_json            <= FUN_000352e8 @ 0x000352e8
 *   revalidate_whitelist_json                <= FUN_000355b4 @ 0x000355b4
 *   malloc                                   <= FUN_00076d6c @ 0x00076d6c
 *   heap_free                                <= FUN_00076d7c @ 0x00076d7c
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_a7c9c                             @ 0x000a7c9c
 *   rodata_a8a24                             @ 0x000a8a24
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_000355b4 @ 0x355b4  (parity: 300/300 trials, PROVEN) */

extern void log_message(const char *msg, const char *file, unsigned int line);
extern int debug_print(void);
extern int convert_app_whitelist_to_json(int);
extern int malloc(int);
extern int heap_free(int);
extern int memset_bytes(int, int, int);

void revalidate_whitelist_json(void)
{
  int iVar1;

  iVar1 = malloc(0x1800);
  if (iVar1 != 0) {
    memset_bytes(iVar1,0,0x15e3);
    convert_app_whitelist_to_json(iVar1);
    heap_free(iVar1);
    return;
  }
  if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ != 0) {
    debug_print();
    return;
  }
  log_message((const char*)((unsigned long)&rodata_a7c9c) /*=0xa7c9c*/,(const char*)((unsigned long)&rodata_a8a24) /*=0xa8a24*/,0x277);
  return;
}
