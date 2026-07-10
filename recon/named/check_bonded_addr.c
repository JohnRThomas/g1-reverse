/* named: check_bonded_addr */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20006ab8  g_ancs_active_conn           
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed check_bonded_addr @ 0x183e4  (parity: 300/300 trials, PROVEN) */

extern void format_bt_addr_str(void);
extern void DEBUG_PRINT(void);
extern void debug_print(void);

void check_bonded_addr(unsigned int param_1)
{
    format_bt_addr_str();
    unsigned int *cnt = (unsigned int*)0x20007514UL;
    *cnt = *cnt + 1;
    unsigned int ptr = *(volatile unsigned int*)0x20006ab8UL;
    *(volatile unsigned char*)(ptr + 0x367) = 0;
    if (*(volatile int*)0x2000230cUL > 0) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
}

