#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0003271c @ 0x0003271c
 * public-name: periodic_check_run
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   display_dev_reg_config                   <= FUN_0002eaa8 @ 0x0002eaa8
 *   dev_read_status_bit_reg34                <= FUN_0002ead8 @ 0x0002ead8
 *   periodic_check_run                       <= FUN_0003271c @ 0x0003271c
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 *   k_uptime_get_4                           <= FUN_0007d12e @ 0x0007d12e
 * address symbols (name @ address):
 *   g_periodic_check_ok_flag                 @ 0x20003031
 *   g_periodic_check_last_uptime_ms          @ 0x20007bf0
 *   g_periodic_check_fail_cnt                @ 0x20019ef0
 */
/* Reconstructed FUN_0003271c @ 0x3271c  (parity: 300/300 trials, PROVEN) */
extern int dev_read_status_bit_reg34(void);
extern void display_dev_reg_config(void);
extern int32_t k_sleep(k_timeout_t);
#ifdef G1_APP_SDK_INLINE_COHESION
#include <stdint.h>
extern int64_t z_impl_k_uptime_ticks(void);
/* Exact configured kernel.h/time_units.h owner: floor(ticks * 1000 / 32768). */
static __attribute__((always_inline)) inline int g1_sdk_uptime_get_4(void)
{
    return (int)(((uint64_t)z_impl_k_uptime_ticks() * 1000u) >> 15);
}
#else
extern int k_uptime_get_4(void); /* k_uptime_get_4 @ 0x0007d12e */
#define g1_sdk_uptime_get_4() k_uptime_get_4()
#endif
void periodic_check_run(void){
    unsigned uVar5 = 0;
    do {
        int iVar4 = dev_read_status_bit_reg34();
        if (iVar4 == 0){ uVar5 = uVar5 & 0xff; break; }
        display_dev_reg_config();
        uVar5 = uVar5 + 1;
        k_sleep(0x290, 0);
    } while (uVar5 != 10);
    int iVar4 = g1_sdk_uptime_get_4();
    if (999 < (unsigned)(iVar4 - *(volatile int*)((unsigned long)&g_periodic_check_last_uptime_ms) /*=0x20007bf0*/)){
        *(volatile int*)((unsigned long)&g_periodic_check_last_uptime_ms) /*=0x20007bf0*/ = iVar4;
        if (uVar5 == 10){
            unsigned char bVar1 = *(volatile unsigned char*)((unsigned long)&g_periodic_check_fail_cnt) /*=0x20019ef0*/;
            *(volatile unsigned char*)((unsigned long)&g_periodic_check_fail_cnt) /*=0x20019ef0*/ = bVar1 + 1;
            if (3 < (unsigned char)(bVar1 + 1)){
                *(volatile unsigned char*)((unsigned long)&g_periodic_check_ok_flag) /*=0x20003031*/ = 0;
                *(volatile unsigned char*)((unsigned long)&g_periodic_check_fail_cnt) /*=0x20019ef0*/ = 3;
                return;
            }
        } else {
            *(volatile unsigned char*)((unsigned long)&g_periodic_check_fail_cnt) /*=0x20019ef0*/ = 0;
        }
        *(volatile unsigned char*)((unsigned long)&g_periodic_check_ok_flag) /*=0x20003031*/ = 1;
    }
}
