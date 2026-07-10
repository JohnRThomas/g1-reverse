#include "g1_app_symbols.h"
/* named: att_handle_rsp */
/* Reconstructed att_handle_rsp @ 0x59730  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int bt_att_req_free(void);
extern int FUN_00073518(int,...);
extern int FUN_00081ddc(int,...);
extern int att_req_send_process(int,...);
typedef void (*codep)(unsigned,...);
unsigned att_handle_rsp(unsigned *param_1, unsigned param_2, unsigned param_3, unsigned param_4){
  volatile unsigned local[2];
  FUN_00073518((int)(param_1+0x58));
  int iVar1 = (int)param_1[0x49];
  if(iVar1==0){
    local[1]="No pending ATT request" /*=0xf4680*/;
    local[0]=2;
    FUN_00081ddc(((uintptr_t)&tbl_880d8) /*=0x88100*/,0x1080,(int)local);
  } else {
    if(iVar1 != ((uintptr_t)&cancel_req) /*=0x2000aea0*/){
      codep pcVar2 = *(codep*)(iVar1+4);
      *(volatile unsigned*)(iVar1+4)=0;
      unsigned uVar3 = *(volatile unsigned*)((int)param_1[0x49]+0x18);
      bt_att_req_free();
      param_1[0x49]=0;
      att_req_send_process((int)param_1[0]);
      if(pcVar2==0) return 0;
      (*pcVar2)(*(unsigned*)param_1[0], param_4, param_2, param_3, uVar3);
      return 0;
    }
    param_1[0x49]=0;
  }
  att_req_send_process((int)param_1[0]);
  return 0;
}

