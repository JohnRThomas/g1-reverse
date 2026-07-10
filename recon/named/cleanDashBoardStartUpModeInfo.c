/* named: cleanDashBoardStartUpModeInfo */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20003994  g_flash_store_cmd_msgq       
//   0x20007554  g_log_use_alt_sink           
//   0x200079e4  g_app_language_msgq          
*/
/* Reconstructed cleanDashBoardStartUpModeInfo @ 0x23c88  (parity: 300/300 trials, PROVEN) */
extern void DEBUG_PRINT(unsigned int a0, unsigned int a1);
extern void debug_print(void);
extern int k_msgq_put(unsigned int a0, void *a1, unsigned int a2, unsigned int a3);
extern void FUN_00072880(unsigned int a0);

unsigned int cleanDashBoardStartUpModeInfo(unsigned int param_1, unsigned int param_2)
{
    unsigned int buf[2];
    int iVar1;
    unsigned int uVar2;
    (void)param_1; (void)param_2;
    buf[0] = 4;
    buf[1] = 0;
    iVar1 = k_msgq_put(0x20003994UL, buf, 0UL, 0UL);
    if (iVar1 == 0) {
        if (2 < *(volatile int*)0x2000230cUL) {
            if (*(volatile int*)0x20007554UL == 0)
                DEBUG_PRINT(0x9e968UL, 0x9ed4aUL);
            else
                debug_print();
        }
        FUN_00072880(0x200079e4UL);
        uVar2 = 0;
    } else {
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile int*)0x20007554UL == 0)
                DEBUG_PRINT(0x9e903UL, 0x9ed4aUL);
            else
                debug_print();
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}

