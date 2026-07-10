#include "g1_app_symbols.h"
/* named: cjson_create_number */
/* globals referenced:
//   0x20002bac  g_cjson_hooks                
*/
/* Reconstructed cjson_create_number @ 0x12c18  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int __aeabi_dcmple(int,int,int,int);
extern int __aeabi_dcmpge(int,int,int,int);
extern int __fixdfsi(int,int);
extern int alloc_zeroed_node(int);
int cjson_create_number(double darg){
  union { double d; uint32_t w[2]; } u; u.d = darg;
  uint32_t param_1 = u.w[0];
  uint32_t param_2 = u.w[1];
  int iVar1 = alloc_zeroed_node(*(volatile uint32_t*)((uintptr_t)&g_cjson_hooks) /*=0x20002bac*/);
  if(iVar1 != 0){
    *(volatile uint32_t*)(iVar1+0x18) = param_1;
    *(volatile uint32_t*)(iVar1+0x1c) = param_2;
    *(volatile uint32_t*)(iVar1+0xc) = 8;
    int iVar2 = __aeabi_dcmpge(param_1,param_2,0,0);
    if(iVar2==0){
      iVar2 = __aeabi_dcmple(param_1,param_2,0,0);
      if(iVar2==0){
        int uVar3 = __fixdfsi(param_1,param_2);
        *(volatile uint32_t*)(iVar1+0x14) = uVar3;
        return iVar1;
      }
      *(volatile uint32_t*)(iVar1+0x14) = 0x80000000UL;
    } else {
      *(volatile uint32_t*)(iVar1+0x14) = 0x7fffffffUL;
    }
  }
  return iVar1;
}

