#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00033384 @ 0x00033384
 * public-name: uart_callback
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_mem_slab_alloc                         <= FUN_00071c20 @ 0x00071c20
 *   k_mem_slab_free                          <= FUN_00071cf4 @ 0x00071cf4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_a797b                             @ 0x000a797b   [INLINED -- G6 literal batch]
 *   rodata_a7993                             @ 0x000a7993
 *   rodata_a7999                             @ 0x000a7999   [INLINED -- G6 literal batch]
 *   rodata_a79ab                             @ 0x000a79ab   [INLINED -- G6 literal batch]
 *   rodata_a79bf                             @ 0x000a79bf   [INLINED -- G6 literal batch]
 *   rodata_a79eb                             @ 0x000a79eb
 *   rodata_a7a10                             @ 0x000a7a10   [INLINED -- G6 literal batch]
 *   rodata_a7a19                             @ 0x000a7a19   [INLINED -- G6 literal batch]
 *   rodata_a7a33                             @ 0x000a7a33   [INLINED -- G6 literal batch]
 *   rodata_a7a52                             @ 0x000a7a52   [INLINED -- G6 literal batch]
 *   rodata_a7b56                             @ 0x000a7b56   [INLINED -- G6 literal batch]
 *   rodata_f5400                             @ 0x000f5400
 *   g_log_level                              @ 0x2000230c
 *   g_uart_rx_mem_slab                       @ 0x200037b8
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_uart_rx_frame_len                      @ 0x2001a128
 *   g_uart_rx_frame_buf                      @ 0x2001a129
 */
/* Reconstructed uart_callback @ 0x33384  (parity: 295/300 trials, PROVEN) */
extern void log_message(unsigned long, ...);
extern void debug_print(unsigned long, ...);
extern int  k_mem_slab_alloc(int,void*,int,int);
extern void k_mem_slab_free(int,int);
extern void assert_post_action(int,int);
extern void printk(unsigned long, ...);
extern void memcpy(int,...);
extern void memset_bytes(void*,int,int);
#define VI(a) (*(volatile int*)(a))
#define VB(a) (*(volatile unsigned char*)(a))

void uart_callback(int param_1,unsigned char *param_2,unsigned int param_3){
  volatile int *lvl=(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/, *g8=(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
  int iVar2; unsigned int uVar5,uVar7; char cVar1; int iVar6; void *local_1c=param_2;
  switch (*param_2) {
  case 0:
    if (2 < *lvl) { if(*g8==0) log_message(((unsigned long)"%s(): Tx sent %d bytes\n") /*=0xa797b*/,((unsigned long)"uart_callback") /*=0xa7b56*/,VI((int)param_2+8),0,param_1); else debug_print(((unsigned long)"%s(): Tx sent %d bytes\n") /*=0xa797b*/,((unsigned long)"uart_callback") /*=0xa7b56*/,VI((int)param_2+8),0,param_1); }
    for (uVar5=0; uVar5 < (unsigned int)VI((int)param_2+8); uVar5++)
      log_message(((unsigned long)&rodata_a7993) /*=0xa7993*/, VB(VI((int)param_2+4)+uVar5));
    break;
  case 1:
    if (*lvl < 1) return;
    if (*g8 != 0) { debug_print(((unsigned long)"%s(): Tx aborted\n") /*=0xa7999*/,((unsigned long)"uart_callback") /*=0xa7b56*/); return; }
    log_message(((unsigned long)"%s(): Tx aborted\n") /*=0xa7999*/,((unsigned long)"uart_callback") /*=0xa7b56*/); return;
  case 2:
    uVar5 = VI((int)param_2+8);
    for (uVar7 = uVar5 & 0xffff; (uVar7 & 0xffff) < 0xf8; uVar7++) {
      iVar2 = VI((int)param_2+4);
      param_3 = VB(iVar2+uVar7);
      if (param_3==0x5a && VB(iVar2+uVar7+1)==0xa5 && VB(iVar2+uVar7+2)==0x7f) {
        param_3 = (unsigned char)(VB(iVar2+uVar7+3)+5);
        if ((int)param_3 <= (int)(0x100 - uVar7)) {
          cVar1 = 0;
          for (iVar6=0; iVar6 < (int)(param_3-1); iVar6++) cVar1 = (char)(cVar1 + VB(iVar2+uVar7+iVar6));
          if ((char)VB(iVar2+param_3+uVar7-1) == cVar1) {
            *(volatile unsigned char*)((unsigned long)&g_uart_rx_frame_len) /*=0x2001a128*/ = (unsigned char)param_3;
            memcpy(((unsigned long)g_uart_rx_frame_buf) /*=0x2001a129*/, iVar2 + uVar7, param_3);
            memset_bytes((void*)VI((int)param_2+4),0,0x100);
            return;
          }
        }
      }
    }
    log_message(((unsigned long)"recv data %d bytes:") /*=0xa79ab*/, VI((int)param_2+0xc), param_3, uVar7 & 0xffff, param_1);
    for (uVar7=0; uVar7 < (unsigned int)VI((int)param_2+0xc); uVar7++)
      log_message(((unsigned long)&rodata_a7993) /*=0xa7993*/, VB(VI((int)param_2+4)+uVar5+uVar7));
    break;
  case 3:
    log_message(((unsigned long)"*************alloc new rx buf*************\n") /*=0xa79bf*/);
    iVar2 = k_mem_slab_alloc(((unsigned long)&g_uart_rx_mem_slab) /*=0x200037b8*/, &local_1c, 0, 0);
    if (iVar2 == 0) {
      iVar2 = ((int(*)(int,int,int))(VI(VI((int)param_3+8)+0x10)))((int)param_3,(int)local_1c,0x100);
      if (iVar2 == 0) return;
      printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"err == 0") /*=0xa7a10*/,((unsigned long)&rodata_a79eb) /*=0xa79eb*/,0x54);
      printk(((unsigned long)"\tFailed to provide new buffer\n") /*=0xa7a33*/);
      assert_post_action(((unsigned long)&rodata_a79eb) /*=0xa79eb*/,0x54);
    } else {
      printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"err == 0") /*=0xa7a10*/,((unsigned long)&rodata_a79eb) /*=0xa79eb*/,0x51);
      printk(((unsigned long)"\tFailed to allocate slab\n") /*=0xa7a19*/);
      assert_post_action(((unsigned long)&rodata_a79eb) /*=0xa79eb*/,0x51);
    }
  case 4:
    log_message(((unsigned long)"****************************UART_RX_BUF_RELEASED***************************************\n") /*=0xa7a52*/);
    k_mem_slab_free(((unsigned long)&g_uart_rx_mem_slab) /*=0x200037b8*/, VI((int)param_2+4));
    return;
  default:
    return;
  }
  log_message(((unsigned long)&rodata_f5400) /*=0xf5400*/);
}
