/* named: display_MasterSendClose */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed display_MasterSendClose @ 0x499b8  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void);
extern int k_msgq_put(void);
extern void DEBUG_PRINT(void);
extern void debug_print(void);

unsigned int display_MasterSendClose(void)
{
    memset_bytes();
    int iVar1 = k_msgq_put();
    unsigned int uVar2;
    if (iVar1 == 0) {
        uVar2 = 0;
        if (*(volatile int*)0x2000230cUL > 2) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT();
            } else {
                debug_print();
            }
        }
    } else {
        DEBUG_PRINT();
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}

