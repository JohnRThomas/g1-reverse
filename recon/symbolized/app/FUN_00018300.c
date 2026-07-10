#include "g1_app_symbols.h"
/* named: FUN_00018300 */
/* globals referenced:
//   0x20006ab8  g_ancs_active_conn           
*/
/* Reconstructed FUN_00018300 @ 0x18300  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(int);
extern void FUN_00072880(int);
extern void change_work_mode_to(int);
void FUN_00018300(int param_1, unsigned int param_2)
{
    DEBUG_PRINT("Updated MTU: TX: %d RX: %d bytes\n" /*=0x9a436*/);
    if (99 < param_2) {
        FUN_00072880(*(volatile int*)((uintptr_t)&g_ancs_active_conn) /*=0x20006ab8*/ + 0x230);
        if (param_2 == 0x1f2) {
            change_work_mode_to(1);
            return;
        }
    }
}

