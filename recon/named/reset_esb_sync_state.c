/* readable reconstruction; identity: FUN_0007ce60 @ 0x0007ce60
 * public-name: reset_esb_sync_state
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   reset_esb_sync_state                     <= FUN_0007ce60 @ 0x0007ce60
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed FUN_0007ce60 @ 0x7ce60  (parity: 300/300 trials, PROVEN) */
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
