#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0003271c @ 0x0003271c
 * public-name: FUN_0003271c
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_uptime_get_4                           <= FUN_0007d12e @ 0x0007d12e
 * address symbols (name @ address):
 *   g_periodic_check_ok_flag                 @ 0x20003031
 *   g_periodic_check_last_uptime_ms          @ 0x20007bf0
 *   g_periodic_check_fail_cnt                @ 0x20019ef0
 */
/* Reconstructed FUN_0003271c @ 0x3271c  (parity: 300/300 trials, PROVEN) */
extern int FUN_0002ead8(void);
extern void FUN_0002eaa8(void);
extern void FUN_00074844(int,int);
extern int k_uptime_get_4(void);
void FUN_0003271c(void){
    unsigned uVar5 = 0;
    do {
        int iVar4 = FUN_0002ead8();
        if (iVar4 == 0){ uVar5 = uVar5 & 0xff; break; }
        FUN_0002eaa8();
        uVar5 = uVar5 + 1;
        FUN_00074844(0x290, 0);
    } while (uVar5 != 10);
    int iVar4 = k_uptime_get_4();
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
