#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000256dc @ 0x000256dc
 * public-name: ipc_ept_op_a_locked_retry
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_send_cmd16_payload                   <= FUN_00025670 @ 0x00025670
 *   ipc_ept_op_a_locked_retry                <= FUN_000256dc @ 0x000256dc
 *   sleep_fixed_33_ticks                     <= FUN_0007c87a @ 0x0007c87a
 * address symbols (name @ address):
 *   rodata_9f203                             @ 0x0009f203
 */
/* Reconstructed FUN_000256dc @ 0x256dc  (parity: 300/300 trials, PROVEN) */
extern void thunk_FUN_000723b8(unsigned,unsigned,unsigned,unsigned,int,unsigned);
extern int dev_send_cmd16_payload(int,unsigned,unsigned,unsigned,int);
extern void thunk_FUN_00072558(unsigned);
extern unsigned long long sleep_fixed_33_ticks(void);
extern void log_message(unsigned,unsigned,unsigned,int);
int ipc_ept_op_a_locked_retry(int param_1, unsigned param_2, unsigned param_3, int param_4){
    int iVar1;
    if (param_4 == 0){ iVar1 = 0; }
    else {
        int iVar4 = 0x14;
        int iVar3 = *(int*)(param_1 + 4);
        unsigned uVar5 = *(unsigned*)(param_1 + 0x10);
        unsigned lock_arg = param_2;
        while (1){
            thunk_FUN_000723b8(uVar5, lock_arg, 0xffffffff, 0xffffffff, param_1, param_2);
            iVar1 = dev_send_cmd16_payload(iVar3, *(unsigned short*)(iVar3 + 8), param_2, param_3, param_4);
            thunk_FUN_00072558(uVar5);
            if (iVar1 == 0) break;
            iVar4 = iVar4 - 1;
            if (iVar4 == 0){
                log_message(((unsigned long)&rodata_9f203) /*=0x9f203*/, *(unsigned short*)(iVar3 + 8), param_2, iVar1);
                return iVar1;
            }
            lock_arg = (unsigned)(sleep_fixed_33_ticks() >> 32);
        }
    }
    return iVar1;
}
