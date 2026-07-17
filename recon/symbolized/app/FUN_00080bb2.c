#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00080bb2 @ 0x00080bb2
 * public-name: FUN_00080bb2
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_00080bb2 @ 0x80bb2  (parity: 300/300 trials, PROVEN) */

extern void FUN_00052744(void *a);

unsigned int FUN_00080bb2(int param_1, int param_2)
{
    unsigned int uVar1;
    if (*(volatile int*)(param_1+0x40) == 0) {
        uVar1 = 0xffffffea;
    } else {
        uVar1 = (unsigned int)*(volatile unsigned short*)(param_1+0x44);
        if ((uVar1 == 0) || (param_2 != 0)) {
            FUN_00052744((void*)param_1);
            *(volatile unsigned short*)(param_1+0x44) = 0;
            *(volatile unsigned int*)(param_1+0x40) = 0;
        } else {
            uVar1 = 0xffffffc3;
        }
    }
    return uVar1;
}
