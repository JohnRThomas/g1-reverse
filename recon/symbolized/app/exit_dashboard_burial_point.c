#include "g1_app_symbols.h"
/* named: exit_dashboard_burial_point */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed exit_dashboard_burial_point @ 0x4aab0  (parity: 300/300 trials, PROVEN) */

extern unsigned int get_device_info(void);
extern unsigned int get_current_burial_point_type(void);
extern long long get_dashboard_sum_time(void);
extern unsigned int accumulate_burial_point_duration(void);
extern unsigned int DEBUG_PRINT(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned int debug_print(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

unsigned int exit_dashboard_burial_point(void)
{
    unsigned int r0v;
    unsigned int base;
    unsigned int uVar2;
    unsigned long long uVar4;
    unsigned int uVar3;

    base = get_device_info() + 0x1000;
    r0v = base;
    if (*(volatile unsigned char*)(base + 0x92) != 0) {
        uVar2 = get_current_burial_point_type();
        r0v = uVar2;
        if (uVar2 < 7) {
            base = get_device_info() + 0x1000;
            *(volatile unsigned char*)(base + 0x92) = 0;
            uVar4 = (unsigned long long)get_dashboard_sum_time();
            r0v = (unsigned int)uVar4;
            uVar3 = (unsigned int)(uVar4 >> 32);
            r0v = accumulate_burial_point_duration();
            if (1 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
                if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    base = get_device_info() + 0x1000;
                    r0v = DEBUG_PRINT("%s(): [exit_dashboard_burial_point] sum_time is %d ms,dashboard_sum_time is %d s\n" /*=0xf03c4*/, "exit_dashboard_burial_point" /*=0xf0459*/, (unsigned int)uVar4, uVar3, *(volatile unsigned int*)(base + 0xd2));
                } else {
                    base = get_device_info() + 0x1000;
                    r0v = debug_print("%s(): [exit_dashboard_burial_point] sum_time is %d ms,dashboard_sum_time is %d s\n" /*=0xf03c4*/, "exit_dashboard_burial_point" /*=0xf0459*/, (unsigned int)uVar4, uVar3, *(volatile unsigned int*)(base + 0xd2));
                }
            }
        }
    }
    return r0v;
}

