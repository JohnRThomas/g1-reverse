#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_ipc_ept_locked_retry_ctx__param_0060   [param_0060; G1-original]
 * Raw function identity: 0x000257ec.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000257ec @ 0x000257ec
 * public-name: ipc_ept_op_b_locked_retry
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_ept_op_b_locked_retry                <= FUN_000257ec @ 0x000257ec
 *   sleep_fixed_33_ticks                     <= FUN_0007c87a @ 0x0007c87a
 *   json_arr_encode                          <= FUN_0007c898 @ 0x0007c898
 * address symbols (name @ address):
 *   rodata_9f285                             @ 0x0009f285
 */
/* Reconstructed FUN_000257ec @ 0x257ec  (parity: 300/300 trials, PROVEN) */
extern void firmware_function_0007c872(unsigned,unsigned,unsigned,unsigned);
extern int json_arr_encode(int,unsigned,unsigned,int);
extern void firmware_function_0007c876(unsigned);
extern unsigned long long sleep_fixed_33_ticks(void);
extern void log_message(unsigned,unsigned,unsigned,int);
int ipc_ept_op_b_locked_retry(int param_1, unsigned param_2, unsigned param_3, int param_4){
    int iVar1;
    if (param_4 == 0){ iVar1 = 0; }
    else {
        int iVar3 = 0x14;
        int iVar4 = *(int*)(param_1 + 4);
        unsigned uVar5 = *(unsigned*)(param_1 + 0x10);
        unsigned lock_arg = param_2;
        while (1){
            firmware_function_0007c872(uVar5, lock_arg, 0xffffffff, 0xffffffff);
            iVar1 = json_arr_encode(iVar4, param_2, param_3, param_4);
            firmware_function_0007c876(uVar5);
            if (iVar1 == 0) break;
            iVar3 = iVar3 - 1;
            if (iVar3 == 0){
                log_message(((unsigned long)&rodata_9f285) /*=0x9f285*/, (*(unsigned short*)(iVar4 + 8)) | 4, param_2, iVar1);
                return iVar1;
            }
            lock_arg = (unsigned)(sleep_fixed_33_ticks() >> 32);
        }
    }
    return iVar1;
}
