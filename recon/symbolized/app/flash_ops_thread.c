#include "g1_app_symbols.h"
/* named: flash_ops_thread */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed flash_ops_thread @ 0x23480  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void);
extern void debug_print(void);
extern int FUN_0002f758(void);
extern void audioStreamFileManagerHandler(void);
extern int FUN_00024678(void);
extern void getQuickNoteBKPQueueCacheData(void);
extern int FUN_00023ef8(void);
extern void SettingStoreHandler(void);
extern void mutex_lock_syscall_handler(void);

void flash_ops_thread(void)
{
    if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 2) {
        if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    do {
        mutex_lock_syscall_handler();
        while (FUN_0002f758() != 0) {
            audioStreamFileManagerHandler();
        }
        while (FUN_00024678() != 0) {
            getQuickNoteBKPQueueCacheData();
        }
        while (FUN_00023ef8() != 0) {
            SettingStoreHandler();
        }
    } while (1);
}

