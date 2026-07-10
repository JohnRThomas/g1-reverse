#include "g1_app_symbols.h"
/* named: fuel_gauge_sample_init_timestamp */
/* globals referenced:
//   0x20004790  g_fuel_gauge_init_timestamp  
*/
/* Reconstructed fuel_gauge_sample_init_timestamp @ 0x2ea28  (parity: 300/300 trials, PROVEN) */

extern int FUN_0000e2b4(void*, int);
extern int fuel_gauge_read_voltage_current_temp(int, void*, void*, void*);
extern unsigned long long k_uptime_get_3(void);
extern void sensor_channel_get_trampoline(int, int, void*);

int fuel_gauge_sample_init_timestamp(int param_1)
{
    int local_20 = 0, uStack_1c = 0, local_18 = 0;
    unsigned char auStack_28[8];
    int iVar1;
    iVar1 = fuel_gauge_read_voltage_current_temp(param_1, &local_20, &uStack_1c, &local_18);
    if (iVar1 >= 0) {
        sensor_channel_get_trampoline(param_1, 0x39, auStack_28);
        iVar1 = FUN_0000e2b4(&local_20, 0);
        if (iVar1 >= 0) {
            unsigned long long uVar2 = k_uptime_get_3();
            *(volatile unsigned long long*)((uintptr_t)&g_fuel_gauge_init_timestamp) /*=0x20004790*/ = uVar2;
            iVar1 = 0;
        }
    }
    return iVar1;
}

