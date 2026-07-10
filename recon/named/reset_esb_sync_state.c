/* named: reset_esb_sync_state */
/* Reconstructed reset_esb_sync_state @ 0x7ce60  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int get_device_info(void);
extern void memset_bytes(int,int,int,unsigned int);
void reset_esb_sync_state(int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4){
  int iVar1;
  iVar1=get_device_info(); *(volatile unsigned char*)(iVar1+0xe9)=0;
  iVar1=get_device_info(); *(volatile unsigned char*)(iVar1+0xea)=0;
  iVar1=get_device_info(); *(volatile unsigned char*)(iVar1+0xcc)=0;
  iVar1=get_device_info(); *(volatile unsigned char*)(iVar1+0xcd)=0;
  iVar1=get_device_info(); *(volatile unsigned char*)(iVar1+0xce)=0;
  iVar1=get_device_info(); *(volatile unsigned char*)(iVar1+0xcf)=0;
  if(param_1==0){
    iVar1=get_device_info(); *(volatile unsigned char*)(*(volatile int*)(iVar1+0x100c)+7)=0xd;
  } else {
    iVar1=get_device_info(); *(volatile unsigned char*)(*(volatile int*)(iVar1+0x100c)+7)=0;
    iVar1=get_device_info(); **(volatile unsigned char**)(iVar1+0x100c)=0;
  }
  iVar1=get_device_info();
  memset_bytes(*(volatile int*)(iVar1+0x100c)+8,0,399,param_4);
}

