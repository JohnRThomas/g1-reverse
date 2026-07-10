#include "g1_app_symbols.h"
/* named: send_data_in_ble_chunks */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed send_data_in_ble_chunks @ 0x3384c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(void);
extern void strlen(void);
extern int get_device_info(void);
extern int debug_print(void);
extern int FUN_00033730(void);
extern int strncmp(void);

int send_data_in_ble_chunks(int param_1)
{
    int iVar4;
    int cVar5;

    if (param_1 == 0) return 0;
    cVar5 = 9;
    do {
        strlen();
        iVar4 = strncmp();
        if (iVar4 == 0) {
            if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) return DEBUG_PRINT();
            return debug_print();
        }
        cVar5 = (cVar5 - 1) & 0xff;
    } while (cVar5 != 0);
    get_device_info();
    return FUN_00033730();
}

