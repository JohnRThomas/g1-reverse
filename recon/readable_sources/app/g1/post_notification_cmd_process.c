#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_3          => struct g1_layout_app_shared_ctx_blob__param_0007        [param_0007; G1-original]
 *   param_1          => struct g1_layout_app_ble_ctx_block__param_0038          [param_0038; G1-original]
 * Raw function identity: 0x000338ec.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000338ec @ 0x000338ec
 * public-name: post_notification_cmd_process
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_fw_load_get_wrapper                <= FUN_00019b54 @ 0x00019b54
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   parse_receiver_msg_pack_pkcs7            <= FUN_00019da4 @ 0x00019da4
 *   post_notification_cmd_process            <= FUN_000338ec @ 0x000338ec
 *   parse_ncs_notification                   <= FUN_00034980 @ 0x00034980
 *   malloc                                   <= FUN_00076d6c @ 0x00076d6c
 *   free                                     <= FUN_00076d7c @ 0x00076d7c
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_a7c2d                             @ 0x000a7c2d
 *   rodata_a7c4a                             @ 0x000a7c4a
 *   rodata_a7c9c                             @ 0x000a7c9c
 *   rodata_a7cb6                             @ 0x000a7cb6
 *   rodata_a82c4                             @ 0x000a82c4
 *   rodata_a82e2                             @ 0x000a82e2
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ancs_notify_rx_buf                     @ 0x20007da8
 */
/* Reconstructed FUN_000338ec @ 0x338ec  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int log_message(int,...);
extern int audio_fw_load_get_wrapper(int,...);
extern int debug_print(int,...);
extern int parse_receiver_msg_pack_pkcs7(int,...);
extern int parse_ncs_notification(int,...);
extern int malloc(int,...);
extern int free(int,...);
extern int memcpy(int,...);
extern int memset_bytes(int,...);

void post_notification_cmd_process(int param_1, unsigned char *param_2, int param_3)
{
    int *piVar1; unsigned uVar2; int iVar3; unsigned char *puVar4; unsigned uVar5;
    unsigned local_b4; unsigned char auStack_b0[16]; unsigned char auStack_a0[132];

    if(param_1==0 || param_2==0 || param_3==0){
        if(1 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/){
            if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ != 0){ debug_print(((unsigned long)&rodata_a7c2d) /*=0xa7c2d*/, ((unsigned long)&rodata_a82e2) /*=0xa82e2*/); return; }
            log_message(((unsigned long)&rodata_a7c2d) /*=0xa7c2d*/, ((unsigned long)&rodata_a82e2) /*=0xa82e2*/); return;
        }
    } else {
        puVar4 = *(unsigned char**)(param_1+0x10);
        local_b4 = 0;
        memset_bytes((int)auStack_b0, 0, 0x10);
        *(unsigned char*)&local_b4 = *param_2;
        *puVar4 = *param_2;
        puVar4[1] = param_2[1];
        *(unsigned*)(param_1+0x14) = *(unsigned short*)(puVar4+2) + 4;
        piVar1 = (int*)((unsigned long)&g_ancs_notify_rx_buf) /*=0x20007da8*/;
        uVar5 = (unsigned)(unsigned char)puVar4[1];
        if(uVar5==2 || uVar5==4){
            *(unsigned short*)(puVar4+2) = 0x1b4;
            memcpy((int)(puVar4+4), param_3);
            if(2 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/){
                if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0){
                    log_message(((unsigned long)&rodata_a7c4a) /*=0xa7c4a*/, ((unsigned long)&rodata_a82e2) /*=0xa82e2*/, uVar5);
                } else { debug_print(((unsigned long)&rodata_a7c4a) /*=0xa7c4a*/, ((unsigned long)&rodata_a82e2) /*=0xa82e2*/, uVar5); }
            }
            audio_fw_load_get_wrapper(param_1, (int)auStack_a0, 8);
        } else {
            if(*(volatile int*)((unsigned long)&g_ancs_notify_rx_buf) /*=0x20007da8*/ == 0){
                iVar3 = malloc(0x800);
                *piVar1 = iVar3;
                if(iVar3==0){
                    if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0){
                        log_message(((unsigned long)&rodata_a7c9c) /*=0xa7c9c*/, ((unsigned long)&rodata_a82c4) /*=0xa82c4*/, 0x19f);
                    } else { debug_print(((unsigned long)&rodata_a7c9c) /*=0xa7c9c*/, ((unsigned long)&rodata_a82c4) /*=0xa82c4*/, 0x19f); }
                } else {
                    memset_bytes(iVar3, 0, 0x800);
                }
            }
            if(*piVar1 != 0){
                iVar3 = parse_receiver_msg_pack_pkcs7(*piVar1, param_3, puVar4[2]);
                uVar2 = local_b4;
                *((unsigned char*)&local_b4 + 1) = (unsigned char)iVar3;
                *((unsigned char*)&local_b4 + 3) = (unsigned char)(uVar2 >> 24);
                *((unsigned char*)&local_b4 + 2) = *(unsigned char*)(param_3+1);
                if(iVar3 == 0xc9){
                    parse_ncs_notification(*piVar1, (int)(puVar4+4));
                    if(2 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/){
                        if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0){
                            log_message(((unsigned long)&rodata_a7cb6) /*=0xa7cb6*/, ((unsigned long)&rodata_a82e2) /*=0xa82e2*/);
                        } else { debug_print(((unsigned long)&rodata_a7cb6) /*=0xa7cb6*/, ((unsigned long)&rodata_a82e2) /*=0xa82e2*/); }
                    }
                    *(unsigned short*)(puVar4+2) = 0x1b4;
                    audio_fw_load_get_wrapper(param_1, (int)auStack_a0, 8);
                    *((unsigned char*)&local_b4 + 1) = 0xc9;
                    free(*piVar1);
                    *piVar1 = 0;
                }
            }
            (*(void(**)(int,...))(param_1+0xc))((int)&local_b4, 0x14);
        }
    }
    return;
}
