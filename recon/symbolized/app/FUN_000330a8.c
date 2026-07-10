#include "g1_app_symbols.h"
/* named: FUN_000330a8 */
/* globals referenced:
//   0x20002424  g_fuel_gauge_dev             
*/
/* Reconstructed FUN_000330a8 @ 0x330a8  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_000330a8(unsigned int param_1)
{
    if (param_1 == 0) {
        return 0xffffffff;
    }
    if (*(volatile unsigned int*)((uintptr_t)&g_fuel_gauge_dev) /*=0x20002424*/ != param_1) {
        *(volatile unsigned int*)((uintptr_t)&g_fuel_gauge_dev) /*=0x20002424*/ = param_1;
    }
    *(volatile unsigned char*)((uintptr_t)&g_pt_comm_state) /*=0x2000242c*/ = 0;
    return 0;
}

