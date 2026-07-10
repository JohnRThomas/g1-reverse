/* named: sett_init */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed sett_init @ 0x22518  (parity: 300/300 trials, PROVEN) */

extern int settings_subsys_init(void);
extern int settings_register(unsigned int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(void);

void sett_init(int *param_1)
{
    int iVar2;
    volatile int *piVar1;
    unsigned int format_string;
    int iVar3;

    iVar2 = settings_subsys_init();
    piVar1 = (volatile int*)0x2000230cUL;
    if (iVar2 == 0) {
        iVar2 = settings_register(0x20002368UL);
        if (iVar2 == 0) {
            if (1 < *piVar1) {
                if (*(volatile unsigned int*)0x20007554UL == 0) {
                    DEBUG_PRINT(0x9e2cb, 0x9e549);
                } else {
                    debug_print();
                }
            }
            iVar2 = 1;
            goto LAB;
        }
        if (*piVar1 < 2) goto LAB;
        iVar3 = *(volatile int*)0x20007554UL;
        format_string = 0x9e2a0;
    } else {
        if (*piVar1 < 2) goto LAB;
        iVar3 = *(volatile int*)0x20007554UL;
        format_string = 0x9e266;
    }
    if (iVar3 == 0) {
        DEBUG_PRINT(format_string, 0x9e549, iVar2);
    } else {
        debug_print();
    }
LAB:
    param_1[0] = iVar2;
    param_1[1] = 0x22169;
    param_1[2] = 0x7c26b;
    param_1[3] = 0x22121;
}

