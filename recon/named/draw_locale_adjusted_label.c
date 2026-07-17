/* readable reconstruction; identity: FUN_0003f380 @ 0x0003f380
 * public-name: draw_locale_adjusted_label
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   draw_locale_adjusted_label               <= FUN_0003f380 @ 0x0003f380
 *   gui_utf_draw                             <= FUN_00043e90 @ 0x00043e90
 *   device_info_text_width_get               <= FUN_0007d3ee @ 0x0007d3ee
 *   device_info_text_height_get_clamped      <= FUN_0007d446 @ 0x0007d446
 * address symbols (name @ address):
 *   rodata_aa070                             @ 0x000aa070
 *   rodata_aa091                             @ 0x000aa091
 */
/* Reconstructed FUN_0003f380 @ 0x3f380  (parity: 300/300 trials, PROVEN) */

extern int FUN_00023ee0(void);
extern int device_info_text_width_get(void);
extern int device_info_text_height_get_clamped(void);
extern void gui_utf_draw(int,...);
void draw_locale_adjusted_label(void){
  int iVar1=FUN_00023ee0();
  int iVar2,iVar3,iVar4,uVar5;
  if(iVar1==6){
    iVar1=device_info_text_width_get(); iVar2=device_info_text_height_get_clamped(); iVar3=device_info_text_width_get(); iVar4=device_info_text_height_get_clamped();
    iVar1+=0xa4; uVar5=0xaa091;
  } else {
    iVar1=device_info_text_width_get(); iVar2=device_info_text_height_get_clamped(); iVar3=device_info_text_width_get(); iVar4=device_info_text_height_get_clamped();
    iVar1+=0x92; uVar5=0xaa070;
  }
  gui_utf_draw(0,uVar5,0,iVar1,iVar2+0x37,iVar3+0x23f,iVar4+0x6d,2,0,0,0,0);
}
