#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_app_shared_ctx_blob__param_0007        [param_0007; G1-original]
 * Raw function identity: 0x00019cd0.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00019cd0 @ 0x00019cd0
 * public-name: parse_receiver_pack_pkcs7
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_9b371                             @ 0x0009b371
 *   rodata_9b3b5                             @ 0x0009b3b5
 *   rodata_9b3e0                             @ 0x0009b3e0
 *   rodata_9e0d0                             @ 0x0009e0d0
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_pkcs7_pack_offset                      @ 0x2000d6f4
 *   g_pkcs7_pack_cmd_id                      @ 0x20010320
 */
/* Reconstructed parse_receiver_pack_pkcs7 @ 0x19cd0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void log_message(uint32_t, ...);
extern void debug_print(uint32_t, ...);
extern void memcpy(int, ...);

unsigned int parse_receiver_pack_pkcs7(int param_1, unsigned char *param_2, unsigned int param_3)
{
    unsigned char bVar1, bVar2;
    unsigned short uVar3;
    unsigned char *pbVar4 = (unsigned char*)((unsigned long)&g_pkcs7_pack_cmd_id) /*=0x20010320*/;
    unsigned short *puVar5 = (unsigned short*)((unsigned long)&g_pkcs7_pack_offset) /*=0x2000d6f4*/;
    unsigned int uVar6;
    unsigned int uVar7;
    int iVar8;
    unsigned int uVar9;

    if (param_2 == (unsigned char*)0) {
        uVar7 = 0xb0;
        iVar8 = *(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        uVar6 = ((unsigned long)&rodata_9b371) /*=0x9b371*/;
    } else {
        if (param_1 != 0) {
            if (param_3 < 3) {
                if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ != 0) {
                    debug_print(((unsigned long)&rodata_9b3b5) /*=0x9b3b5*/, ((unsigned long)&rodata_9e0d0) /*=0x9e0d0*/, 0xbbUL, param_3);
                    return 0xca;
                }
                log_message(((unsigned long)&rodata_9b3b5) /*=0x9b3b5*/, ((unsigned long)&rodata_9e0d0) /*=0x9e0d0*/, 0xbbUL, param_3);
                return 0xca;
            }
            bVar1 = param_2[2];
            uVar9 = (unsigned int)*param_2;
            bVar2 = param_2[1];
            if (bVar1 == 0) {
                *pbVar4 = *param_2;
                *puVar5 = (unsigned short)bVar1;
            }
            if (*pbVar4 != uVar9) {
                if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ != 0) {
                    debug_print(((unsigned long)&rodata_9b3e0) /*=0x9b3e0*/, ((unsigned long)&rodata_9e0d0) /*=0x9e0d0*/);
                    return 0xca;
                }
                log_message(((unsigned long)&rodata_9b3e0) /*=0x9b3e0*/, ((unsigned long)&rodata_9e0d0) /*=0x9e0d0*/, 0xd0UL, uVar9, (unsigned int)*pbVar4);
                return 0xca;
            }
            uVar3 = *puVar5;
            memcpy(param_1 + (unsigned int)uVar3, param_2 + 3, param_3 - 3, uVar9, param_1, param_2);
            if ((unsigned int)bVar1 == (unsigned int)(bVar2 - 1)) {
                uVar6 = 0xc9;
            } else {
                uVar6 = 0xcb;
            }
            *puVar5 = (unsigned short)((int)param_3 + (uVar3 - 3));
            return uVar6;
        }
        uVar7 = 0xb5;
        iVar8 = *(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        uVar6 = 0x0009b38fUL;
    }
    if (iVar8 == 0) {
        log_message(uVar6, ((unsigned long)&rodata_9e0d0) /*=0x9e0d0*/, uVar7);
    } else {
        debug_print(uVar6, ((unsigned long)&rodata_9e0d0) /*=0x9e0d0*/, uVar7);
    }
    return 0xca;
}
