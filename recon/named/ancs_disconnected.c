/* named: ancs_disconnected */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20006ab8  g_ancs_active_conn           
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed ancs_disconnected @ 0x18adc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned int,unsigned int,void*,unsigned int);
extern int get_device_info(void);
extern void format_bt_addr_str(unsigned int,void*);
extern void ancs_cancel_timers(void);
extern void debug_print(unsigned int,unsigned int,void*,unsigned int);
extern void mutex_lock_syscall_handler(int,int,unsigned int,unsigned int);
extern unsigned int FUN_00081526(void);
void ancs_disconnected(unsigned int param_1,unsigned int param_2){
  int iVar3; unsigned int uVar2; unsigned char auStack_30[36];
  *(volatile unsigned char*)(*(volatile int*)0x20006ab8UL+0x365)=0;
  *(volatile int*)0x20007518UL=0;
  uVar2=FUN_00081526();
  format_bt_addr_str(uVar2,auStack_30);
  if(*(volatile int*)0x2000230cUL>0){
    if(*(volatile int*)0x20007554UL==0){
      DEBUG_PRINT(0x0009a92a,0x0009b1c8,auStack_30,param_2);
    } else {
      debug_print(0x0009a92a,0x0009b1c8,auStack_30,param_2);
    }
  }
  *(volatile unsigned char*)(*(volatile int*)0x20006ab8UL+0x367)=0;
  while(1){
    iVar3=get_device_info();
    if(*(volatile int*)(iVar3+0x9b4)==0) break;
    iVar3=get_device_info();
    mutex_lock_syscall_handler(iVar3+0x9ac,0,0xffffffff,0xffffffff);
  }
  ancs_cancel_timers();
  (void)param_1;
}

