/* readable reconstruction; identity: FUN_00036d38 @ 0x00036d38
 * public-name: FUN_00036d38
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   gui_utf_draw                             <= FUN_00043e90 @ 0x00043e90
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   device_info_text_width_get               <= FUN_0007d3ee @ 0x0007d3ee
 *   device_info_text_height_get_clamped      <= FUN_0007d446 @ 0x0007d446
 * address symbols (name @ address):
 *   rodata_a8ea1                             @ 0x000a8ea1
 *   rodata_a8eb5                             @ 0x000a8eb5
 *   rodata_a8ec6                             @ 0x000a8ec6
 *   rodata_a8edd                             @ 0x000a8edd
 *   g_display_last_drawn_lang                @ 0x20004968
 */
/* Reconstructed FUN_00036d38 @ 0x36d38  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern unsigned FUN_00023ee0(void);
extern int get_device_info(void);
extern int device_info_text_width_get(void);
extern int device_info_text_height_get_clamped(void);
extern void clean_fb_data(int,int,int,int,int,int);
extern void reflash_fb_data_to_lcd(int,int,int,int,int,int);
extern void gui_utf_draw(int,int,int,int,int,int,int,int,int,int,int,int);

void FUN_00036d38(void)
{
    volatile uint8_t *g = (volatile uint8_t*)0x20004968;
    unsigned uVar1;
    int iVar2, iVar3, iVar4, iVar5, iVar6;
    int uVar7, uVar8;

    uVar1 = FUN_00023ee0();
    if ((unsigned)*g != uVar1) {
        *g = (uint8_t)uVar1;
        iVar2 = get_device_info();
        iVar3 = device_info_text_width_get();
        iVar4 = device_info_text_height_get_clamped();
        iVar5 = device_info_text_width_get();
        iVar6 = device_info_text_height_get_clamped();
        clean_fb_data(iVar2 + 0xb90, 0, iVar3 + 0x10a, iVar4 + 0x1c, iVar5 + 0x232, iVar6 + 0x88);
        iVar2 = get_device_info();
        uVar7 = *(volatile int*)(iVar2 + 0xeb4);
        iVar2 = get_device_info();
        uVar8 = *(volatile int*)(iVar2 + 0xeb8);
        iVar2 = device_info_text_width_get();
        iVar3 = device_info_text_height_get_clamped();
        iVar4 = device_info_text_width_get();
        iVar5 = device_info_text_height_get_clamped();
        reflash_fb_data_to_lcd(uVar7, uVar8, iVar2 + 0x10a, iVar3 + 0x1c, iVar4 + 0x232, iVar5 + 0x88);
    }
    if (uVar1 == 6) {
        iVar2 = device_info_text_width_get();
        iVar3 = device_info_text_height_get_clamped();
        iVar4 = device_info_text_width_get();
        iVar5 = device_info_text_height_get_clamped();
        gui_utf_draw(0, 0x000a8ec6, 0, iVar2 + 0x134, iVar3 + 0x28, iVar4 + 0x236, iVar5 + 0x43, 1, 0, 0, 0, 0);
        iVar2 = device_info_text_width_get();
        iVar4 = device_info_text_height_get_clamped();
        iVar5 = device_info_text_width_get();
        iVar3 = device_info_text_height_get_clamped();
        iVar2 = iVar2 + 0x15a;
        uVar7 = 0x000a8edd;
        gui_utf_draw(0, uVar7, 0, iVar2, iVar4 + 0x43, iVar5 + 0x236, iVar3 + 0x5e, 1, 0, 0, 0, 0);
    } else {
        iVar2 = device_info_text_width_get();
        iVar3 = device_info_text_height_get_clamped();
        iVar4 = device_info_text_width_get();
        iVar5 = device_info_text_height_get_clamped();
        gui_utf_draw(0, 0x000a8ea1, 0, iVar2 + 0x144, iVar3 + 0x28, iVar4 + 0x236, iVar5 + 0x43, 1, 0, 0, 0, 0);
        iVar2 = device_info_text_width_get();
        iVar4 = device_info_text_height_get_clamped();
        iVar5 = device_info_text_width_get();
        iVar3 = device_info_text_height_get_clamped();
        iVar2 = iVar2 + 0x150;
        uVar7 = 0x000a8eb5;
        gui_utf_draw(0, uVar7, 0, iVar2, iVar4 + 0x43, iVar5 + 0x236, iVar3 + 0x5e, 1, 0, 0, 0, 0);
    }
}
