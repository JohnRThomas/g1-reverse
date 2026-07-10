/* named: pairing_failed */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed pairing_failed @ 0x18444  (parity: 300/300 trials, PROVEN) */

extern void format_bt_addr_str(void);
extern unsigned int FUN_00081526(void);
extern void DEBUG_PRINT(void);
extern void debug_print(void);
extern void FUN_00056a68(void);

void pairing_failed(unsigned int param_1, unsigned int param_2)
{
    unsigned int uVar1 = FUN_00081526();
    (void)uVar1;
    format_bt_addr_str();
    DEBUG_PRINT();
    if (*(volatile int*)0x2000230cUL > 0) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    FUN_00056a68();
}

