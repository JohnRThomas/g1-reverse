#include "g1_app_symbols.h"
/* named: ble_conn_pool_alloc */
/* Reconstructed ble_conn_pool_alloc @ 0x562a4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int k_work_init(int,int);
extern int FUN_000732d4(int,int);
extern int memset_bytes(int,int,int,int,int);
int ble_conn_pool_alloc(int param_1, int param_2, int param_3, int param_4){
  int iVar1 = 0;
  volatile int *piVar2;
  while(1){
    if(iVar1==param_2) return 0;
    piVar2 = (volatile int*)(param_1+0xd0);
    if(*piVar2==0) break;
    param_1 += 0xd8;
    iVar1 += 1;
  }
  *piVar2 = 1;
  if(param_1==0) return 0;
  memset_bytes(param_1,0,0xd0,(int)piVar2,param_4);
  FUN_000732d4(param_1+0x60, ((uintptr_t)&tbl_5709c) /*=0x570a1*/);
  k_work_init(param_1+0x28, ((uintptr_t)&rodata_813d1) /*=0x813d1*/);
  return param_1;
}

