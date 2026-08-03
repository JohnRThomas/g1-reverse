#include "g1_app_symbols.h"
#include <stddef.h>
/* readable reconstruction; identity: FUN_00031ee8 @ 0x00031ee8
 * public-name: set_glasses_sn_info
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   build_and_send_device_status_report      <= FUN_00022b00 @ 0x00022b00
 *   get_product_code_buf                     <= FUN_000232b8 @ 0x000232b8
 *   store_product_code_info                  <= FUN_000232dc @ 0x000232dc
 *   read_sys_settting_from_flash             <= FUN_000232f8 @ 0x000232f8
 *   printf                                   <= FUN_000777f0 @ 0x000777f0
 *   k_msleep_ticks32768_b                    <= FUN_0007d14a @ 0x0007d14a
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 * address symbols (name @ address):
 *   rodata_a672f                             @ 0x000a672f   [INLINED -- G6 literal batch]
 *   rodata_a718e                             @ 0x000a718e   [INLINED -- G6 literal batch]
 *   rodata_a71ab                             @ 0x000a71ab   [INLINED -- G6 literal batch]
 *   rodata_a71cd                             @ 0x000a71cd   [INLINED -- refactor stage 01]
 *   rodata_a71e0                             @ 0x000a71e0   [INLINED -- G6 literal batch]
 *   rodata_a7209                             @ 0x000a7209   [INLINED -- G6 literal batch]
 *   rodata_a769d                             @ 0x000a769d   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_test_mode_flag                         @ 0x20019ef3
 */
/* Reconstructed set_glasses_sn_info @ 0x31ee8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#include "../../../headers/g1_log.h"
#include "g1_core.h"
extern int get_device_info(void);
extern int build_and_send_device_status_report(int,int);
extern unsigned int get_product_code_buf(void);
extern int store_product_code_info(int);
extern int printf(const char *, ...);
extern int memcmp(const void *, const void *, size_t);

uint32_t set_glasses_sn_info(int param_1, uint32_t param_2, uint32_t *param_3, uint8_t *param_4){
    uint32_t uVar1;
    int iVar2;
    int8_t cVar3;
    uint8_t *puVar4;
    uint8_t auStack_9c[53];
    uint8_t auStack_67[83];
    log_message(((unsigned long)"join in set_glasses_sn_info\n") /*=0xa718e*/);
    if (param_3==0 || param_4==0){ log_message(((unsigned long)"set_glasses_sn_info para is NULL\n") /*=0xa71ab*/); uVar1=0xffffffff; }
    else if (*(volatile uint8_t *)((unsigned long)&g_test_mode_flag) /*=0x20019ef3*/ == 1){
        param_1 = param_1 + 4;
        puVar4 = (uint8_t*)*param_3;
        store_product_code_info(param_1);
        printf(((unsigned long)"The string is: %s\n") /*=0xa71cd*/, param_1);
        uVar1 = get_device_info();
        build_and_send_device_status_report(uVar1,0);
        if (2 < *(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/){
            if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0){ uVar1=get_product_code_buf(); log_message(((unsigned long)"%s(): BLE_REQ_PUT_DEVICE_SN new sn:%16s\n") /*=0xa71e0*/,((unsigned long)"set_glasses_sn_info") /*=0xa769d*/,uVar1); }
            else { uVar1=get_product_code_buf(); debug_print(((unsigned long)"%s(): BLE_REQ_PUT_DEVICE_SN new sn:%16s\n") /*=0xa71e0*/,((unsigned long)"set_glasses_sn_info") /*=0xa769d*/,uVar1); }
        }
        *puVar4=0x29; puVar4[1]=1; puVar4[3]=1; cVar3=5; puVar4[2]=3; puVar4[4]=0; *param_4=5;
        do {
            iVar2 = read_sys_settting_from_flash(auStack_9c);
            if (iVar2==0 && (iVar2=memcmp(param_1, auStack_67, 0xb))==0){ log_message(((unsigned long)"SN codes updated and written to flash successfully.\n") /*=0xa7209*/); goto done; }
            cVar3 = cVar3 - 1;
            k_msleep_ticks32768_b(100);
        } while (cVar3 != 0);
        puVar4[4]=1;
done:   uVar1=0;
    } else { log_message(((unsigned long)"warning: not test mode,disable setting\n") /*=0xa672f*/); uVar1=0xfffffffe; }
    return uVar1;
}
