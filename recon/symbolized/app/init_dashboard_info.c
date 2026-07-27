#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00036ed8 @ 0x00036ed8
 * public-name: init_dashboard_info
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   uarte_nrfx_irq_rx_ready                  <= FUN_000165b4 @ 0x000165b4
 *   init_dashboard_startup_mode_info_defaults <= FUN_00016658 @ 0x00016658
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   getQuickNoteDataFromFlash                <= FUN_00024534 @ 0x00024534
 *   record_dashboard_startup_snapshot        <= FUN_0004a4b4 @ 0x0004a4b4
 * address symbols (name @ address):
 *   rodata_a8eee                             @ 0x000a8eee   [INLINED -- G6 literal batch]
 *   rodata_a8f19                             @ 0x000a8f19   [INLINED -- G6 literal batch]
 *   rodata_a8f46                             @ 0x000a8f46   [INLINED -- G6 literal batch]
 *   rodata_a8fb7                             @ 0x000a8fb7   [INLINED -- G6 literal batch]
 *   rodata_a95f9                             @ 0x000a95f9   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed init_dashboard_info @ 0x36ed8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#include "../../headers/g1_log.h"
extern int uarte_nrfx_irq_rx_ready(void);
extern void init_dashboard_startup_mode_info_defaults(void);
extern int get_device_info(void);
extern int getQuickNoteDataFromFlash(int,int,int,int,int);
extern void record_dashboard_startup_snapshot(unsigned int, unsigned int);
#define VB(a) (*(volatile unsigned char*)(a))
#define VI(a) (*(volatile int*)(a))

void init_dashboard_info(void){
  volatile int *p40 = (volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/;
  volatile int *p44 = (volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
  int iVar3, iVar4, iVar5, iVar7;
  iVar3 = uarte_nrfx_irq_rx_ready();
  if (iVar3 == 0) {
    if (2 < *p40) {
      if (*p44 == 0) { log_message(((unsigned long)"%s(): system startup ,NCS memory is vaild\n") /*=0xa8eee*/, ((unsigned long)"init_dashboard_info") /*=0xa95f9*/); }
      else { debug_print(((unsigned long)"%s(): system startup ,NCS memory is vaild\n") /*=0xa8eee*/, ((unsigned long)"init_dashboard_info") /*=0xa95f9*/); }
    }
    init_dashboard_startup_mode_info_defaults();
  } else {
    if (2 < *p40) {
      if (*p44 == 0) { log_message(((unsigned long)"%s(): system startup ,NCS memory is invaild\n") /*=0xa8f19*/, ((unsigned long)"init_dashboard_info") /*=0xa95f9*/); }
      else { debug_print(((unsigned long)"%s(): system startup ,NCS memory is invaild\n") /*=0xa8f19*/, ((unsigned long)"init_dashboard_info") /*=0xa95f9*/); }
    }
    iVar3 = get_device_info();
    { unsigned int pb = VI(iVar3 + 0xfec);
      VB(pb) = 0x80; VB(pb+2) = 0x92; VB(pb+1) = 0; VB(pb+3) = 0x65; }
    iVar3 = get_device_info();
    iVar3 = VI(iVar3 + 0xfec);
    VB(iVar3+6)=0; VB(iVar3+7)=0xf4; VB(iVar3+8)=0x51; VB(iVar3+9)=0xc2;
    VB(iVar3+10)=0x8c; VB(iVar3+0xc)=0; VB(iVar3+0xb)=1; VB(iVar3+0xd)=0;
    iVar3 = get_device_info();
    { int q = VI(iVar3+0xfec); record_dashboard_startup_snapshot(VI(q+6), VI(q+10)); }
  }
  iVar7 = 4;
  iVar3 = 0;
  do {
    iVar4 = get_device_info();
    iVar5 = VI(iVar4 + 0x1020);
    iVar4 = get_device_info();
    iVar4 = getQuickNoteDataFromFlash(iVar3, iVar5+iVar7, 0x29, iVar7+0x29+VI(iVar4+0x1020), 0x119);
    if (iVar4 == -1) {
      iVar4 = get_device_info();
      VB(iVar3*0x143 + VI(iVar4+0x1020) + 3) = 0;
      if (2 < *p40) {
        if (*p44 == 0) log_message(((unsigned long)"%s(): QuickNote %d is invaild,don't export\n") /*=0xa8f46*/, ((unsigned long)"init_dashboard_info") /*=0xa95f9*/, iVar3);
        else debug_print(((unsigned long)"%s(): QuickNote %d is invaild,don't export\n") /*=0xa8f46*/, ((unsigned long)"init_dashboard_info") /*=0xa95f9*/, iVar3);
      }
    } else if (iVar4 == 0) {
      iVar4 = get_device_info();
      VB(iVar3*0x143 + VI(iVar4+0x1020) + 3) = 1;
      if (2 < *p40) {
        if (*p44 == 0) log_message(0x000a8f72, ((unsigned long)"init_dashboard_info") /*=0xa95f9*/, iVar3);
        else debug_print(0x000a8f72, ((unsigned long)"init_dashboard_info") /*=0xa95f9*/, iVar3);
      }
    } else if (0 < *p40) {
      if (*p44 == 0) log_message(((unsigned long)"%s(): !!!! getQuickNoteDataFromFlash return unknown value.\n") /*=0xa8fb7*/, ((unsigned long)"init_dashboard_info") /*=0xa95f9*/);
      else debug_print(((unsigned long)"%s(): !!!! getQuickNoteDataFromFlash return unknown value.\n") /*=0xa8fb7*/, ((unsigned long)"init_dashboard_info") /*=0xa95f9*/);
    }
    iVar3++;
    iVar7 += 0x143;
    if (iVar3 == 4) return;
  } while (1);
}
