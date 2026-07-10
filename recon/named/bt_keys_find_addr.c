/* named: bt_keys_find_addr */
/* globals referenced:
//   0x2000af4c  bt_keys_pool                 
*/
/* Reconstructed bt_keys_find_addr @ 0x5e938  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int assert_post_action(int,int);
extern int printk(int,int,int,int);
extern int memcmp(int,int,int);
unsigned char *bt_keys_find_addr(uint32_t param_1, int param_2){
  unsigned char *pbVar1 = (unsigned char*)0x2000af4cUL;
  int iVar2;
  if(param_2==0){
    printk(0x00099cbd, 0x000f52ac, 0x000f5268, 0x11a);
    assert_post_action(0x000f5268, 0x11a);
    iVar2 = 1;
    return pbVar1 + iVar2*0x5c;
  }
  if((uint32_t)*(volatile uint8_t*)pbVar1 != param_1 ||
     memcmp((int)(pbVar1+1), param_2, 7) != 0){
    if((uint32_t)*(volatile uint8_t*)(pbVar1+0x5c) != param_1 ||
       memcmp(0x2000afa9, param_2, 7) != 0){
      return (unsigned char*)0;
    }
    iVar2 = 1;
  } else {
    iVar2 = 0;
  }
  return pbVar1 + iVar2*0x5c;
}

