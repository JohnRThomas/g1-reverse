#include "g1_app_symbols.h"
/* named: FUN_00055fb4 */
/* globals referenced:
//   0x2000ad1c  g_ble_conn_cb_list_head      
*/
/* Reconstructed FUN_00055fb4 @ 0x55fb4  (parity: 300/300 trials, PROVEN) */

typedef void (*fn_t)(int, unsigned char);

void FUN_00055fb4(int param_1)
{
    unsigned int *puVar2;
    unsigned char b = *(unsigned char *)(param_1 + 0xc);

    puVar2 = *(unsigned int **)((uintptr_t)&g_ble_conn_cb_list_head) /*=0x2000ad1c*/;
    while (puVar2 != (unsigned int *)0) {
        fn_t f = (fn_t)(*puVar2);
        if (f != (fn_t)0) {
            f(param_1, b);
        }
        puVar2 = (unsigned int *)puVar2[8];
    }
}

