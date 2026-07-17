/* readable reconstruction; identity: FUN_0004f0ec @ 0x0004f0ec
 * public-name: FUN_0004f0ec
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   atomic_clear_bit                         <= FUN_0007f5d8 @ 0x0007f5d8
 *   atomic_test_and_set_bit                  <= FUN_0007f612 @ 0x0007f612
 * address symbols (name @ address):
 *   rodata_7f5c5                             @ 0x0007f5c5
 *   rodata_880e8                             @ 0x000880e8
 *   rodata_f15cc                             @ 0x000f15cc
 */
/* Reconstructed FUN_0004f0ec @ 0x4f0ec  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int atomic_test_and_set_bit(void*, int);
extern int FUN_0005c3c4(uint32_t, void*);
extern void atomic_clear_bit(void*, int);
extern void FUN_0004d944(uint32_t, int, void*, int);

int FUN_0004f0ec(volatile uint32_t *param_1, int param_2, uint32_t param_3, uint32_t param_4){
  int iVar2;
  uint32_t uVar1;
  volatile uint32_t local_30, local_2c, uStack_20;
  volatile int iStack_28;
  if (param_1 == 0 || param_2 == 0){
    iVar2 = -0x16;
  } else {
    uStack_20 = param_4;
    iVar2 = atomic_test_and_set_bit((void*)(param_1+1), 1);
    uVar1 = 0x7f5c5;
    if (iVar2 == 0){
      *(volatile uint16_t*)(param_1 + 0x216) = 1;
      param_1[0x212] = uVar1;
      *(volatile uint16_t*)(param_1 + 0x215) = *(volatile uint16_t*)((char*)param_1 + 0xe);
      *(volatile uint16_t*)((char*)param_1 + 0x856) = *(volatile uint16_t*)(param_1 + 4);
      param_1[0x217] |= 1;
      param_1[0x219] = param_2;
      iVar2 = FUN_0005c3c4(param_1[0], (void*)(param_1 + 0x212));
      if (iVar2 != 0){
        atomic_clear_bit((void*)(param_1+1), 1);
        local_2c = 0xf15cc;
        local_30 = 3;
        iStack_28 = iVar2;
        FUN_0004d944(0x880e8, 0x1840, (void*)&local_30, 0);
      }
    } else {
      iVar2 = -0x78;
    }
  }
  return iVar2;
}
