#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00023480 @ 0x00023480
 * public-name: flash_ops_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   SettingStoreHandler                      <= FUN_00023f04 @ 0x00023f04
 *   getQuickNoteBKPQueueCacheData            <= FUN_00024684 @ 0x00024684
 *   audioStreamFileManagerHandler            <= FUN_0002f94c @ 0x0002f94c
 *   mutex_lock_syscall_handler               <= FUN_00072908 @ 0x00072908
 * address symbols (name @ address):
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
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
    if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
        if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
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
