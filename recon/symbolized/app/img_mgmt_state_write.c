#include "g1_app_symbols.h"
/* named: img_mgmt_state_write */
/* Reconstructed img_mgmt_state_write @ 0x51e9c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int smp_add_cmd_err(int,int,uint32_t);
extern int img_mgmt_state_read_51c98(int);
extern int img_mgmt_state_set_pending(int,int);
extern int FUN_00080872(int,void*,int,void*);
extern void nullsub_4(void);
extern void nullsub_5(void);
int img_mgmt_state_write(int param_1){
    int iVar7=*(volatile int*)(param_1+8);
    int r4=*(volatile int*)(param_1+4);
    int iVar1=FUN_00080872(r4+4,(void*)0,2,(void*)0);
    if(iVar1!=0) return 3;
    nullsub_4();
    iVar1=smp_add_cmd_err(iVar7+4,1,0x18);
    nullsub_5();
    if(iVar1!=0) return 0;
    return 7;
}

