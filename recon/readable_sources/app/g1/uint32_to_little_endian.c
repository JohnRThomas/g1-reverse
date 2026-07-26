#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_audio_fw_load_msg__param_0039          [param_0039; G1-original]
 * Raw function identity: 0x0004a568.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0004a568 @ 0x0004a568
 * public-name: uint32_to_little_endian
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_f02d2                             @ 0x000f02d2   [INLINED -- G6 literal batch]
 *   rodata_f02e7                             @ 0x000f02e7   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed uint32_to_little_endian @ 0x4a568  (parity: 300/300 trials, PROVEN) */


unsigned int uint32_to_little_endian(unsigned char *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int uVar1;
    if (param_1 == 0) {
        if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 1) {
            unsigned int sink=*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
            if (sink == 0) {
                log_message(((unsigned long)"%s(): buf is NULL !\n") /*=0xf02d2*/,((unsigned long)"uint32_to_little_endian") /*=0xf02e7*/,param_3,sink,param_4);
            } else {
                debug_print(((unsigned long)"%s(): buf is NULL !\n") /*=0xf02d2*/,((unsigned long)"uint32_to_little_endian") /*=0xf02e7*/,param_3,sink,param_4);
            }
        }
        uVar1 = 0;
    } else {
        param_1[0] = (unsigned char)param_2;
        param_1[1] = (unsigned char)(param_2 >> 8);
        param_1[2] = (unsigned char)(param_2 >> 16);
        param_1[3] = (unsigned char)(param_2 >> 24);
        uVar1 = 1;
    }
    return uVar1;
}
