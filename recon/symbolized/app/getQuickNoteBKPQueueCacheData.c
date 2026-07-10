#include "g1_app_symbols.h"
/* named: getQuickNoteBKPQueueCacheData */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20003960  g_quicknote_flash_msgq       
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed getQuickNoteBKPQueueCacheData @ 0x24684  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t undefined4; typedef unsigned int uint;
extern int DEBUG_PRINT(int,...); extern int debug_print(int,...); extern int k_msgq_get(int,...);

int getQuickNoteBKPQueueCacheData(uint param_1,uint param_2,undefined4 param_3)
{
  uint local_30 = param_1, local_2c = param_2; undefined4 uStack_28 = param_3;
  int iVar4 = k_msgq_get(((uintptr_t)&g_quicknote_flash_msgq) /*=0x20003960*/,(int)&local_30,0,0);
  if (iVar4 != 0) {
    if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ < 1) return -1;
    if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) DEBUG_PRINT("%s(): quick note file queue get failed\r\n\n" /*=0x9ef15*/,"getQuickNoteBKPQueueCacheData" /*=0x9f032*/);
    else debug_print(0);
    if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ < 1) return -1;
    iVar4 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
    if (iVar4 != 0) { debug_print(0); return -1; }
    DEBUG_PRINT("%s(): quick note get queue data failed\n" /*=0x9ef3f*/,"QuickNoteStoreHandler" /*=0x9f050*/);
    return -1;
  }
  (void)local_2c; (void)uStack_28;
  return 0;
}

