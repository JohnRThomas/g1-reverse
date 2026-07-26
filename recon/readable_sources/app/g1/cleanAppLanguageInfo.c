#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00023b78 @ 0x00023b78
 * public-name: cleanAppLanguageInfo
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 * address symbols (name @ address):
 *   rodata_9e903                             @ 0x0009e903   [INLINED -- G6 literal batch]
 *   rodata_9e968                             @ 0x0009e968   [INLINED -- G6 literal batch]
 *   rodata_9ed8f                             @ 0x0009ed8f   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_flash_store_cmd_msgq                   @ 0x20003994
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_language_msgq                      @ 0x200079e4
 */
/* Reconstructed cleanAppLanguageInfo @ 0x23b78  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_put(void*, void*, int, int);
extern void k_sem_give(void*);

int cleanAppLanguageInfo(unsigned int param_1, unsigned int param_2)
{
  int iVar1;
  int uVar2;
  unsigned char buf[8];

  buf[0] = 2;
  *(unsigned int*)&buf[1] = 0;
  buf[5] = 0;
  iVar1 = k_msgq_put((void*)((unsigned long)&g_flash_store_cmd_msgq) /*=0x20003994*/, buf, 0, 0);
  if (iVar1 == 0) {
    if (*(int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
      if (*(int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
        log_message(((unsigned long)"%s(): SEND APP Language Command...\n") /*=0x9e968*/, ((unsigned long)"cleanAppLanguageInfo") /*=0x9ed8f*/);
      } else {
        debug_print(((unsigned long)"%s(): SEND APP Language Command...\n") /*=0x9e968*/, ((unsigned long)"cleanAppLanguageInfo") /*=0x9ed8f*/);
      }
    }
    k_sem_give((void*)((unsigned long)&g_app_language_msgq) /*=0x200079e4*/);
    uVar2 = 0;
  } else {
    if (*(int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
      if (*(int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
        log_message(((unsigned long)"%s(): setting flash store queue fill failed\r\n\n") /*=0x9e903*/, ((unsigned long)"cleanAppLanguageInfo") /*=0x9ed8f*/);
      } else {
        debug_print(((unsigned long)"%s(): setting flash store queue fill failed\r\n\n") /*=0x9e903*/, ((unsigned long)"cleanAppLanguageInfo") /*=0x9ed8f*/);
      }
    }
    uVar2 = -1;
  }
  return uVar2;
}
