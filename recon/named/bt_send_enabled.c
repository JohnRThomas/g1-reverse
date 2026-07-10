/* named: bt_send_enabled */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20006a30  g_ble_conn_ctx_ptr           
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed bt_send_enabled @ 0x17e3c  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int, unsigned int, int);
extern void debug_print(void);

void bt_send_enabled(int param_1)
{
    if (*(volatile int*)0x2000230cUL > 2) {
        if (*(volatile int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x9a143UL, 0x9a2cdUL, param_1);
        } else {
            debug_print();
        }
    }
    int *p = *(int* volatile*)0x20006a30UL;
    *(volatile unsigned char*)((char*)p + 0x366) = (param_1 == 0);
}

