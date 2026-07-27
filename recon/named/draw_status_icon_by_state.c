/* readable reconstruction; identity: FUN_0003be18 @ 0x0003be18
 * public-name: draw_status_icon_by_state
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   draw_status_icon_by_state                <= FUN_0003be18 @ 0x0003be18
 *   gui_reset_dynamic_bitmap_frame_state     <= FUN_00043308 @ 0x00043308
 *   gui_clear_icon_box_40                    <= FUN_00043324 @ 0x00043324
 *   gui_bmp_dynamic_bitmap_draw              <= FUN_0004334c @ 0x0004334c
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   device_info_text_width_get               <= FUN_0007d3ee @ 0x0007d3ee
 *   device_info_text_height_get_clamped      <= FUN_0007d446 @ 0x0007d446
 * address symbols (name @ address):
 *   g_status_icon_last_state                 @ 0x200024f0
 */
/* Reconstructed FUN_0003be18 @ 0x3be18  (parity: 300/300 trials, PROVEN) */
extern int get_device_info(void);
extern unsigned int gui_reset_dynamic_bitmap_frame_state(void);
extern void gui_clear_icon_box_40(int a0,int a1);
extern void gui_bmp_dynamic_bitmap_draw(int a0,int a1,int a2,int a3,int a4,int a5,int a6,int a7);
extern void reflash_fb_data_to_lcd(int a0,int a1,int a2,int a3,int a4,int a5);
extern int device_info_text_width_get(void);
extern int device_info_text_height_get_clamped(void);

int draw_status_icon_by_state(unsigned char *param_1, int param_2, int param_3, int param_4)
{
    unsigned int uVar5 = *param_1;
    int uVar2 = 0, iVar3 = 0, uVar4 = 0;
    volatile int *piVar1 = (volatile int*)0x200024f0UL;

    if (uVar5 < 6) {
        if (*piVar1 != 1) {
            gui_reset_dynamic_bitmap_frame_state();
            *piVar1 = 1;
            uVar2 = device_info_text_width_get();
            iVar3 = device_info_text_height_get_clamped();
            gui_clear_icon_box_40(uVar2, iVar3+0x36);
            iVar3 = get_device_info();
            uVar2 = *(int*)(iVar3+0xeb4);
            iVar3 = get_device_info();
            reflash_fb_data_to_lcd(uVar2, *(int*)(iVar3+0xeb8), 0,0,0x280,199);
        }
        uVar2 = device_info_text_width_get();
        iVar3 = device_info_text_height_get_clamped();
        iVar3 = iVar3+0x36;
        uVar4 = 1;
    } else if (uVar5 == 6) {
        if (*piVar1 != 9) {
            gui_reset_dynamic_bitmap_frame_state();
            *piVar1 = 9;
            uVar2 = device_info_text_width_get();
            iVar3 = device_info_text_height_get_clamped();
            gui_clear_icon_box_40(uVar2, iVar3+0x36);
            iVar3 = get_device_info();
            uVar2 = *(int*)(iVar3+0xeb4);
            iVar3 = get_device_info();
            reflash_fb_data_to_lcd(uVar2, *(int*)(iVar3+0xeb8), 0,0,0x280,199);
        }
        uVar2 = device_info_text_width_get();
        iVar3 = device_info_text_height_get_clamped();
        iVar3 = iVar3+0x36;
        uVar4 = 9;
    } else {
        if (uVar5 != 7) {
            if (uVar5 < 0xc) {
                if (*piVar1 == 0xff) return 0;
                gui_reset_dynamic_bitmap_frame_state();
                *piVar1 = 0xff;
                uVar2 = device_info_text_width_get();
                iVar3 = device_info_text_height_get_clamped();
                gui_clear_icon_box_40(uVar2, iVar3+0x36);
                iVar3 = get_device_info();
                uVar2 = *(int*)(iVar3+0xeb4);
                iVar3 = get_device_info();
                reflash_fb_data_to_lcd(uVar2, *(int*)(iVar3+0xeb8), 0,0,0x280,199);
                return 0;
            }
            if (uVar5-0xc < 2) return 0;
            if (uVar5==0xf) return 0;
            if ((uVar5!=0xe) && (uVar5!=0x10)) return 0;
            if (*piVar1==0xff) return 0;
            gui_reset_dynamic_bitmap_frame_state();
            *piVar1 = 0xff;
            return 0;
        }
        if (*piVar1 != 4) {
            gui_reset_dynamic_bitmap_frame_state();
            *piVar1 = 4;
            uVar2 = device_info_text_width_get();
            iVar3 = device_info_text_height_get_clamped();
            gui_clear_icon_box_40(uVar2, iVar3+0x36);
            iVar3 = get_device_info();
            uVar2 = *(int*)(iVar3+0xeb4);
            iVar3 = get_device_info();
            reflash_fb_data_to_lcd(uVar2, *(int*)(iVar3+0xeb8), 0,0,0x280,199);
        }
        uVar2 = device_info_text_width_get();
        iVar3 = device_info_text_height_get_clamped();
        iVar3 = iVar3+0x36;
        uVar4 = 4;
    }
    gui_bmp_dynamic_bitmap_draw(uVar4,uVar2,iVar3,0,0,0,0,param_4);
    return 0;
}
