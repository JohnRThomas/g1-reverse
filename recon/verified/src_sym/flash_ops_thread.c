/* Reconstructed flash_ops_thread @ 0x23480  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void);
extern void debug_print(void);
extern int FUN_0002f758(void);
extern void audioStreamFileManagerHandler(void);
extern int FUN_00024678(void);
extern void getQuickNoteBKPQueueCacheData(void);
extern int FUN_00023ef8(void);
extern void SettingStoreHandler(void);
extern void FUN_00072908(void);

void flash_ops_thread(void)
{
    if (*(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */ > 2) {
        if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    do {
        FUN_00072908();
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

