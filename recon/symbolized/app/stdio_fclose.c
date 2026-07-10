#include "g1_app_symbols.h"
/* named: stdio_fclose */
/* globals referenced:
//   0x20002d20  g_libc_heap_ctrl             
*/
/* Reconstructed stdio_fclose @ 0x77d54  (parity: 300/300 trials, PROVEN) */
extern void stdio_streams_init(int);
extern void smakebuf_r(void*,void*);
extern void heap_free_core(void*);
int stdio_fclose(int *param_1, int *param_2){
  int iVar4 = *(volatile int*)((uintptr_t)&g_libc_heap_ctrl) /*=0x20002d20*/;
  if (iVar4 != 0 && *(int*)(iVar4+0x18) == 0) stdio_streams_init(iVar4);
  if (param_2 == (int*)((uintptr_t)&rodata_9871c) /*=0x9871c*/) param_2 = *(int**)(iVar4+4);
  else if (param_2 == (int*)((uintptr_t)&rodata_986fc) /*=0x986fc*/) param_2 = *(int**)(iVar4+8);
  else if (param_2 == (int*)((uintptr_t)&rodata_986dc) /*=0x986dc*/) param_2 = *(int**)(iVar4+0xc);
  volatile unsigned short *P0c = (volatile unsigned short*)((char*)param_2 + 0xc);
  volatile int *pv = (volatile int*)param_2;
  int s = *(short*)((char*)param_2 + 0xc);
  if ((s & 8) == 0){
    if ((s & 0x10) == 0){
      *(volatile int*)param_1 = 9;
      *P0c = (unsigned short)(s | 0x40);
      return -1;
    }
    if (s & 4){
      if (param_2[0xd] != 0){
        if ((int*)param_2[0xd] != param_2 + 0x11) heap_free_core(param_1);
        pv[0xd] = 0;
      }
      *P0c = *P0c & ((uintptr_t)&tbl_ffc8) /*=0xffdb*/;
      pv[1] = 0;
      pv[0] = param_2[4];
    }
    *P0c = *P0c | 8;
  }
  if (param_2[4] == 0 && (*P0c & 0x280) != 0x200)
    smakebuf_r(param_1, param_2);
  {
    int s2 = *(short*)((char*)param_2+0xc);
    if (s2 & 1){
      pv[2] = 0;
      pv[6] = -param_2[5];
    } else {
      pv[2] = (s2 & 2) ? 0 : param_2[5];
    }
    if (param_2[4] != 0) return 0;
    if ((s2 & 0x80) == 0) return 0;
    *P0c = (unsigned short)(s2 | 0x40);
    return -1;
  }
}

