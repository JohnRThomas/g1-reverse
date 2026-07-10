/* Reconstructed on_triple_click @ 0x289e4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t);
extern void FUN_00019c70(void);
extern void FUN_00028964(void);
extern void FUN_000289b0(void);
void on_triple_click(void){
  if(*(volatile uint32_t*)0x20007554UL==0) DEBUG_PRINT(0xa0ae5);
  else FUN_00019c70();
  if(*(volatile uint8_t*)0x20018d8bUL==0) FUN_00028964();
  else FUN_000289b0();
}

