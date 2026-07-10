/* named: bt_keys_store */
/* Reconstructed bt_keys_store @ 0x5ec18  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void printk(unsigned int,unsigned int,unsigned int,int);
extern void assert_post_action(unsigned int,int);
extern int FUN_00053168(unsigned int,void*,void*,int);
extern void FUN_0004d944(unsigned int,unsigned int,void*,int);
int bt_keys_store(unsigned char* param_1){
  int iVar1;
  struct{unsigned int a,b; int c;} log;
  if(param_1==0){
    printk(0x00099cbd,0x000f5298,0x000f5268,0x146);
    assert_post_action(0x000f5268,0x146);
  }
  iVar1=FUN_00053168(*param_1,param_1+1,param_1+0xc,0x50);
  if(iVar1!=0){
    log.b=0x000f5353; log.a=3; log.c=iVar1;
    FUN_0004d944(0x00088158,0x1840,&log,0);
  }
  return iVar1;
}

