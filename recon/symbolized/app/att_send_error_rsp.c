#include "g1_app_symbols.h"
/* named: att_send_error_rsp */
/* Reconstructed att_send_error_rsp @ 0x821f4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern long long bt_att_chan_create_pdu(unsigned,int);
extern int tail_58568(void);
extern unsigned char* net_buf_simple_add(int,int);
extern int bt_att_chan_send_rsp(unsigned,int);
void att_send_error_rsp(unsigned param_1, int param_2, unsigned short param_3, unsigned param_4){
    if (param_2 == 0) return;
    long long uVar5 = bt_att_chan_create_pdu(param_1, 1);
    int iVar1 = (int)uVar5;
    if (iVar1 == 0){ tail_58568(); return; }
    unsigned char* puVar2 = net_buf_simple_add(iVar1 + 0xc, 4);
    *(volatile unsigned char*)puVar2 = (unsigned char)param_2;
    *(volatile unsigned short*)(puVar2 + 1) = param_3;
    *(volatile unsigned char*)(puVar2 + 3) = (unsigned char)param_4;
    bt_att_chan_send_rsp(param_1, iVar1);
}

