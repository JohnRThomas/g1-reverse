#include "g1_app_symbols.h"
/* named: runtime_info_sync */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed runtime_info_sync @ 0x16268  (parity: 300/300 trials, PROVEN) */

extern int global_ipc_service_send(void*, int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(void);

unsigned int runtime_info_sync(unsigned short *param_1)
{
    unsigned int local_18;
    unsigned int local_14;
    unsigned int uVar1;
    unsigned char *b = (unsigned char*)param_1;

    local_18 = ((unsigned int)(*param_1) << 16) | 1;
    local_14 = (unsigned int)b[2] | ((unsigned int)b[3] << 8) | ((unsigned int)b[4] << 16);
    uVar1 = global_ipc_service_send(&local_18, 8);
    if (*(volatile unsigned char*)((uintptr_t)&g_esb_bringup_log_pending_flag) /*=0x20002fe0*/ != 0) {
        *(volatile unsigned char*)((uintptr_t)&g_esb_bringup_log_pending_flag) /*=0x20002fe0*/ = 0;
        if (1 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): --role:%d --mode:%d, esb_channel %d --ret:%d esb_master_addr %02X esb_slave_addr %02X\n" /*=0x9957c*/, "runtime_info_sync" /*=0x99bee*/,
                    (local_18 >> 16) & 0xff, local_18 >> 24,
                    local_14 & 0xff, uVar1,
                    (unsigned int)b[3], (unsigned int)b[4]);
            } else {
                debug_print();
            }
        }
    }
    return uVar1;
}

