#include "g1_app_symbols.h"
/* named: draw_locale_adjusted_label */
/* Reconstructed draw_locale_adjusted_label @ 0x3f380  (parity: 300/300 trials, PROVEN) */

extern int FUN_00023ee0(void);
extern int device_info_text_width_get(void);
extern int device_info_text_height_get_clamped(void);
extern void gui_utf_draw(int,...);
void draw_locale_adjusted_label(void){
  int iVar1=FUN_00023ee0();
  int iVar2,iVar3,iVar4,uVar5;
  if(iVar1==6){
    iVar1=device_info_text_width_get(); iVar2=device_info_text_height_get_clamped(); iVar3=device_info_text_width_get(); iVar4=device_info_text_height_get_clamped();
    iVar1+=0xa4; uVar5="Ihre Route wird berechnet..." /*=0xaa091*/;
  } else {
    iVar1=device_info_text_width_get(); iVar2=device_info_text_height_get_clamped(); iVar3=device_info_text_width_get(); iVar4=device_info_text_height_get_clamped();
    iVar1+=0x92; uVar5="Your route is being generated..." /*=0xaa070*/;
  }
  gui_utf_draw(0,uVar5,0,iVar1,iVar2+0x37,iVar3+0x23f,iVar4+0x6d,2,0,0,0,0);
}

