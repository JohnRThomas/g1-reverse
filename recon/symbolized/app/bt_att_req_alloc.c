#include "g1_app_symbols.h"
/* named: bt_att_req_alloc */
/* globals referenced:
//   0x20003798  req_slab                     
//   0x2000ae9c  att_handle_rsp_thread        
*/
/* Reconstructed bt_att_req_alloc @ 0x596c0  (parity: 300/300 trials, PROVEN) */

extern int k_current_get(void);
extern int k_mem_slab_alloc(int a, int *b, int c, int d, int e);
extern int memset_bytes(int a, int b, int c);

int bt_att_req_alloc(int param_1, int param_2, int param_3)
{
  int iVar1;
  int uVar2;
  int local_14 = 0;

  uVar2 = param_1;
  iVar1 = k_current_get();
  if (*(volatile int*)((uintptr_t)&att_handle_rsp_thread) /*=0x2000ae9c*/ == iVar1) {
    param_2 = 0;
    param_1 = param_2;
  }
  iVar1 = k_mem_slab_alloc(((uintptr_t)&req_slab) /*=0x20003798*/, &local_14, param_1, param_2, uVar2);
  if (iVar1 == 0) {
    uVar2 = memset_bytes(local_14, 0, 0x1c);
  } else {
    uVar2 = 0;
  }
  return uVar2;
}

