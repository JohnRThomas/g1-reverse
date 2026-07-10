/* named: SendDashBoardStartupModeInfoToSlave */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x2000392c  g_dashboard_response_msgq    
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed SendDashBoardStartupModeInfoToSlave @ 0x48a3c  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern int k_msgq_put(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int, unsigned int, unsigned int);

unsigned int SendDashBoardStartupModeInfoToSlave(int param_1)
{
    int iVar1;
    unsigned int uVar2, uVar3;
    unsigned char buf[24];

    memset_bytes(buf + 1, 0, 0x17);
    buf[0] = 6;
    buf[4] = (unsigned char)param_1;
    *(unsigned short*)(buf + 2) = 1;
    iVar1 = k_msgq_put(*(volatile unsigned int*)0x2000392cUL, buf, 0, 0);
    if (iVar1 == 0) {
        uVar3 = 0;
        if (2 < *(volatile int*)0x2000230cUL) {
            uVar2 = 0xef5f3;
            if (param_1 == 1) {
                uVar2 = 0xef5df;
            }
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0xef603, 0xef6b0, uVar2);
            } else {
                debug_print(0xef603, 0xef6b0, uVar2);
            }
        }
    } else {
        DEBUG_PRINT(0xef058, 0xef6b0);
        uVar3 = 0xffffffff;
    }
    return uVar3;
}

