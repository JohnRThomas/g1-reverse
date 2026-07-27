#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005c3c4 @ 0x0005c3c4
 * public-name: gatt_subscribe_add
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_find_conn_in_known_table            <= FUN_00059c70 @ 0x00059c70
 *   gatt_sub_free                            <= FUN_00059e78 @ 0x00059e78
 *   gatt_write_ccc                           <= FUN_0005a540 @ 0x0005a540
 *   gatt_subscribe_add                       <= FUN_0005c3c4 @ 0x0005c3c4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   bt_addr_le_copy_828da                    <= FUN_000828da @ 0x000828da
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f3ebd                             @ 0x000f3ebd
 *   rodata_f46b8                             @ 0x000f46b8
 *   rodata_f4a0a                             @ 0x000f4a0a   [INLINED -- G6 literal batch]
 *   rodata_f4d35                             @ 0x000f4d35   [INLINED -- G6 literal batch]
 *   rodata_f4d4e                             @ 0x000f4d4e   [INLINED -- G6 literal batch]
 *   rodata_f4d5c                             @ 0x000f4d5c   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_0005c3c4 @ 0x5c3c4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../headers/g1_log.h"
extern void* gatt_find_conn_in_known_table(void);
extern void gatt_sub_free(void*);
extern int gatt_write_ccc(void *, unsigned char *);
extern void assert_post_action(const char *, unsigned int);
extern void bt_addr_le_copy_828da(unsigned long*, unsigned long*);

int gatt_subscribe_add(int param_1,int *param_2){
  if(param_1 == 0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f3ebd) /*=0xf3ebd*/,((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0x147d);
    printk(((unsigned long)"\tinvalid parameters\n\n") /*=0xf4a0a*/);
    assert_post_action(((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0x147d);
  }
  if(param_2 == 0 || *param_2 == 0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"params && params->notify") /*=0xf4d35*/,((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0x147e);
    printk(((unsigned long)"\tinvalid parameters\n\n") /*=0xf4a0a*/);
    assert_post_action(((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0x147e);
  }
  if((short)param_2[4] == 0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"params->value") /*=0xf4d4e*/,((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0x147f);
    printk(((unsigned long)"\tinvalid parameters\n\n") /*=0xf4a0a*/);
    assert_post_action(((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0x147f);
  }
  if(*(short*)((int)param_2 + 0xe) == 0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"params->ccc_handle") /*=0xf4d5c*/,((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0x1485);
    printk(((unsigned long)"\tinvalid parameters\n\n") /*=0xf4a0a*/);
    assert_post_action(((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0x1485);
  }
  if(*(char*)(param_1 + 0xd) != 7) return -0x80;
  unsigned char *puVar2 = (unsigned char*)gatt_find_conn_in_known_table();
  if(puVar2 == 0){
    puVar2 = (unsigned char*)gatt_find_conn_in_known_table();
    if(puVar2 == 0) return -0xc;
    bt_addr_le_copy_828da(puVar2 + 1, param_1 + 0x90);
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
