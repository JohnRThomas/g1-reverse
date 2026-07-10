/* named: cjson_delete */
/* globals referenced:
//   0x20002bac  g_cjson_hooks                
*/
/* Reconstructed cjson_delete @ 0x64b1c  (parity: 300/300 trials, PROVEN) */

typedef void (*fp0_t)(void);
typedef void (*fp1_t)(volatile int*);

void cjson_delete(volatile int *param_1)
{
    volatile int *base = (volatile int*)0x20002bacUL;
    while (param_1 != 0) {
        int iVar2 = param_1[0];
        int cond1 = (param_1[3] << 0x17) >= 0;
        if (cond1) {
            if (param_1[2] != 0) {
                cjson_delete((volatile int*)param_1[2]);
                cond1 = (param_1[3] << 0x17) >= 0;
            }
            if (cond1) {
                if (param_1[4] != 0) {
                    fp0_t fp = (fp0_t)(*(volatile int*)((char*)base + 4));
                    fp();
                }
            }
        }
        if ((param_1[3] << 0x16) >= 0 && param_1[8] != 0) {
            fp0_t fp2 = (fp0_t)(*(volatile int*)((char*)base + 4));
            fp2();
        }
        {
            fp1_t fp3 = (fp1_t)(*(volatile int*)((char*)base + 4));
            fp3(param_1);
        }
        param_1 = (volatile int*)iVar2;
    }
}

