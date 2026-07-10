/* named: gpiote_channel_release_if_unshared */
/* globals referenced:
//   0x20002bc0  g_gpiote_cb                  
*/
/* Reconstructed gpiote_channel_release_if_unshared @ 0x65504  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern int nrfx_flag32_free(uint32_t);
extern int get_pin_idx(void);
extern void assert_post_action(uint32_t,uint32_t);
extern void printk(uint32_t,uint32_t,uint32_t,uint32_t);
void gpiote_channel_release_if_unshared(void){
  int iVar3=get_pin_idx();
  int iVar4=0x20002bc0;
  uint16_t uVar1=*(volatile uint16_t*)(0x20002bc0UL+(iVar3+8)*2);
  if((int)((uint)uVar1<<0x17)<0){
    uint uVar5=((uint)uVar1<<0x13)>>0x1c;
    *(volatile uint16_t*)(0x20002bc0UL+(iVar3+8)*2)=uVar1 & 0xe0ff;
    int i=0;
    volatile uint16_t* puVar6=(volatile uint16_t*)(iVar4+0xe);
    do{
      puVar6=puVar6+1;
      if(((*puVar6 & 0x100)!=0) && (uVar5==(((uint)*puVar6<<0x13)>>0x1c))) return;
      i=i+1;
    }while(i!=0x30);
    *(volatile uint32_t*)(iVar4+uVar5*8)=0;
    int iVar4b=nrfx_flag32_free(0x20002c34);
    if(iVar4b!=0x0bad0000){
      printk(0x99cbd,0xf0ac7,0xf6b00,0x15f);
      assert_post_action(0xf6b00,0x15f);
    }
  }
}

