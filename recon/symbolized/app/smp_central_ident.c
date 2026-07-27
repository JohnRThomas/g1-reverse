#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005e080 @ 0x0005e080
 * public-name: smp_central_ident
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_addr_le_str                           <= FUN_00052cdc @ 0x00052cdc
 *   smp_pairing_complete                     <= FUN_0005daf0 @ 0x0005daf0
 *   smp_central_ident                        <= FUN_0005e080 @ 0x0005e080
 *   bt_keys_get_type                         <= FUN_0005e9d0 @ 0x0005e9d0
 *   atomic_test_bit                          <= FUN_00082ff6 @ 0x00082ff6
 *   smp_log_message                          <= FUN_00083074 @ 0x00083074
 *   atomic_set_bit                           <= FUN_00083090 @ 0x00083090
 * address symbols (name @ address):
 *   rodata_88180                             @ 0x00088180
 *   rodata_f4e60                             @ 0x000f4e60
 */
/* Reconstructed FUN_0005e080 @ 0x5e080  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int atomic_test_bit(int,int);
extern int bt_keys_get_type(int,int,int,int);
extern unsigned int bt_addr_le_str(const void *);
extern void smp_log_message(uint32_t,int,void*);
extern void atomic_set_bit(int,uint32_t);
extern void smp_pairing_complete(int);

uint32_t smp_central_ident(int param_1, int param_2){
  uint8_t bVar1;
  int iVar2, iVar5, iVar6;
  uint32_t uVar3;
  uint16_t *puVar4;
  volatile uint32_t local_28, local_24, uStack_20;
  volatile uint16_t local_1c;
  iVar6 = *(int*)(param_1+0xf0);
  iVar2 = atomic_test_bit(param_1+4, 0xd);
  if (iVar2 != 0){
    iVar5 = iVar6 + 0x90;
    puVar4 = *(uint16_t**)(param_2+0xc);
    iVar2 = bt_keys_get_type(4, *(uint8_t*)(iVar6+8), iVar5, param_2);
    if (iVar2 == 0){
      uStack_20 = bt_addr_le_str(iVar5);
      local_24 = ((unsigned long)&rodata_f4e60) /*=0xf4e60*/;
      local_1c = 0x200;
      local_28 = 0x1000003;
      smp_log_message(((unsigned long)&rodata_88180) /*=0x88180*/, 0x1c40, (void*)&local_28);
      return 8;
    }
    *(uint16_t*)(iVar2+0x18) = *puVar4;
    *(uint32_t*)(iVar2+0x10) = *(uint32_t*)((char*)puVar4+2);
    *(uint32_t*)(iVar2+0x14) = *(uint32_t*)((char*)puVar4+6);
  }
  bVar1 = *(uint8_t*)(param_1+0xe9);
  *(uint8_t*)(param_1+0xe9) = bVar1 & 0xfe;
  if ((int)((uint32_t)bVar1 << 0x1e) < 0){
    uVar3 = 8;
  } else {
    if ((int)((uint32_t)bVar1 << 0x1d) >= 0) goto LAB;
    uVar3 = 10;
  }
  atomic_set_bit(param_1, uVar3);
LAB:
  if (*(short*)(param_1+0xe8) == 0){
    smp_pairing_complete(param_1);
  }
  return 0;
}
