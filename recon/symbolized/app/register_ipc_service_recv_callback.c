#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00025ae8 @ 0x00025ae8
 * public-name: register_ipc_service_recv_callback
 * provenance: uncatalogued by Ghidra (gap 0x25ad2..0x25b78, immediately before
 *   its sibling global_ipc_service_send @0x25b78).  Extent derived from the
 *   original image bytes: code 0x25ae8..0x25b53 (0x6c B) + literal pool
 *   0x25b54..0x25b6b.  The function names itself through its own "%s()" log
 *   argument at 0x9f6a3.
 * callees (readable <= raw @ address):
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_9f512                             @ 0x0009f512
 *   rodata_9f540                             @ 0x0009f540
 *   rodata_9f6a3                             @ 0x0009f6a3
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ipc0_endpoint                          @ 0x20007a84
 */
/* Reconstructed register_ipc_service_recv_callback @ 0x25ae8
 * (cfg_verify PASS, 300/300 trials; plus 96/96 directed-fixture cases) */
#include <stdint.h>
extern void log_message(uint32_t, ...);
extern void debug_print(uint32_t, ...);

int register_ipc_service_recv_callback(unsigned int param_1)
{
    int *piVar1;
    int iVar2;
    int iVar3;

    piVar1 = *(int * volatile *)((unsigned long)&g_ipc0_endpoint) /*=0x20007a84*/;
    iVar2 = *(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    iVar3 = piVar1[1];
    if (iVar3 < 0x16) {
        piVar1[iVar3 + 2] = (int)param_1;
        piVar1[1] = iVar3 + 1;
        if (2 < iVar2) {
            if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)&rodata_9f512) /*=0x9f512*/,
                            ((unsigned long)&rodata_9f6a3) /*=0x9f6a3*/,
                            *(volatile unsigned char *)param_1,
                            *(volatile int *)(param_1 + 4), iVar3 + 1);
            } else {
                debug_print(((unsigned long)&rodata_9f512) /*=0x9f512*/,
                            ((unsigned long)&rodata_9f6a3) /*=0x9f6a3*/,
                            *(volatile unsigned char *)param_1,
                            *(volatile int *)(param_1 + 4), iVar3 + 1);
            }
        }
        return 0;
    }
    if (0 < iVar2) {
        if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)&rodata_9f540) /*=0x9f540*/,
                        ((unsigned long)&rodata_9f6a3) /*=0x9f6a3*/,
                        *(volatile unsigned char *)param_1,
                        *(volatile int *)(param_1 + 4), iVar3, 0x16);
        } else {
            debug_print(((unsigned long)&rodata_9f540) /*=0x9f540*/,
                        ((unsigned long)&rodata_9f6a3) /*=0x9f6a3*/,
                        *(volatile unsigned char *)param_1,
                        *(volatile int *)(param_1 + 4), iVar3, 0x16);
        }
    }
    return -1;
}
