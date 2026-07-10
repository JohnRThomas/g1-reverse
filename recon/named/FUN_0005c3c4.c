/* named: FUN_0005c3c4 */
/* Reconstructed FUN_0005c3c4 @ 0x5c3c4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void* FUN_00059c70(void);
extern void gatt_sub_free(void*);
extern int gatt_write_ccc(int,int*);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);
extern void FUN_000828da(void*,int);

int FUN_0005c3c4(int param_1,int *param_2){
  if(param_1 == 0){
    printk(0x00099cbd,0x000f3ebd,0x000f46b8,0x147d);
    printk(0x000f4a0a);
    assert_post_action(0x000f46b8,0x147d);
  }
  if(param_2 == 0 || *param_2 == 0){
    printk(0x00099cbd,0x000f4d35,0x000f46b8,0x147e);
    printk(0x000f4a0a);
    assert_post_action(0x000f46b8,0x147e);
  }
  if((short)param_2[4] == 0){
    printk(0x00099cbd,0x000f4d4e,0x000f46b8,0x147f);
    printk(0x000f4a0a);
    assert_post_action(0x000f46b8,0x147f);
  }
  if(*(short*)((int)param_2 + 0xe) == 0){
    printk(0x00099cbd,0x000f4d5c,0x000f46b8,0x1485);
    printk(0x000f4a0a);
    assert_post_action(0x000f46b8,0x1485);
  }
  if(*(char*)(param_1 + 0xd) != 7) return -0x80;
  unsigned char *puVar2 = (unsigned char*)FUN_00059c70();
  if(puVar2 == 0){
    puVar2 = (unsigned char*)FUN_00059c70();
    if(puVar2 == 0) return -0xc;
    FUN_000828da(puVar2 + 1, param_1 + 0x90);
    *puVar2 = *(unsigned char*)(param_1 + 8);
  }
  int *piVar5 = *(int**)(puVar2 + 8);
  if(piVar5 != 0){
    int bVar1 = 0;
    do{
      if(param_2 == piVar5 - 6) return -0x78;
      if(((short)piVar5[-3] == (short)param_2[3]) &&
         (*(unsigned short*)(param_2 + 4) <= *(unsigned short*)(piVar5 - 2)))
        bVar1 = 1;
      piVar5 = (int*)*piVar5;
    }while(piVar5 != 0);
    if(bVar1) goto LAB;
  }
  {
    int iVar3 = gatt_write_ccc(param_1, param_2);
    if(iVar3 != 0){
      if(*(int*)(puVar2 + 8) != 0) return iVar3;
      gatt_sub_free(puVar2);
      return iVar3;
    }
  }
LAB:
  param_2[6] = *(int*)(puVar2 + 8);
  *(int**)(puVar2 + 8) = param_2 + 6;
  if(*(int*)(puVar2 + 0xc) == 0)
    *(int**)(puVar2 + 0xc) = param_2 + 6;
  return 0;
}

