/* named: clean_fb_data */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed clean_fb_data @ 0x471cc  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(void);
extern void memset_bytes(int, void*, int);

int clean_fb_data(int param_1, void *param_2, int param_3, int param_4, int param_5, int param_6)
{
    int iVar1;
    int *piVar2;
    if (0x27f < param_5) param_5 = 0x280;
    if (199 < param_6) param_6 = 200;
    if ((param_5 < param_3) || (param_6 < param_4)) {
        if (*(volatile int*)0x2000230cUL > 0) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0xd7347U, 0xd7374U, param_3, 0, param_4);
            } else {
                debug_print();
            }
        }
        iVar1 = -1;
    } else {
        param_3 = param_3/2;
        piVar2 = (int*)(param_1 + (param_4 + 0x3fffffff)*4);
        while ((int*)(param_1 + param_6*4) != piVar2) {
            piVar2 = piVar2+1;
            memset_bytes(*piVar2+param_3, param_2, (1-param_3)+param_5/2);
        }
        iVar1 = (param_5/2 - param_3)+1;
    }
    return iVar1;
}

