#include "g1_app_symbols.h"
/* named: stream_flash_init */
/* Reconstructed stream_flash_init @ 0x4e2b4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern unsigned FUN_0007f064(int);
extern void flash_page_foreach(int,int,void*);
extern void FUN_0004d944(int,int,void*,int);
unsigned stream_flash_init(int *param_1,int param_2,int param_3,unsigned param_4,unsigned param_5,int param_6,int param_7){
  unsigned uVar1; unsigned local_40; unsigned local_3c; int local_28; int local_24;
  if (((param_1 != 0) && (param_2 != 0)) && (param_3 != 0)) {
    local_3c = 0;
    local_40 = param_4;
    uVar1 = FUN_0007f064(param_2);
    if (param_4 == (param_4 / uVar1) * uVar1) {
      flash_page_foreach(param_2,((uintptr_t)&rodata_7f071) /*=0x7f071*/,&local_40);
      if (local_3c == 0) { return 0xfffffff2; }
      if (((unsigned)(param_5 + param_6) <= local_3c) &&
         (uVar1 = FUN_0007f064(param_2), param_5 == (param_5 / uVar1) * uVar1)) {
        *param_1 = param_3;
        param_1[1] = param_4;
        param_1[3] = param_2;
        param_1[4] = 0;
        param_1[2] = 0;
        param_1[5] = param_5;
        if (param_6 == 0) { param_6 = local_3c - param_5; }
        param_1[7] = param_7;
        param_1[6] = param_6;
        param_1[8] = -1;
        return 0;
      }
      local_24 = "Incorrect parameter" /*=0xf1105*/;
    } else { local_24 = "Buffer size is not aligned to minimal write-block-size" /*=0xf10ce*/; }
    local_28 = 2;
    FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x880d8*/,0x1040,&local_28,0);
  }
  return 0xfffffff2;
}

