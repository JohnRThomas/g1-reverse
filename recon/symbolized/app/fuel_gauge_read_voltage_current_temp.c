#include "g1_app_symbols.h"
/* named: fuel_gauge_read_voltage_current_temp */
/* Reconstructed fuel_gauge_read_voltage_current_temp @ 0x2e988  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32;
typedef int (*fp)(int,int);
extern void sensor_channel_get_trampoline(int,int,void*);
static inline float mkf(int b){ union{int i;float f;}u; u.i=b; return u.f; }
int fuel_gauge_read_voltage_current_temp(int param_1, float* param_2, float* param_3, float* param_4){
    int local[2];
    int iVar2 = (*(fp*)(*(int*)(param_1+8)+0xc))(param_1, 0x3a);
    if(iVar2 >= 0){
        float f = mkf(0x49742400);
        sensor_channel_get_trampoline(param_1, 0x28, local);
        *param_2 = (float)(int)local[1] / f + (float)(int)local[0];
        sensor_channel_get_trampoline(param_1, 0x2c, local);
        *param_4 = (float)(int)local[1] / f + (float)(int)local[0];
        sensor_channel_get_trampoline(param_1, 0x29, local);
        iVar2 = 0;
        *param_3 = (float)(int)local[1] / f + (float)(int)local[0];
    }
    return iVar2;
}

