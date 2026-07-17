#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00025850 @ 0x00025850
 * public-name: ipc_ept_op_c_locked_retry
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_ept_op_c_locked_retry                <= FUN_00025850 @ 0x00025850
 *   sleep_fixed_33_ticks                     <= FUN_0007c87a @ 0x0007c87a
 *   set_uart_line_ctrl_dtr                   <= FUN_0007c882 @ 0x0007c882
 * address symbols (name @ address):
 *   rodata_9f2be                             @ 0x0009f2be
 */
/* Reconstructed FUN_00025850 @ 0x25850  (parity: 300/300 trials, PROVEN) */
extern void FUN_0007c872(unsigned,unsigned,unsigned,unsigned);
extern int set_uart_line_ctrl_dtr(int,unsigned,unsigned,int);
extern void FUN_0007c876(unsigned);
extern unsigned long long sleep_fixed_33_ticks(void);
extern void log_message(unsigned,unsigned,unsigned,int);
int ipc_ept_op_c_locked_retry(int param_1, unsigned param_2, unsigned param_3, int param_4){
    int iVar1;
    if (param_4 == 0){ iVar1 = 0; }
    else {
        int iVar3 = 0x14;
        int iVar4 = *(int*)(param_1 + 4);
        unsigned uVar5 = *(unsigned*)(param_1 + 0x10);
        unsigned lock_arg = param_2;
        while (1){
            FUN_0007c872(uVar5, lock_arg, 0xffffffff, 0xffffffff);
            iVar1 = set_uart_line_ctrl_dtr(iVar4, param_2, param_3, param_4);
            FUN_0007c876(uVar5);
            if (iVar1 == 0) break;
            iVar3 = iVar3 - 1;
            if (iVar3 == 0){
                log_message(((unsigned long)&rodata_9f2be) /*=0x9f2be*/, (*(unsigned short*)(iVar4 + 8)) | 4, param_2, iVar1);
                return iVar1;
            }
            lock_arg = (unsigned)(sleep_fixed_33_ticks() >> 32);
        }
    }
    return iVar1;
}
