#include "g1_app_symbols.h"
/* named: ble_privacy_request_random_address */
/* Reconstructed ble_privacy_request_random_address @ 0x552ac  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00053d70(int,int,void*);
extern void FUN_0008104a(uint32_t,int,void*);
extern int memcmp(int,uint32_t,int);
extern void FUN_00080fba(int,int);
extern void net_buf_unref(int);
uint32_t ble_privacy_request_random_address(uint8_t* param_1){
  int local_34[5];
  uint32_t local_20;
  if(param_1==0){
    local_20=2;
    FUN_0008104a(((uintptr_t)&tbl_880d8) /*=0x88150*/,0x1080,&local_20);
    return 0;
  }
  int iVar1=FUN_00053d70(0x1009,0,local_34);
  if(iVar1!=0){
    local_20=2;
    FUN_0008104a(((uintptr_t)&tbl_880d8) /*=0x88150*/,0x1080,&local_20);
    return 0;
  }
  int iVar2=*(volatile int*)(local_34[0]+0xc)+1;
  int r=memcmp(iVar2,((uintptr_t)&rodata_f2b47) /*=0xf2b47*/,6);
  if(r!=0){
    r=memcmp(iVar2,((uintptr_t)&rodata_f2b41) /*=0xf2b41*/,6);
    if(r!=0){
      FUN_00080fba((int)param_1+1,iVar2);
      *param_1=0;
      net_buf_unref(local_34[0]);
      return 1;
    }
  }
  net_buf_unref(local_34[0]);
  return 0;
}

