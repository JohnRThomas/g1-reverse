/* named: update_demo_image_display */
/* globals referenced:
//   0x2001b810  g_display_page_index         
//   0x2001b811  g_display_page_dirty_flag    
*/
/* Reconstructed update_demo_image_display @ 0x36a18  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int get_device_info(void);
extern void get_demo_image_source(int);
extern void gui_screen_clear(void);
extern void reflash_fb_data_to_lcd(unsigned,unsigned,unsigned,unsigned,int,int);
extern unsigned FUN_00047a84(int,int*,int*);
extern void fb_blit_rows_copy(int,unsigned,int,int,unsigned,unsigned);

unsigned update_demo_image_display(int param_1,unsigned param_2,int param_3,int param_4){
  int local_18 = param_3;
  int local_14 = param_4;
  if(param_3==2){
    gui_screen_clear();
    *(volatile uint32_t*)0x200024e4UL = 0xffffffffU;
    *(volatile uint32_t*)0x200024e0UL = 0xffffffffU;
    *(volatile uint8_t*)0x200033d4UL = 0xff;
    return 0;
  }
  if(*(volatile uint8_t*)0x2001b811UL == 0){
    int iVar4 = get_device_info();
    unsigned r2 = *(uint16_t*)(iVar4+0x1072);
    if(!(r2 == *(volatile uint32_t*)0x200024e4UL &&
         (iVar4=get_device_info(), (unsigned)*(uint16_t*)(iVar4+0x1074) == *(volatile uint32_t*)0x200024e0UL))){
      gui_screen_clear();
      iVar4=get_device_info();
      *(volatile uint32_t*)0x200024e4UL = *(uint16_t*)(iVar4+0x1072);
      iVar4=get_device_info();
      *(volatile uint32_t*)0x200024e0UL = *(uint16_t*)(iVar4+0x1074);
      unsigned uVar5 = FUN_00047a84(0,&local_18,&local_14);
      fb_blit_rows_copy(param_1+0x24, uVar5, local_18/2, local_14,
                   *(volatile uint32_t*)0x200024e4UL, *(volatile uint32_t*)0x200024e0UL);
      iVar4=get_device_info();
      unsigned uVar5b = *(uint32_t*)(iVar4+0xeb4);
      iVar4=get_device_info();
      unsigned uVar10 = *(volatile uint32_t*)0x200024e0UL;
      unsigned uVar9 = *(volatile uint32_t*)0x200024e4UL;
      int iVar6 = local_14 + (int)uVar10;
      int iVar7 = local_18 + (int)uVar9;
      unsigned uVar8 = *(uint32_t*)(iVar4+0xeb8);
      reflash_fb_data_to_lcd(uVar5b, uVar8, uVar9, uVar10, iVar7, iVar6);
    }
    return 0;
  } else {
    if(*(volatile uint8_t*)0x200033d4UL == *(volatile uint8_t*)0x2001b810UL) return 0;
    *(volatile uint8_t*)0x200033d4UL = *(volatile uint8_t*)0x2001b810UL;
    gui_screen_clear();
    *(volatile uint32_t*)0x200024e4UL = 0;
    *(volatile uint32_t*)0x200024e0UL = 0;
    FUN_00047a84(0,&local_18,&local_14);
    get_demo_image_source(*(volatile uint8_t*)0x2001b810UL);
    int iVar4=get_device_info();
    unsigned uVar5 = *(uint32_t*)(iVar4+0xeb4);
    iVar4=get_device_info();
    unsigned uVar10 = *(volatile uint32_t*)0x200024e0UL;
    unsigned uVar9 = *(volatile uint32_t*)0x200024e4UL;
    int iVar6 = local_14 + (int)uVar10;
    int iVar7 = local_18 + (int)uVar9;
    unsigned uVar8 = *(uint32_t*)(iVar4+0xeb8);
    reflash_fb_data_to_lcd(uVar5, uVar8, uVar9, uVar10, iVar7, iVar6);
    return 0;
  }
}

