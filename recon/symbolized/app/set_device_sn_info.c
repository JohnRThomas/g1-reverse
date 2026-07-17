#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00032164 @ 0x00032164
 * public-name: set_device_sn_info
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   build_and_send_device_status_report      <= FUN_00022b00 @ 0x00022b00
 *   read_sys_settting_from_flash             <= FUN_000232f8 @ 0x000232f8
 *   printf                                   <= FUN_000777f0 @ 0x000777f0
 *   k_msleep_ticks32768_b                    <= FUN_0007d14a @ 0x0007d14a
 * address symbols (name @ address):
 *   rodata_a672f                             @ 0x000a672f
 *   rodata_a71cd                             @ 0x000a71cd
 *   rodata_a71e0                             @ 0x000a71e0
 *   rodata_a7209                             @ 0x000a7209
 *   rodata_a72e1                             @ 0x000a72e1
 *   rodata_a72fc                             @ 0x000a72fc
 *   rodata_a76f2                             @ 0x000a76f2
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_test_mode_flag                         @ 0x20019ef3
 */
/* Reconstructed set_device_sn_info @ 0x32164  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int DEBUG_PRINT(int,...);
extern int get_device_info(void);
extern int debug_print(int,...);
extern int build_and_send_device_status_report(int,int);
extern int FUN_000232b0(void);
extern int FUN_000232c0(int);
extern int read_sys_settting_from_flash(void*);
extern int printf(int,int);
extern int k_msleep_ticks32768_b(int);
extern int FUN_00086be4(int,void*,int);

uint32_t set_device_sn_info(int param_1, uint32_t param_2, uint32_t *param_3, uint8_t *param_4){
    uint32_t uVar1;
    int iVar2;
    int8_t cVar3;
    uint8_t *puVar4;
    uint8_t auStack_9c[21];
    uint8_t auStack_87[115];
    DEBUG_PRINT(((unsigned long)&rodata_a72e1) /*=0xa72e1*/);
    if (param_3==0 || param_4==0){ DEBUG_PRINT(((unsigned long)&rodata_a72fc) /*=0xa72fc*/); uVar1=0xffffffff; }
    else if (*(volatile uint8_t*)((unsigned long)&g_test_mode_flag) /*=0x20019ef3*/ == 1){
        param_1 = param_1 + 4;
        puVar4 = (uint8_t*)*param_3;
        FUN_000232c0(param_1);
        printf(((unsigned long)&rodata_a71cd) /*=0xa71cd*/, param_1);
        uVar1 = get_device_info();
        build_and_send_device_status_report(uVar1,0);
        if (2 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/){
            if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0){ uVar1=FUN_000232b0(); DEBUG_PRINT(((unsigned long)&rodata_a71e0) /*=0xa71e0*/,((unsigned long)&rodata_a76f2) /*=0xa76f2*/,uVar1); }
            else { uVar1=FUN_000232b0(); debug_print(((unsigned long)&rodata_a71e0) /*=0xa71e0*/,((unsigned long)&rodata_a76f2) /*=0xa76f2*/,uVar1); }
        }
        *puVar4=0x1c; puVar4[1]=1; puVar4[3]=1; cVar3=5; puVar4[2]=3; puVar4[4]=0; *param_4=5;
        do {
            iVar2 = read_sys_settting_from_flash(auStack_9c);
            if (iVar2==0 && (iVar2=FUN_00086be4(param_1, auStack_87, 0xe))==0){ DEBUG_PRINT(((unsigned long)&rodata_a7209) /*=0xa7209*/); goto done; }
            cVar3 = cVar3 - 1;
            k_msleep_ticks32768_b(100);
        } while (cVar3 != 0);
        puVar4[4]=1;
done:   uVar1=0;
    } else { DEBUG_PRINT(((unsigned long)&rodata_a672f) /*=0xa672f*/); uVar1=0xfffffffe; }
    return uVar1;
}
