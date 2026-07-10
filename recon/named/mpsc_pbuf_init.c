/* named: mpsc_pbuf_init */
/* Reconstructed mpsc_pbuf_init @ 0x4bc28  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int assert_post_action(int,int);
extern int printk(int,...);
extern int z_impl_k_sem_init(int,int,int);
extern int memset_bytes(int,int,int);
void mpsc_pbuf_init(int param_1, uint32_t *param_2, uint32_t param_3, uint32_t param_4){
  memset_bytes(param_1, 0, 0x20);
  *(volatile uint32_t*)(param_1+0x1c) = param_2[3];
  *(volatile uint32_t*)(param_1+0x18) = param_2[2];
  *(volatile uint32_t*)(param_1+0x20) = param_2[0];
  uint32_t uVar3 = param_2[1];
  *(volatile uint32_t*)(param_1+0x28) = 0;
  *(volatile uint32_t*)(param_1+0x24) = uVar3;
  uint32_t uVar2 = param_2[4];
  if(uVar3 != 0 && ((uVar3 - 1) & uVar3) == 0){
    uVar2 |= 1;
  }
  *(volatile uint32_t*)(param_1+0x10) = uVar2;
  int iVar1 = z_impl_k_sem_init(param_1+0x2c, 0, 1);
  if(iVar1 != 0){
    printk(0x00099cbd, 0x000a7a10, 0x000f0982, 0x2e);
    assert_post_action(0x000f0982, 0x2e);
  }
}

