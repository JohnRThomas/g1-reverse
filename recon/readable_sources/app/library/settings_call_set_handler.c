#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_5          => struct g1_layout_settings_set_handler_args__param_0153  [param_0153; library]
 * Raw function identity: 0x0004e604.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0004e604 @ 0x0004e604
 * public-name: settings_call_set_handler
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   settings_parse_and_lookup                <= FUN_0004e540 @ 0x0004e540
 *   settings_call_set_handler                <= FUN_0004e604 @ 0x0004e604
 *   settings_name_steq                       <= FUN_0007f1a0 @ 0x0007f1a0
 * address symbols (name @ address):
 *   rodata_88278                             @ 0x00088278
 *   rodata_f1180                             @ 0x000f1180
 */
/* Reconstructed FUN_0004e604 @ 0x4e604  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32;
typedef u32 (*fp4)(u32,u32,u32,u32);
typedef u32 (*fp5)(u32,u32,u32,u32,u32);
extern int settings_name_steq(u32,int,void*);
extern int settings_parse_and_lookup(u32,void*);
extern void z_log_msg_runtime_create(u32,int,void*,int);
u32 settings_call_set_handler(u32 param_1,u32 param_2,u32 param_3,u32 param_4,int* param_5){
    u32 local_24 = param_1;
    if(param_5 != 0){
        if(*param_5 != 0){
            int iVar1 = settings_name_steq(param_1, *param_5, &local_24);
            if(iVar1 == 0) return 0;
        }
        if(param_5[1] != 0){
            return ((fp5)(uintptr_t)param_5[1])(local_24, param_2, param_3,
                                                param_4, (u32)param_5[2]);
        }
    }
    int iVar1 = settings_parse_and_lookup(param_1, &local_24);
    if(iVar1 != 0){
        u32 local_34 = (*(fp4*)(iVar1+8))(local_24, param_2, param_3, param_4);
        if(local_34 != 0){
            struct diagnostic_record {
                u32 type;
                u32 message;
                u32 argument;
                u32 error;
                uint16_t flags;
            };
            unsigned char *scratch = __builtin_alloca(40);
            struct diagnostic_record *record =
                (struct diagnostic_record *)(scratch + 24);
            record->type = 0x01000004;
            record->message = ((unsigned long)&rodata_f1180) /*=0xf1180*/;
            record->argument = param_1;
            record->error = local_34;
            record->flags = 0x200;
            z_log_msg_runtime_create(((unsigned long)&rodata_88278) /*=0x88278*/, 0x2440, record, 0);
        }
    }
    return 0;
}
