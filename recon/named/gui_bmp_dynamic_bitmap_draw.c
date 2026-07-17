/* readable reconstruction; identity: FUN_0004334c @ 0x0004334c
 * public-name: gui_bmp_dynamic_bitmap_draw
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   atomic_get_3_0                           <= FUN_000431a8 @ 0x000431a8
 *   gui_bmp_dynamic_bitmap_draw              <= FUN_0004334c @ 0x0004334c
 *   resource_manger_get                      <= FUN_0004588c @ 0x0004588c
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   fb_blit_rows_copy                        <= FUN_0007d53a @ 0x0007d53a
 * address symbols (name @ address):
 *   rodata_aa8eb                             @ 0x000aa8eb
 *   rodata_aade4                             @ 0x000aade4
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_gui_active_canvas                      @ 0x2000a034
 *   g_gui_dynbmp_cycle_count                 @ 0x2000f6fe
 *   g_gui_dynbmp_frame_index                 @ 0x2000f700
 *   g_gui_dynbmp_frame_limit                 @ 0x2000f702
 */
/* Reconstructed FUN_0004334c @ 0x4334c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned,...);
extern int get_device_info(void);
extern void debug_print(unsigned,...);
extern unsigned atomic_get_3_0(void);
extern int resource_manger_get(int,unsigned,int*,int*,int*,unsigned char*);
extern void clean_fb_data(unsigned,int,int,int,int,int);
extern void reflash_fb_data_to_lcd(unsigned,unsigned,int,int,int,int);
extern void fb_blit_rows_copy(unsigned,int,int,int,int,int);

unsigned gui_bmp_dynamic_bitmap_draw(unsigned param_1,int param_2,int param_3,int p4,int p5,int p6,unsigned char in_stack8){
  struct __attribute__((packed, aligned(4))) {
    unsigned char reserved[3];
    unsigned char depth;
    int width;
    int height;
    int bitmap[2];
    unsigned char tail_padding[4];
  } local;
  local.width = 0;
  local.height = 0;
  local.bitmap[0] = 0;
  int iVar5 = resource_manger_get(5, param_1, &local.width, &local.height,
                           local.bitmap, &local.depth);
  if(iVar5 < 0){
    if(*(volatile int*)0x2000230cUL > 1){
      if(*(volatile int*)0x20007554UL == 0)
        DEBUG_PRINT(0x000aa8eb, 0x000aade4);
      else
        debug_print(0x000aa8eb, 0x000aade4);
    }
    return 0xffffffff;
  }
  *(volatile unsigned short*)0x2000f702UL = (unsigned short)local.depth;
  unsigned uVar7 = atomic_get_3_0();
  unsigned pv4 = *(volatile unsigned*)0x2000a034UL;
  if((uVar7 & 2) != 0){
    clean_fb_data(pv4, 0, param_2, param_3,
                 local.width + param_2, local.height + param_3);
  }
  unsigned short us = *(volatile unsigned short*)0x2000f700UL;
  fb_blit_rows_copy(pv4,
               local.height * ((int)(local.width * (unsigned)us) / 2) + local.bitmap[0],
               local.width / 2, local.height, param_2, param_3);
  int iVar = atomic_get_3_0();
  if((int)(iVar << 0x1e) < 0){
    int t = get_device_info();
    unsigned uv6 = *(volatile unsigned*)(t + 0xeb4);
    t = get_device_info();
    reflash_fb_data_to_lcd(uv6, *(volatile unsigned*)(t + 0xeb8), param_2, param_3,
                 local.width + param_2, local.height + param_3);
  }
  unsigned short uVar1 = *(volatile unsigned short*)0x2000f702UL;
  if(((int)(unsigned)*(volatile unsigned short*)0x2000f700UL < (int)(unsigned short)(uVar1 - 1))
     || (in_stack8 == 0)
     || ((int)(unsigned)*(volatile unsigned short*)0x2000f6feUL < (int)(in_stack8 - 1))){
    *(volatile unsigned short*)0x2000f700UL = *(volatile unsigned short*)0x2000f700UL + 1;
  }
  if((unsigned)uVar1 <= (unsigned)*(volatile unsigned short*)0x2000f700UL){
    *(volatile unsigned short*)0x2000f700UL = 0;
    *(volatile unsigned short*)0x2000f6feUL = *(volatile unsigned short*)0x2000f6feUL + 1;
  }
  return 0;
}
