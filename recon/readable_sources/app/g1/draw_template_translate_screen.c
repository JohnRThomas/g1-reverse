#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0003fd44 @ 0x0003fd44
 * public-name: draw_template_translate_screen
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   gui_set_active_canvas                    <= FUN_000431b4 @ 0x000431b4
 *   gui_bmp_bitmap_draw                      <= FUN_00043484 @ 0x00043484
 *   gui_utf_draw                             <= FUN_00043e90 @ 0x00043e90
 *   gui_clock_draw                           <= FUN_000442bc @ 0x000442bc
 *   snprintf                                 <= FUN_00077914 @ 0x00077914
 *   get_timestamp                            <= FUN_0007d224 @ 0x0007d224
 *   device_info_text_width_get               <= FUN_0007d3ee @ 0x0007d3ee
 *   device_info_text_height_get_clamped      <= FUN_0007d446 @ 0x0007d446
 * address symbols (name @ address):
 *   rodata_aa487                             @ 0x000aa487
 *   rodata_aa4ea                             @ 0x000aa4ea
 *   rodata_aa5ab                             @ 0x000aa5ab
 *   g_log_level                              @ 0x2000230c
 *   g_translate_lang_string_table            @ 0x200024f4
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed draw_template_translate_screen @ 0x3fd44  (parity: 300/300 trials, PROVEN) */
extern void log_message(int,...);
extern int  get_device_info(void);
extern void debug_print(int,int,...);
extern void gui_set_active_canvas(int);
extern void gui_bmp_bitmap_draw(int,int,int,int,int,int);
extern void gui_utf_draw(int,int,int,int,int,int,int,int,int,int,int,int);
extern void gui_clock_draw(int,int,int,int,int,int,int);
extern void snprintf(int*,int,int,int,int);
extern int  get_timestamp(void);
extern int  device_info_text_width_get(void);
extern int  device_info_text_height_get_clamped(void);
#define VI(a) (*(volatile int*)(a))

int draw_template_translate_screen(int param_1){
  volatile int *lvl=(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/;
  volatile int *g8=(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
  int iVar1,iVar4,iVar5,iVar6,iVar7,uVar2,uVar3;
  unsigned int uVar8,uVar9;
  int local_24[3];
  iVar1 = get_device_info();
  gui_set_active_canvas(param_1 + 0x24);
  uVar8 = *(volatile unsigned char*)(iVar1+0xf0);
  uVar9 = (unsigned int)(*(volatile unsigned char*)(iVar1+0xef) - 1);
  if (uVar8 < 9 && (uVar9 & 0xff) < 8 && uVar8 != 0) {
    local_24[0]=0; local_24[1]=0; local_24[2]=0;
    snprintf(local_24, 10, ((unsigned long)&rodata_aa4ea) /*=0xaa4ea*/,
                 VI(((unsigned long)&g_translate_lang_string_table) /*=0x200024f4*/ + (uVar8-1)*4), VI(((unsigned long)&g_translate_lang_string_table) /*=0x200024f4*/ + uVar9*4));
    uVar2 = device_info_text_width_get();
    iVar4 = device_info_text_height_get_clamped();
    iVar5 = device_info_text_width_get();
    iVar6 = device_info_text_height_get_clamped();
    gui_utf_draw(0,(int)local_24,3,uVar2,iVar4+0x6e,iVar5+0x50,iVar6+0x89,1,0,0,0,0);
  } else if (0 < *lvl) {
    if (*g8==0) log_message(((unsigned long)&rodata_aa487) /*=0xaa487*/,((unsigned long)&rodata_aa5ab) /*=0xaa5ab*/,uVar8,*(volatile unsigned char*)(iVar1+0xef));
    else debug_print(((unsigned long)&rodata_aa487) /*=0xaa487*/,((unsigned long)&rodata_aa5ab) /*=0xaa5ab*/,uVar8,
                      *(volatile unsigned char*)(iVar1+0xef));
  }
  uVar2 = get_timestamp();
  uVar3 = device_info_text_width_get();
  iVar4 = device_info_text_height_get_clamped();
  iVar5 = device_info_text_width_get();
  iVar6 = device_info_text_height_get_clamped();
  gui_clock_draw(uVar2,uVar3,iVar4+2,iVar5+0x50,iVar6+0x1d,3,1);
  if (*(volatile char*)(iVar1+0xf1) == 1) {
    uVar2 = device_info_text_width_get();
    iVar4 = device_info_text_height_get_clamped();
    uVar3 = 0x1b;
  } else {
    uVar2 = device_info_text_width_get();
    iVar4 = device_info_text_height_get_clamped();
    uVar3 = 0x33;
  }
  gui_bmp_bitmap_draw(uVar3,uVar2,iVar4+0x36,0,0,0);
  iVar4 = device_info_text_width_get();
  iVar5 = device_info_text_height_get_clamped();
  iVar6 = device_info_text_width_get();
  iVar7 = device_info_text_height_get_clamped();
  gui_utf_draw(0,iVar1+0xf5,0,iVar4+0x58,iVar5+1,iVar6+0x240,iVar7+0x88,5,0,0,0,0);
  return 0;
}
