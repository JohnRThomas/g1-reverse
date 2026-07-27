#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   local_2c         => struct g1_layout_bitmap_merge_locals__stack_1016        [stack_1016; G1-original]
 * Raw function identity: 0x00043bd8.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00043bd8 @ 0x00043bd8
 * public-name: gui_bitmps_merge_draw
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   atomic_get_3_0                           <= FUN_000431a8 @ 0x000431a8
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 * address symbols (name @ address):
 *   rodata_aa96d                             @ 0x000aa96d
 *   rodata_aacc8                             @ 0x000aacc8
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_gui_active_canvas                      @ 0x2000a034
 */
/* Reconstructed gui_bitmps_merge_draw @ 0x43bd8  (parity: 300/300 trials, PROVEN) */
extern void log_message(unsigned long, ...);
extern int  get_device_info(void);
extern void debug_print(unsigned long, ...);
extern unsigned long long atomic_get_3_0(void);
extern void clean_fb_data(int,int,int,int,int,int);
extern void reflash_fb_data_to_lcd(int,int,int,int,int,int);
#define VI(a) (*(volatile int*)(a))
#define VB(a) (*(volatile unsigned char*)(a))

int gui_bitmps_merge_draw(unsigned int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 unsigned char param_7,unsigned char param_8){
  volatile int *lvl=(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/, *g8=(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
  int iVar4,iVar6,iVar7,iVar11; unsigned int uVar3,uVar5,uVar8,uVar12; int uVar9;
  unsigned char bVar1,bVar2; int pbVar10, local_5c; unsigned int local_2c[2];
  unsigned long long uVar13;
  if ((param_3 < (int)param_1) || (param_4 < param_2) || (0xf < (param_7 | param_8))) {
    if (*lvl < 2) return -1;
    iVar4 = *g8; uVar9 = ((unsigned long)&rodata_aa96d) /*=0xaa96d*/;
  } else {
    if ((param_1 & 1) == 0) {
      iVar4 = param_3;
      uVar13 = atomic_get_3_0();
      if ((int)((unsigned int)uVar13 << 0x1e) < 0)
        clean_fb_data(VI(((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/),(int)(param_1&1),(int)param_1,(int)(uVar13>>0x20),iVar4,param_4);
      iVar11 = 0;
      uVar5 = (unsigned int)((int)(param_3-(int)param_1) >> 3);
      iVar6 = VI(((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/);
      for (iVar4 = 0; iVar4 < param_4 - param_2; iVar4++) {
        pbVar10 = param_6 + iVar11;
        local_5c = param_5 + iVar11;
        for (iVar7 = 0; iVar7 < (int)uVar5; iVar7++) {
          bVar1 = VB(local_5c); bVar2 = VB(pbVar10);
          uVar3 = 0; local_2c[0] = 0; uVar8 = 0;
          do {
            if ((((int)(unsigned int)bVar1 >> (uVar8 & 0xff)) & 1) != 0) {
              if ((int)(uVar8 << 0x1f) < 0) uVar3 |= param_7;
              else uVar3 |= (unsigned int)((param_7 & 0xf) << 4);
            }
            if ((((int)(unsigned int)bVar2 >> (uVar8 & 0xff)) & 1) != 0) {
              if ((int)(uVar8 << 0x1f) < 0) uVar3 |= param_8;
              else uVar3 |= (unsigned int)((param_8 & 0xf) << 4);
            }
            uVar12 = uVar8 + 1;
            if ((uVar12 & 1) == 0) { *((char*)local_2c + ((int)uVar8 >> 1)) = (char)uVar3; uVar3 = 0; }
            uVar8 = uVar12;
          } while (uVar12 != 8);
          *(volatile int*)(VI(iVar6 + param_2*4 + iVar4*4) + iVar7*4 + (int)param_1/2) = local_2c[0];
          pbVar10++; local_5c++;
        }
        iVar11 += (int)(uVar5 & ~((unsigned int)((int)(param_3-(int)param_1) >> 0x1f)));
      }
      iVar4 = (int)atomic_get_3_0();
      if ((int)((unsigned int)iVar4 << 0x1e) < 0) {
        iVar4 = get_device_info(); uVar9 = VI(iVar4+0xeb4);
        iVar4 = get_device_info(); reflash_fb_data_to_lcd(uVar9, VI(iVar4+0xeb8), (int)param_1, param_2, param_3, param_4);
        return 0;
      }
      return 0;
    }
    if (*lvl < 2) return -1;
    iVar4 = *g8; uVar9 = 0xaa9a3;
  }
  if (iVar4 == 0) log_message(uVar9, ((unsigned long)&rodata_aacc8) /*=0xaacc8*/); else debug_print(uVar9, ((unsigned long)&rodata_aacc8) /*=0xaacc8*/);
  return -1;
}
