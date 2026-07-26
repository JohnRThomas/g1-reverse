#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00032164 @ 0x00032164
 * public-name: set_device_sn_info
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   build_and_send_device_status_report      <= FUN_00022b00 @ 0x00022b00
 *   get_device_serial_buf                    <= FUN_000232b0 @ 0x000232b0
 *   format_device_serial_to_buf              <= FUN_000232c0 @ 0x000232c0
 *   read_sys_settting_from_flash             <= FUN_000232f8 @ 0x000232f8
 *   printf                                   <= FUN_000777f0 @ 0x000777f0
 *   k_msleep_ticks32768_b                    <= FUN_0007d14a @ 0x0007d14a
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 * address symbols (name @ address):
 *   rodata_a672f                             @ 0x000a672f   [INLINED -- G6 literal batch]
 *   rodata_a71cd                             @ 0x000a71cd
 *   rodata_a71e0                             @ 0x000a71e0   [INLINED -- G6 literal batch]
 *   rodata_a7209                             @ 0x000a7209   [INLINED -- G6 literal batch]
 *   rodata_a72e1                             @ 0x000a72e1   [INLINED -- G6 literal batch]
 *   rodata_a72fc                             @ 0x000a72fc   [INLINED -- G6 literal batch]
 *   rodata_a76f2                             @ 0x000a76f2   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_test_mode_flag                         @ 0x20019ef3
 */
/* Reconstructed set_device_sn_info @ 0x32164  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#include "../../headers/g1_log.h"
extern int get_device_info(void);
extern int build_and_send_device_status_report(int,int);
extern int get_device_serial_buf(void);
extern int format_device_serial_to_buf(int);
extern int read_sys_settting_from_flash(void*);
extern int printf(int,int);
extern int k_msleep_ticks32768_b(int);
extern int memcmp(int,void*,int);

uint32_t set_device_sn_info(int param_1, uint32_t param_2, uint32_t *param_3, uint8_t *param_4){
    uint32_t uVar1;
    int iVar2;
    int8_t cVar3;
    uint8_t *puVar4;
    uint8_t auStack_9c[21];
    uint8_t auStack_87[115];
    log_message(((unsigned long)"join in get_query_sn_info\n") /*=0xa72e1*/);
    if (param_3==0 || param_4==0){ log_message(((unsigned long)"get_query_sn_info para is NULL\n") /*=0xa72fc*/); uVar1=0xffffffff; }
    else if (*(volatile uint8_t*)((unsigned long)&g_test_mode_flag) /*=0x20019ef3*/ == 1){
        param_1 = param_1 + 4;
        puVar4 = (uint8_t*)*param_3;
        format_device_serial_to_buf(param_1);
        printf(((unsigned long)&rodata_a71cd) /*=0xa71cd*/, param_1);
        uVar1 = get_device_info();
        build_and_send_device_status_report(uVar1,0);
        if (2 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/){
            if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0){ uVar1=get_device_serial_buf(); log_message(((unsigned long)"%s(): BLE_REQ_PUT_DEVICE_SN new sn:%16s\n") /*=0xa71e0*/,((unsigned long)"set_device_sn_info") /*=0xa76f2*/,uVar1); }
            else { uVar1=get_device_serial_buf(); debug_print(((unsigned long)"%s(): BLE_REQ_PUT_DEVICE_SN new sn:%16s\n") /*=0xa71e0*/,((unsigned long)"set_device_sn_info") /*=0xa76f2*/,uVar1); }
        }
        *puVar4=0x1c; puVar4[1]=1; puVar4[3]=1; cVar3=5; puVar4[2]=3; puVar4[4]=0; *param_4=5;
        do {
            iVar2 = read_sys_settting_from_flash(auStack_9c);
            if (iVar2==0 && (iVar2=memcmp(param_1, auStack_87, 0xe))==0){ log_message(((unsigned long)"SN codes updated and written to flash successfully.\n") /*=0xa7209*/); goto done; }
            cVar3 = cVar3 - 1;
            k_msleep_ticks32768_b(100);
        } while (cVar3 != 0);
        puVar4[4]=1;
done:   uVar1=0;
    } else { log_message(((unsigned long)"warning: not test mode,disable setting\n") /*=0xa672f*/); uVar1=0xfffffffe; }
    return uVar1;
}
