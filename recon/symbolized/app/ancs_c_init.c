#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0001905c @ 0x0001905c
 * public-name: ancs_c_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ancs_c_init                              <= FUN_0001905c @ 0x0001905c
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   ancs_service_ctx_clear                   <= FUN_0007f69e @ 0x0007f69e
 *   bt_ancs_register_attr                    <= FUN_0007f772 @ 0x0007f772
 *   bt_ancs_register_app_attr                <= FUN_0007f79e @ 0x0007f79e
 * address symbols (name @ address):
 *   rodata_9ab0c                             @ 0x0009ab0c   [INLINED -- G6 literal batch]
 *   rodata_9b15e                             @ 0x0009b15e   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_ancs_client                            @ 0x20006ae8
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_0001905c @ 0x1905c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../headers/g1_log.h"
extern int ancs_service_ctx_clear(int,...);
/* P4 iteration 20 -- the shipped firmware VENDORS ancs_client.c: its
 * bt_ancs_register_attr accepts len <= 256 and writes
 * ancs_notif_attr_list at +0x868/+0x870/+0x874, while upstream NCS 2.5.1
 * accepts len <= 32 and writes +0x108/+0x110/+0x114 (proven by disassembly of
 * 0x0007f772 / 0x0007f79e against the linked stock bodies; the recovered
 * ancs_service_ctx_clear memsets 0xa2c bytes at g_ancs_client, so the shipped
 * struct really is that large).  adoption_manifest.json excluded both
 * reconstructions on a 1.0 instruction-SHAPE match, which cannot see a
 * changed immediate or a changed struct offset.  MEASURED: with bt_enable()
 * finally succeeding, the fifth registration (id = 3, len = 0x100) failed the
 * stock `cmp r4,#31` guard, ancs_c_init returned -EINVAL and ancs_main
 * rebooted the SoC at t = 6.6 s -- so bt_start() (advertising) was never
 * reached.  Call the raw identities, which recon/application/app/CMakeLists.txt
 * links alongside (not instead of) the stock owner. */
extern int FUN_0007f772(int,...);
extern int FUN_0007f79e(int,...);
#define bt_ancs_register_attr     FUN_0007f772
#define bt_ancs_register_app_attr FUN_0007f79e
#define C8 (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define CC (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)

int ancs_c_init(int param_1, unsigned param_2, unsigned param_3, unsigned param_4)
{
    int iVar1; unsigned uVar2;
    iVar1 = ancs_service_ctx_clear(((unsigned long)&g_ancs_client) /*=0x20006ae8*/);
    if(iVar1 == 0){
        iVar1 = bt_ancs_register_attr(((unsigned long)&g_ancs_client) /*=0x20006ae8*/, 0, param_1+0x10, 0x20, param_4);
        if(iVar1 == 0){
            iVar1 = bt_ancs_register_app_attr(((unsigned long)&g_ancs_client) /*=0x20006ae8*/, 0, param_1+0x30, 0x20);
            if(iVar1 == 0){
                iVar1 = bt_ancs_register_attr(((unsigned long)&g_ancs_client) /*=0x20006ae8*/, 1, param_1+0x50, 0x20, param_4);
                if(iVar1 == 0){
                    iVar1 = bt_ancs_register_attr(((unsigned long)&g_ancs_client) /*=0x20006ae8*/, 2, param_1+0x70, 0x20, param_4);
                    if(iVar1 == 0){
                        iVar1 = bt_ancs_register_attr(((unsigned long)&g_ancs_client) /*=0x20006ae8*/, 3, param_1+0x90, 0x100);
                        if(iVar1 == 0){
                            iVar1 = bt_ancs_register_attr(((unsigned long)&g_ancs_client) /*=0x20006ae8*/, 5, param_1+400, 0x20);
                            if(iVar1 == 0) return 0;
                            if(C8 < 1) return iVar1;
                            if(CC == 0){ uVar2 = 0x3e4; goto LAB_00019090; }
                            uVar2 = 0x3e4;
                        } else {
                            if(C8 < 1) return iVar1;
                            if(CC == 0){ uVar2 = 0x3dc;
LAB_00019090:
                                log_message(((unsigned long)"%s(): %d: err=%d\n") /*=0x9ab0c*/, ((unsigned long)"ancs_c_init") /*=0x9b15e*/, uVar2, iVar1); return iVar1; }
                            uVar2 = 0x3dc;
                        }
                    } else {
                        if(C8 < 1) return iVar1;
                        if(CC == 0){ uVar2 = 0x3d4; goto LAB_00019090; }
                        uVar2 = 0x3d4;
                    }
                } else {
                    if(C8 < 1) return iVar1;
                    if(CC == 0){ uVar2 = 0x3cc; goto LAB_00019090; }
                    uVar2 = 0x3cc;
                }
            } else {
                if(C8 < 1) return iVar1;
                if(CC == 0){ uVar2 = 0x3c4; goto LAB_00019090; }
                uVar2 = 0x3c4;
            }
        } else {
            if(C8 < 1) return iVar1;
            if(CC == 0){ uVar2 = 0x3bc; goto LAB_00019090; }
            uVar2 = 0x3bc;
        }
    } else {
        if(C8 < 1) return iVar1;
        if(CC == 0){ uVar2 = 0x3b4; goto LAB_00019090; }
        uVar2 = 0x3b4;
    }
    debug_print(((unsigned long)"%s(): %d: err=%d\n") /*=0x9ab0c*/, ((unsigned long)"ancs_c_init") /*=0x9b15e*/, uVar2, iVar1);
    return iVar1;
}
