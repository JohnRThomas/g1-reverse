#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_g1_device_runtime_state__param_0027    [param_0027; G1-original]
 * Raw function identity: 0x00023844.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00023844 @ 0x00023844
 * public-name: brightness_level
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   update_burial_point_to_flash             <= FUN_00023014 @ 0x00023014
 *   file_subsystem_queue_init                <= FUN_000234e8 @ 0x000234e8
 *   crc32_table_init                         <= FUN_000235dc @ 0x000235dc
 *   try_to_save_file                         <= FUN_00023634 @ 0x00023634
 *   get_demo_image_source_from_flash         <= FUN_000365ec @ 0x000365ec
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 *   rproc_virtio_negotiate_features          <= FUN_0007c34a @ 0x0007c34a
 *   set_shutdown_flag                        <= FUN_0007cbfe @ 0x0007cbfe
 * address symbols (name @ address):
 *   rodata_28000                             @ 0x00028000
 *   rodata_9e1de                             @ 0x0009e1de
 *   rodata_9e201                             @ 0x0009e201
 *   rodata_9e21f                             @ 0x0009e21f
 *   rodata_9e230                             @ 0x0009e230
 *   rodata_9e23c                             @ 0x0009e23c
 *   rodata_9e249                             @ 0x0009e249
 *   rodata_9e259                             @ 0x0009e259
 *   rodata_9e8af                             @ 0x0009e8af   [INLINED -- G6 literal batch]
 *   rodata_9e8cf                             @ 0x0009e8cf   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_200079c4                               @ 0x200079c4
 *   g_font_total_size                        @ 0x200079d4
 *   g_font_buf_len                           @ 0x200079d8
 *   g_font_flash_write_offset                @ 0x200079dc
 *   g_font_crc32                             @ 0x200079e0
 */
/* Full reconstruction brightness_level @ 0x23844, CFG-correct extent 464 bytes.
 * CFG_VERIFY_PREFIX_FIRST CFG_VERIFY_PREFIX_K=20 */
#include <stdint.h>
#include "../../../headers/g1_log.h"
extern void file_subsystem_queue_init(void);
extern void crc32_table_init(void);
extern void try_to_save_file(uintptr_t);
extern void z_impl_k_sem_take(uintptr_t,uintptr_t,uint32_t,uint32_t);
extern int get_device_info(void);
extern void update_burial_point_to_flash(void);
extern void get_demo_image_source_from_flash(void);
extern int32_t k_sleep(k_timeout_t);
extern unsigned int change_work_mode_to(unsigned int);
extern void set_shutdown_flag(uintptr_t,uint32_t);
extern unsigned int rproc_virtio_negotiate_features(void*, unsigned int);
extern uint64_t thunk_FUN_00074f68(void);

typedef void (*brightness_callback)(uintptr_t text, uintptr_t value,
                                    uint32_t style);

void brightness_level(uintptr_t context)
{
    file_subsystem_queue_init();
    crc32_table_init();
    uint32_t completion_flag = 0;
    for (;;) {
        z_impl_k_sem_take(context + 0x80,0,0xffffffffu,0xffffffffu);
        uint32_t drained = 0;
        while (*(volatile uint32_t *)((unsigned long)&g_200079c4) /*=0x200079c4*/ != 0) {
            try_to_save_file(context);
            drained = 1;
        }
        uint32_t mode = *(volatile uint32_t *)(context + 0x104c);
        if (mode == 0x15 || drained)
            continue;

        brightness_callback callback =
            *(brightness_callback *)(context + 0x1040);
        uintptr_t text = 0;
        uintptr_t value = 0;
        uint32_t style = 0;
        uint32_t invoke = 0;
        switch (mode) {
        case 1:
            text=((unsigned long)&rodata_9e21f) /*=0x9e21f*/; value=context+0xed5; style=1; invoke=1; break;
        case 2:
            text=((unsigned long)&rodata_9e230) /*=0x9e230*/; value=context+0xf60; style=1; invoke=1; break;
        case 3:
            text=((unsigned long)&rodata_9e23c) /*=0x9e23c*/; value=context+0xfea; style=1; invoke=1; break;
        case 6:
            text=((unsigned long)&rodata_9e1de) /*=0x9e1de*/; value=*(volatile uintptr_t*)(context+0xfec);
            style=0x6a; invoke=1; break;
        case 7:
            text=((unsigned long)&rodata_9e201) /*=0x9e201*/; value=*(volatile uintptr_t*)(context+0xff0);
            style=7; invoke=1; break;
        case 8:
            text=((unsigned long)&rodata_9e249) /*=0x9e249*/; value=*(volatile uintptr_t*)(context+0xff4);
            style=0x16a; invoke=1; break;
        case 0xb:
            text=((unsigned long)&rodata_9e259) /*=0x9e259*/; value=context+0xef4; style=1; invoke=1; break;
        case 0x11:
            k_sleep(0x50000,0);
            change_work_mode_to(7);
            break;
        case 0x16:
            if (*(volatile uint32_t*)((unsigned long)&g_font_total_size) /*=0x200079d4*/ == 0x1c0000u) {
                get_demo_image_source_from_flash();
                uintptr_t owner=get_device_info();
                uint8_t level=*(volatile uint8_t*)owner==1?0x0d:0x0c;
                owner=get_device_info();
                uintptr_t slot=*(volatile uintptr_t*)(owner+0x100c);
                *(volatile uint8_t*)slot=level;
            }
            *(volatile uint32_t*)((unsigned long)&g_font_total_size) /*=0x200079d4*/=0;
            *(volatile uint32_t*)((unsigned long)&g_font_buf_len) /*=0x200079d8*/=0;
            *(volatile uint32_t*)((unsigned long)&g_font_crc32) /*=0x200079e0*/=0;
            *(volatile uint32_t*)((unsigned long)&g_font_flash_write_offset) /*=0x200079dc*/=0;
            continue;
        case 0x17:
            set_shutdown_flag(context,0);
            change_work_mode_to(1);
            continue;
        case 0x19:
        case 0x1a:
            completion_flag=1;
            break;
        case 0x3e:
            get_device_info();
            update_burial_point_to_flash();
            goto wait_for_frame;
        default:
            break;
        }
        if (invoke) {
            callback(text,value,style);
        } else if (mode != 0x19 && mode != 0x1a && mode != 0x3e) {
            if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
                int alternate=*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                if (alternate)
                    debug_print(((unsigned long)"%s(): ignore.\n") /*=0x9e8af*/,((unsigned long)"storage_commit_thread") /*=0x9e8cf*/,0,(uint32_t)alternate);
                else
                    log_message(((unsigned long)"%s(): ignore.\n") /*=0x9e8af*/,((unsigned long)"storage_commit_thread") /*=0x9e8cf*/,0,0);
            }
        }

wait_for_frame:
        do {
            uint64_t before=thunk_FUN_00074f68();
            z_impl_k_sem_take(context+0x80,0,((unsigned long)&rodata_28000) /*=0x28000*/,0);
            uint64_t after=thunk_FUN_00074f68();
            before=(before*1000u)>>15;
            after=(after*1000u)>>15;
            if ((int64_t)(after-before)>=5000)
                break;
        } while (1);
        *(volatile uint32_t*)(context+0x104c)=0;
        rproc_virtio_negotiate_features(context,completion_flag);
    }
}
