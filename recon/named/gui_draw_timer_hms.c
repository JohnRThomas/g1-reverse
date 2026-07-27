/* readable reconstruction; identity: FUN_000362e8 @ 0x000362e8
 * public-name: gui_draw_timer_hms
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   gui_draw_timer_hms                       <= FUN_000362e8 @ 0x000362e8
 *   utf8_string_to_utf16                     <= FUN_000478d8 @ 0x000478d8
 *   find_chinese_bitmap_by_unicode           <= FUN_0004792c @ 0x0004792c
 *   load_icon_bitmap_expanded                <= FUN_00047a4c @ 0x00047a4c
 *   nullsub_2                                <= FUN_0007d2d6 @ 0x0007d2d6
 *   fb_blit_rows_wrap320                     <= FUN_0007d4f8 @ 0x0007d4f8
 *   font_glyph_pixel_offset                  <= FUN_0007d850 @ 0x0007d850
 * address symbols (name @ address):
 *   rodata_a8d52                             @ 0x000a8d52
 *   rodata_a8d5d                             @ 0x000a8d5d
 */
/* Reconstructed FUN_000362e8 @ 0x362e8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte; typedef uint32_t undefined4; typedef uint16_t undefined2; typedef unsigned int uint; typedef unsigned short ushort;
extern int get_device_info(int,...);
extern void* utf8_string_to_utf16(unsigned int, unsigned short*);
extern unsigned int find_chinese_bitmap_by_unicode(unsigned int, short, short);
extern int load_icon_bitmap_expanded(int,...);
extern int nullsub_2(int,...);
extern int fb_blit_rows_wrap320(int*, int, int, int, int, int);
extern int font_glyph_pixel_offset(int,...);

undefined4 gui_draw_timer_hms(int param_1,undefined4 param_2)
{
  int bVar1; int iVar2; undefined4 uVar3; int iVar4; int iVar5;
  uint uVar6; uint uVar7; uint uVar8;
  ushort local_2a[3];
  param_1 = param_1 + 0x24;
  iVar2 = get_device_info(0);
  uVar8 = *(uint *)(iVar2 + 0xef) % 0xe10;
  uVar6 = (*(uint *)(iVar2 + 0xef) / 0xe10) % 0x18;
  bVar1 = 0;
  uVar7 = uVar8 % 0x3c;
  local_2a[0] = 0;
  if (uVar8 < 0x3c) {
    bVar1 = (uVar6 == 0 && uVar7 == 0);
    if (uVar6 != 0 || uVar7 != 0) { uVar3 = 9; } else { uVar3 = 4; }
  } else { uVar3 = 9; }
  uVar3 = load_icon_bitmap_expanded(uVar3,0x120);
  iVar4 = 0xc;
  fb_blit_rows_wrap320(param_1,uVar3,0xc,0x18,0xc,0xc);
  if (bVar1) {
    iVar4 = utf8_string_to_utf16(0xa8d52,(int)local_2a);
    for (iVar5 = 0; iVar5 < (int)(uint)local_2a[0]; iVar5 = iVar5 + 1) {
      uVar3 = find_chinese_bitmap_by_unicode(*(undefined2 *)(iVar4 + iVar5 * 2),0xc,0x24);
      fb_blit_rows_wrap320(param_1,uVar3,0xc,0x24,iVar5 * 0xc + 0x20,8);
    }
  } else {
    if (uVar6 != 0) {
      uVar3 = font_glyph_pixel_offset(uVar6 / 10,0xf,0x24,0);
      fb_blit_rows_wrap320(param_1,uVar3,0xf,0x24,0x20,0xc);
      uVar3 = font_glyph_pixel_offset(uVar6 % 10,0xf,0x24,0);
      fb_blit_rows_wrap320(param_1,uVar3,0xf,0x24,0x2f,0xc);
      uVar3 = font_glyph_pixel_offset(10,0xf,0x24,0);
      fb_blit_rows_wrap320(param_1,uVar3,0xf,0x24,0x3e,0xc);
      iVar4 = 0x39;
    }
    uVar3 = font_glyph_pixel_offset((uVar8 / 0x3c) / 10,0xf,0x24,0);
    fb_blit_rows_wrap320(param_1,uVar3,0xf,0x24,iVar4 + 0x14,0xc);
    uVar3 = font_glyph_pixel_offset((uVar8 / 0x3c) % 10,0xf,0x24,0);
    fb_blit_rows_wrap320(param_1,uVar3,0xf,0x24,iVar4 + 0x23,0xc);
    uVar3 = font_glyph_pixel_offset(10,0xf,0x24,0);
    fb_blit_rows_wrap320(param_1,uVar3,0xf,0x24,iVar4 + 0x32,0xc);
    uVar3 = font_glyph_pixel_offset(uVar7 / 10,0xf,0x24,0);
    fb_blit_rows_wrap320(param_1,uVar3,0xf,0x24,iVar4 + 0x41,0xc);
    uVar3 = font_glyph_pixel_offset(uVar7 % 10,0xf,0x24,0);
    fb_blit_rows_wrap320(param_1,uVar3,0xf,0x24,iVar4 + 0x50,0xc);
  }
  if (*(byte *)(iVar2 + 0xf3) < 2) {
    nullsub_2(param_1,param_2,0,0,0);
  } else {
    uVar3 = load_icon_bitmap_expanded(0xc,0x120);
    fb_blit_rows_wrap320(param_1,uVar3,0xc,0x18,0xe2,0x14);
    iVar2 = utf8_string_to_utf16(0xa8d5d,(int)local_2a);
    for (iVar4 = 0; iVar4 < (int)(uint)local_2a[0]; iVar4 = iVar4 + 1) {
      uVar3 = find_chinese_bitmap_by_unicode(*(undefined2 *)(iVar2 + iVar4 * 2),0xc,0x20);
      fb_blit_rows_wrap320(param_1,uVar3,0xc,0x20,iVar4 * 0xc + 0xf4,8);
    }
  }
  return 0;
}
