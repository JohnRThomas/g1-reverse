/* readable reconstruction; identity: FUN_00059730 @ 0x00059730
 * public-name: att_handle_rsp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_att_req_free                          <= FUN_00059708 @ 0x00059708
 *   att_handle_rsp                           <= FUN_00059730 @ 0x00059730
 *   k_work_cancel_delayable                  <= FUN_00073518 @ 0x00073518
 *   att_req_send_process                     <= FUN_000820ae @ 0x000820ae
 * address symbols (name @ address):
 *   rodata_88100                             @ 0x00088100
 *   rodata_f4680                             @ 0x000f4680
 *   cancel_req                               @ 0x2000aea0
 */
/* Reconstructed FUN_00059730 @ 0x59730  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int bt_att_req_free(void *);
extern int k_work_cancel_delayable(void *, unsigned, unsigned, unsigned);
extern int FUN_00081ddc(int,...);
extern int att_req_send_process(int,...);
typedef void (*codep)(unsigned,...);
unsigned att_handle_rsp(unsigned *param_1, unsigned param_2, unsigned param_3, unsigned param_4){
  volatile unsigned local[2];
  k_work_cancel_delayable(param_1+0x58, param_2, param_3, param_4);
  int iVar1 = (int)param_1[0x49];
  if(iVar1==0){
    local[1]=0xf4680;
    local[0]=2;
    FUN_00081ddc(0x88100,0x1080,(int)local);
  } else {
    if(iVar1 != 0x2000aea0){
      codep pcVar2 = *(codep*)(iVar1+4);
      *(volatile unsigned*)(iVar1+4)=0;
      unsigned uVar3 = *(volatile unsigned*)((int)param_1[0x49]+0x18);
      bt_att_req_free((void *)param_1[0x49]);
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
