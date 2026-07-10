/* named: gui_bmp_dynamic_bitmap_draw */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x2000a034  g_gui_active_canvas          
//   0x2000f6fe  g_gui_dynbmp_cycle_count     
//   0x2000f700  g_gui_dynbmp_frame_index     
//   0x2000f702  g_gui_dynbmp_frame_limit     
*/
/* Reconstructed gui_bmp_dynamic_bitmap_draw @ 0x4334c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned,...);
extern int get_device_info(void);
extern void debug_print(void);
extern unsigned atomic_get_3_0(void);
extern int resource_manger_get(int,unsigned,int*,int*,int*,unsigned char*);
extern void clean_fb_data(unsigned,int,int,int,int,int);
extern void reflash_fb_data_to_lcd(unsigned,unsigned,int,int,int,int);
extern void fb_blit_rows_copy(unsigned,int,int,int,int,int);

unsigned gui_bmp_dynamic_bitmap_draw(unsigned param_1,int param_2,int param_3,int p4,int p5,int p6,unsigned char in_stack8){
  int local_2c = 0, local_28 = 0;
  int local_24[2]; local_24[0] = 0;
  unsigned char local_2d;
  int iVar5 = resource_manger_get(5, param_1, &local_2c, &local_28, local_24, &local_2d);
  if(iVar5 < 0){
    if(*(volatile int*)0x2000230cUL > 1){
      if(*(volatile int*)0x20007554UL == 0)
        DEBUG_PRINT(0x000aa8eb, 0x000aade4);
      else
        debug_print();
    }
    return 0xffffffff;
  }
  *(volatile unsigned short*)0x2000f702UL = (unsigned short)local_2d;
  unsigned uVar7 = atomic_get_3_0();
  unsigned pv4 = *(volatile unsigned*)0x2000a034UL;
  if((uVar7 & 2) != 0){
    clean_fb_data(pv4, 0, param_2, param_3, local_2c + param_2, local_28 + param_3);
  }
  unsigned short us = *(volatile unsigned short*)0x2000f700UL;
  fb_blit_rows_copy(pv4,
               local_28 * ((int)(local_2c * (unsigned)us) / 2) + local_24[0],
               local_2c / 2, local_28, param_2, param_3);
  int iVar = atomic_get_3_0();
  if((int)(iVar << 0x1e) < 0){
    int t = get_device_info();
    unsigned uv6 = *(volatile unsigned*)(t + 0xeb4);
    t = get_device_info();
    reflash_fb_data_to_lcd(uv6, *(volatile unsigned*)(t + 0xeb8), param_2, param_3,
                 local_2c + param_2, local_28 + param_3);
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

