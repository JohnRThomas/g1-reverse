#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_channel_assign_info__param_0091        [param_0091; G1-original]
 * Raw function identity: 0x00031fd8.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00031fd8 @ 0x00031fd8
 * public-name: get_assign_channel_info
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   build_and_send_device_status_report      <= FUN_00022b00 @ 0x00022b00
 *   read_sys_settting_from_flash             <= FUN_000232f8 @ 0x000232f8
 *   get_assign_channel_info                  <= FUN_00031fd8 @ 0x00031fd8
 *   k_msleep_ticks32768_b                    <= FUN_0007d14a @ 0x0007d14a
 * address symbols (name @ address):
 *   rodata_a672f                             @ 0x000a672f   [INLINED -- G6 literal batch]
 *   rodata_a723e                             @ 0x000a723e   [INLINED -- G6 literal batch]
 *   rodata_a7266                             @ 0x000a7266   [INLINED -- G6 literal batch]
 *   rodata_a7293                             @ 0x000a7293   [INLINED -- G6 literal batch]
 *   rodata_a72ab                             @ 0x000a72ab   [INLINED -- G6 literal batch]
 *   rodata_a72c6                             @ 0x000a72c6   [INLINED -- G6 literal batch]
 *   rodata_a76da                             @ 0x000a76da   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_test_mode_flag                         @ 0x20019ef3
 */
/* Reconstructed FUN_00031fd8 @ 0x31fd8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
typedef unsigned uint; typedef unsigned char byte;
extern int get_device_info(int,...);
extern int build_and_send_device_status_report(int,...);
extern int read_sys_settting_from_flash(int,...);
extern int k_msleep_ticks32768_b(int,...);

unsigned get_assign_channel_info(int param_1, unsigned param_2, unsigned *param_3, unsigned char *param_4)
{
    volatile int *piVar1,*piVar2; unsigned uVar3; int iVar4; char cVar5; unsigned char *puVar6;
    unsigned char auStack_9c[8]; char local_94; char local_47; char local_46;
    piVar1 = (volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/;
    if(3 < *piVar1){
        if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0){ log_message(((unsigned long)"%s(): join in get_assign_channel_info\n\n") /*=0xa723e*/, ((unsigned long)"get_assign_channel_info") /*=0xa76da*/); }
        else { debug_print(((unsigned long)"%s(): join in get_assign_channel_info\n\n") /*=0xa723e*/, ((unsigned long)"get_assign_channel_info") /*=0xa76da*/); }
    }
    if(param_3 == 0 || param_4 == 0){
        if(0 < *piVar1){
            if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0){ log_message(((unsigned long)"%s(): get_assign_channel_info para is NULL\n\n") /*=0xa7266*/, ((unsigned long)"get_assign_channel_info") /*=0xa76da*/); }
            else { debug_print(((unsigned long)"%s(): get_assign_channel_info para is NULL\n\n") /*=0xa7266*/, ((unsigned long)"get_assign_channel_info") /*=0xa76da*/); }
        }
        uVar3 = 0xffffffff;
    } else if(*(volatile char*)((unsigned long)&g_test_mode_flag) /*=0x20019ef3*/ == 1){
        puVar6 = (unsigned char*)*param_3;
        iVar4 = get_device_info(0);
        *(unsigned char*)(iVar4 + 2) = *(unsigned char*)(param_1 + 4);
        iVar4 = get_device_info(0);
        *(unsigned char*)(iVar4 + 3) = *(unsigned char*)(param_1 + 5);
        iVar4 = get_device_info(0);
        *(unsigned char*)(iVar4 + 4) = *(unsigned char*)(param_1 + 6);
        piVar2 = (volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        if(3 < *piVar1){
            if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0){
                iVar4 = get_device_info(0);
                log_message(((unsigned long)"%s(): esb_channel: %d\n\n") /*=0xa7293*/, ((unsigned long)"get_assign_channel_info") /*=0xa76da*/, (uint)*(byte*)(iVar4 + 2));
            } else {
                iVar4 = get_device_info(0);
                debug_print(((unsigned long)"%s(): esb_channel: %d\n\n") /*=0xa7293*/, ((unsigned long)"get_assign_channel_info") /*=0xa76da*/, *(unsigned char*)(iVar4 + 2));
            }
            if(3 < *piVar1){
                if(*piVar2 == 0){
                    iVar4 = get_device_info(0);
                    log_message(((unsigned long)"%s(): esb master addr:%d\n\n") /*=0xa72ab*/, ((unsigned long)"get_assign_channel_info") /*=0xa76da*/, (uint)*(byte*)(iVar4 + 3));
                } else {
                    iVar4 = get_device_info(0);
                    debug_print(((unsigned long)"%s(): esb master addr:%d\n\n") /*=0xa72ab*/, ((unsigned long)"get_assign_channel_info") /*=0xa76da*/, *(unsigned char*)(iVar4 + 3));
                }
                if(3 < *piVar1){
                    if(*piVar2 == 0){
                        iVar4 = get_device_info(0);
                        log_message(((unsigned long)"%s(): esb slave addr: %d\n\n") /*=0xa72c6*/, ((unsigned long)"get_assign_channel_info") /*=0xa76da*/, (uint)*(byte*)(iVar4 + 4));
                    } else {
                        iVar4 = get_device_info(0);
                        debug_print(((unsigned long)"%s(): esb slave addr: %d\n\n") /*=0xa72c6*/, ((unsigned long)"get_assign_channel_info") /*=0xa76da*/, *(unsigned char*)(iVar4 + 4));
                    }
                }
            }
        }
        uVar3 = get_device_info(0);
        build_and_send_device_status_report(uVar3, 0);
        cVar5 = 0;
        *puVar6 = 0x1d;
        puVar6[2] = 3;
        puVar6[1] = 1;
        puVar6[3] = 1;
        puVar6[4] = 0;
        do {
            iVar4 = read_sys_settting_from_flash((int)auStack_9c);
            if(iVar4 == 0 && *(char*)(param_1 + 4) == local_94 &&
               *(char*)(param_1 + 5) == local_47 && *(char*)(param_1 + 6) == local_46)
                goto control_label_00032102;
            cVar5 = cVar5 + 1;
            k_msleep_ticks32768_b(100);
        } while(cVar5 != 5);
        puVar6[4] = 1;
control_label_00032102:
        uVar3 = 0;
        *param_4 = 5;
    } else {
        log_message(((unsigned long)"warning: not test mode,disable setting\n") /*=0xa672f*/);
        uVar3 = 0xfffffffe;
    }
    return uVar3;
}
