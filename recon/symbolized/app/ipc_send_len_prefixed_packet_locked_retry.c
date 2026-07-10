#include "g1_app_symbols.h"
/* named: ipc_send_len_prefixed_packet_locked_retry */
/* Reconstructed ipc_send_len_prefixed_packet_locked_retry @ 0x25788  (parity: 300/300 trials, PROVEN) */
extern void thunk_FUN_000723b8(unsigned,unsigned,unsigned,unsigned,int,unsigned);
extern int ipc_send_len_prefixed_packet(int,unsigned,unsigned,unsigned);
extern void thunk_FUN_00072558(unsigned);
extern void sleep_fixed_33_ticks(void);
extern void DEBUG_PRINT(unsigned,unsigned,unsigned,int);
int ipc_send_len_prefixed_packet_locked_retry(int param_1, unsigned param_2, unsigned param_3, int param_4){
    int iVar1;
    if (param_4 == 0){ iVar1 = 0; }
    else {
        int iVar4 = 0x14;
        int iVar3 = *(int*)(param_1 + 4);
        unsigned uVar5 = *(unsigned*)(param_1 + 0x10);
        while (1){
            thunk_FUN_000723b8(uVar5, param_2, 0xffffffff, 0xffffffff, param_1, param_2);
            iVar1 = ipc_send_len_prefixed_packet(*(int*)iVar3, *(unsigned short*)(iVar3 + 8), param_2, param_3);
            thunk_FUN_00072558(uVar5);
            if (iVar1 == 0) break;
            iVar4 = iVar4 - 1;
            if (iVar4 == 0){
                DEBUG_PRINT("eeprom_st25dv_read addr %04X offset %04X failed %d\r\n" /*=0x9f250*/, *(unsigned short*)(iVar3 + 8), param_2, iVar1);
                return iVar1;
            }
            sleep_fixed_33_ticks();
        }
    }
    return iVar1;
}

