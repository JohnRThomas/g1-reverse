/* Reconstructed display_close_screen @ 0x49858  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(int,...);
extern int FUN_000167a8(void);
extern int FUN_00019c70(void);
extern int FUN_00036024(void);
extern int FUN_000497b0(void*,int);
extern int FUN_000745c8(void);
extern int FUN_00086c78(int,int,int);
int display_close_screen(int param_1, uint32_t param_2){
  uint8_t loc[4];
  *(volatile uint16_t*)(loc) = 1;
  loc[1] = (uint8_t)param_1;
  if(param_1 != 0){
    if(*(volatile int*)0x2000230cUL > 0){
      if(*(volatile int*)0x20007554UL == 0){
        DEBUG_PRINT(0x000f006d, 0x000f0177, param_1, 0, param_1);
      } else {
        FUN_00019c70();
      }
    }
    if(param_1 == 4){
      FUN_00036024();
    }
    FUN_000497b0(loc, 2);
    FUN_000745c8();
    int iVar1 = FUN_000167a8();
    FUN_00086c78(iVar1 + 0xef, 0, 0x5dc);
  }
  return 0;
}

