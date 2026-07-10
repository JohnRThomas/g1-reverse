#include "g1_app_symbols.h"
/* named: revalidate_whitelist_json */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed revalidate_whitelist_json @ 0x355b4  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(const char *msg, const char *file, unsigned int line);
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
  if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ != 0) {
    debug_print();
    return;
  }
  DEBUG_PRINT((const char*)"[%s-%d] malloc failed !!\n" /*=0xa7c9c*/,(const char*)"dump_whitelist" /*=0xa8a24*/,0x277);
  return;
}

