#include "g1_app_symbols.h"
/* named: uart_callback */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed uart_callback @ 0x33384  (parity: 295/300 trials, PROVEN) */
extern void DEBUG_PRINT(int,...);
extern void EPILOGUE(void);
extern void debug_print(void);
extern int  k_mem_slab_alloc(int,void*,int,int);
extern void k_mem_slab_free(int,int);
extern void assert_post_action(int,int);
extern void printk(int,int,int,int);
extern void memcpy(int,...);
extern void memset_bytes(void*,int,int);
#define VI(a) (*(volatile int*)(a))
#define VB(a) (*(volatile unsigned char*)(a))

void uart_callback(int param_1,unsigned char *param_2,unsigned int param_3){
  volatile int *lvl=(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/, *g8=(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
  int iVar2; unsigned int uVar5,uVar7; char cVar1; int iVar6; void *local_1c=param_2;
  switch (*param_2) {
  case 0:
    if (2 < *lvl) { if(*g8==0) DEBUG_PRINT("%s(): Tx sent %d bytes\n" /*=0xa797b*/,"uart_callback" /*=0xa7b56*/,VI((int)param_2+8),0,param_1); else debug_print(); }
    for (uVar5=0; uVar5 < (unsigned int)VI((int)param_2+8); uVar5++)
      DEBUG_PRINT("%02x " /*=0xa7993*/, VB(VI((int)param_2+4)+uVar5));
    break;
  case 1:
    if (*lvl < 1) { EPILOGUE(); return; }
    if (*g8 != 0) { debug_print(); return; }
    DEBUG_PRINT("%s(): Tx aborted\n" /*=0xa7999*/,"uart_callback" /*=0xa7b56*/); return;
  case 2:
    uVar5 = VI((int)param_2+8);
    for (uVar7 = uVar5 & ((uintptr_t)&tbl_ffc8) /*=0xffff*/; (uVar7 & ((uintptr_t)&tbl_ffc8) /*=0xffff*/) < 0xf8; uVar7++) {
      iVar2 = VI((int)param_2+4);
      param_3 = VB(iVar2+uVar7);
      if (param_3==0x5a && VB(iVar2+uVar7+1)==0xa5 && VB(iVar2+uVar7+2)==0x7f) {
        param_3 = (unsigned char)(VB(iVar2+uVar7+3)+5);
        if ((int)param_3 <= (int)(0x100 - uVar7)) {
          cVar1 = 0;
          for (iVar6=0; iVar6 < (int)(param_3-1); iVar6++) cVar1 = (char)(cVar1 + VB(iVar2+uVar7+iVar6));
          if ((char)VB(iVar2+param_3+uVar7-1) == cVar1) {
            *(volatile unsigned char*)((uintptr_t)&g_uart_rx_frame_len) /*=0x2001a128*/ = (unsigned char)param_3;
            memcpy((g_uart_rx_frame_buf) /*=0x2001a129*/);
            memset_bytes((void*)VI((int)param_2+4),0,0x100);
            return;
          }
        }
      }
    }
    DEBUG_PRINT("recv data %d bytes:" /*=0xa79ab*/, VI((int)param_2+0xc), param_3, uVar7 & ((uintptr_t)&tbl_ffc8) /*=0xffff*/, param_1);
    for (uVar7=0; uVar7 < (unsigned int)VI((int)param_2+0xc); uVar7++)
      DEBUG_PRINT("%02x " /*=0xa7993*/, VB(VI((int)param_2+4)+uVar5+uVar7));
    break;
  case 3:
    DEBUG_PRINT("*************alloc new rx buf*************\n" /*=0xa79bf*/);
    iVar2 = k_mem_slab_alloc(((uintptr_t)&g_uart_rx_mem_slab) /*=0x200037b8*/, &local_1c, 0, 0);
    if (iVar2 != 0) { printk(0,0,0,0); printk(0,0,0,0); assert_post_action(0,0x51); }
    for (;;) {
      iVar2 = ((int(*)(int,int,int))(VI(VI((int)param_3+8)+0x10)))((int)param_3,(int)local_1c,0x100);
      if (iVar2 == 0) return;
      printk(0,0,0,0); printk(0,0,0,0); assert_post_action(0,0x54);
    }
  case 4:
    DEBUG_PRINT("****************************UART_RX_BUF_RELEASED***************************************\n" /*=0xa7a52*/);
    k_mem_slab_free(((uintptr_t)&g_uart_rx_mem_slab) /*=0x200037b8*/, VI((int)param_2+4));
    return;
  default:
    EPILOGUE(); return;
  }
  DEBUG_PRINT(((uintptr_t)&rodata_f5400) /*=0xf5400*/);
}

