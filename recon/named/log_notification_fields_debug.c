/* named: log_notification_fields_debug */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed log_notification_fields_debug @ 0x4a3d0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(int, ...);
extern void debug_print(void);

void log_notification_fields_debug(int param_1, int param_2, int param_3, int param_4)
{
    volatile int *piVar1 = (volatile int*)0x20007554UL;
    if (*piVar1 == 0) {
        DEBUG_PRINT(0x000f0229, param_2 + 0x10);
    } else {
        debug_print();
    }
    if (*piVar1 == 0) {
        DEBUG_PRINT(0x000f024d, param_2 + 0x90);
    } else {
        debug_print();
    }
    if (*piVar1 != 0) {
        debug_print();
        return;
    }
    DEBUG_PRINT(0x000f028c, *(volatile int*)(param_2+8), param_3, param_4);
}

