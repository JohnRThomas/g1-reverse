/* readable reconstruction; identity: FUN_0003e05c @ 0x0003e05c
 * public-name: navigation_overview_map_display
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   navigation_direction_img_display         <= FUN_0003dff8 @ 0x0003dff8
 *   gui_canvas_flags_set_bit1                <= FUN_000432d0 @ 0x000432d0
 *   gui_canvas_flags_clear_bit1              <= FUN_000432ec @ 0x000432ec
 *   gui_bitmps_merge_draw                    <= FUN_00043bd8 @ 0x00043bd8
 *   gui_utf_draw                             <= FUN_00043e90 @ 0x00043e90
 *   gui_clock_draw                           <= FUN_000442bc @ 0x000442bc
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   snprintf                                 <= FUN_00077914 @ 0x00077914
 *   get_timestamp                            <= FUN_0007d224 @ 0x0007d224
 *   device_info_text_width_get               <= FUN_0007d3ee @ 0x0007d3ee
 *   device_info_text_height_get_clamped      <= FUN_0007d446 @ 0x0007d446
 *   decode_rle_byte_pairs                    <= FUN_0007da70 @ 0x0007da70
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_a8c57                             @ 0x000a8c57
 *   rodata_a9ebd                             @ 0x000a9ebd   [INLINED -- G6 literal batch]
 *   rodata_a9ee1                             @ 0x000a9ee1
 *   rodata_a9eff                             @ 0x000a9eff
 *   rodata_a9f2a                             @ 0x000a9f2a
 *   rodata_a9f30                             @ 0x000a9f30   [INLINED -- G6 literal batch]
 *   rodata_a9f51                             @ 0x000a9f51   [INLINED -- G6 literal batch]
 *   rodata_aa446                             @ 0x000aa446   [INLINED -- G6 literal batch]
 *   rodata_aae20                             @ 0x000aae20
 *   g_log_level                              @ 0x2000230c
 *   g_ipc_or_evt_ctx                         @ 0x20004bb8
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ble_work_queue                         @ 0x20007574
 *   g_20010323                               @ 0x20010323
 *   g_20010324                               @ 0x20010324
 *   g_20010326                               @ 0x20010326
 *   g_20015e52                               @ 0x20015e52
 *   g_buf_2001b9ac                           @ 0x2001b9ac
 *   g_2001ba2d                               @ 0x2001ba2d
 *   g_buf_2001ba2e                           @ 0x2001ba2e
 *   g_2001c336                               @ 0x2001c336
 */
/* Reconstructed navigation_overview_map_display @ 0x3e05c  (parity: 298/300 trials, PROVEN) */

#include <stdint.h>

extern void log_message(unsigned a, unsigned b);
extern int  get_device_info(void);
extern void debug_print(void);
extern void reflash_fb_data_to_lcd(unsigned a, unsigned b, int c, int d, int e, int f);
extern void gui_canvas_flags_clear_bit1(void);
extern void gui_canvas_flags_set_bit1(void);
extern void clean_fb_data(int a, int b, int c, int d, int e, int f);
extern int  device_info_text_width_get(void);
extern int  device_info_text_height_get_clamped(void);
extern int  get_timestamp(void);
extern void gui_bitmps_merge_draw(int a, int b, int c, int d, int e, int f, int g, int h);
extern void memset_bytes(unsigned a, int b, int c);
extern void memcpy(unsigned a, unsigned b, int c);
extern void snprintf(unsigned a, int b, unsigned c, int d, int e);
extern void gui_utf_draw(int a, unsigned b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l);
extern void gui_clock_draw(int a, int b, int c, int d, int e, int f, int g);
extern void navigation_direction_img_display(unsigned char a);
extern void decode_rle_byte_pairs(unsigned a, unsigned b, unsigned c);
extern void FUN_0007d376(unsigned a, unsigned b, unsigned c, unsigned d);
extern void FUN_0007d37a(unsigned a);

void navigation_overview_map_display(unsigned param_1, int param_2)
{
    unsigned char bVar1;
    int iVar3, iVar6, iVar9, iVar10, iVar11, iVar14;
    unsigned uVar13, uVar12;
    int *piVar2 = (int*)0x2000230c;
    unsigned char *pcVar4, *pcVar5;
    unsigned lbuf32[2];
    unsigned char *lbuf = (unsigned char*)lbuf32;

    iVar3 = 0x20004bb8;
    if (*(volatile unsigned char*)(0x20004bb8 + 5) == 0) {
        if (2 < *(volatile int*)0x2000230c) {
            if (*(volatile int*)0x20007554 == 0)
                log_message(((unsigned long)"%s(): reflash overview map && text\n"), ((unsigned long)"navigation_overview_map_display"));
            else
                debug_print();
        }
        iVar6 = get_device_info();
        iVar11 = 0x640;
        iVar6 = iVar6 + 0xb90;
        while (1) {
            uVar13 = 0;
            do {
                iVar10 = (int)(uVar13 % 0x1a) * 0xa00 + iVar11 + 0x000aae20;
                iVar9 = 0;
                do {
                    iVar14 = *(volatile int*)(iVar6 + uVar13 * 4);
                    bVar1 = *(volatile unsigned char*)(iVar14 + iVar9);
                    if (bVar1 != 0)
                        *(volatile unsigned char*)(iVar14 + iVar9) =
                            bVar1 & *(volatile unsigned char*)(iVar10 + iVar9);
                    iVar9 = iVar9 + 1;
                } while (iVar9 != 0x140);
                uVar13 = uVar13 + 1;
            } while (uVar13 != 199);
            iVar9 = get_device_info();
            uVar12 = *(volatile unsigned*)(iVar9 + 0xeb4);
            iVar9 = get_device_info();
            reflash_fb_data_to_lcd(uVar12, *(volatile unsigned*)(iVar9 + 0xeb8), 0, 0, 0x280, 199);
            pcVar4 = (unsigned char*)0x2001ba2d;
            if (iVar11 == 0x500) break;
            iVar11 = 0x500;
        }
        if ((*(volatile unsigned char*)0x20010326 == 1) &&
            (*(volatile unsigned char*)0x2001ba2d == 0)) {
            if (*(volatile int*)(param_2 + 0xb1) == 0x1210) {
                if (2 < *piVar2) {
                    if (*(volatile int*)0x20007554 == 0)
                        log_message(0x000a9ee1, ((unsigned long)"navigation_overview_map_display"));
                    else
                        debug_print();
                }
                memset_bytes(0x2001ba2e, 0, 0x1210);
                FUN_0007d376(0x20007574, 0, 0xffffffff, 0xffffffff);
                memcpy(0x2001ba2e, 0x20015e52, 0x1210);
            } else {
                if (2 < *piVar2) {
                    if (*(volatile int*)0x20007554 == 0)
                        log_message(0x000a9eff, ((unsigned long)"navigation_overview_map_display"));
                    else
                        debug_print();
                }
                memset_bytes(0x2001ba2e, 0, 0x1210);
                FUN_0007d376(0x20007574, 0, 0xffffffff, 0xffffffff);
                decode_rle_byte_pairs(0x20015e52, *(volatile unsigned*)(param_2 + 0xb1), 0x2001ba2e);
            }
            *pcVar4 = 1;
            FUN_0007d37a(0x20007574);
        }
        gui_canvas_flags_clear_bit1();
        iVar11 = 1;
        do {
            clean_fb_data(iVar6, 0, 0, 0, 0x280, 199);
            {
                int a1 = device_info_text_width_get();
                int a2 = device_info_text_height_get_clamped();
                int a3 = device_info_text_width_get();
                int a4 = device_info_text_height_get_clamped();
                gui_bitmps_merge_draw(a1 + 0x1b6, a2, a3 + 0x240, a4 + 0x88,
                             0x2001c336 - 0x908, 0x2001c336, 2, 0xf);
            }
            memset_bytes(0x2001b9ac, 0, 0x80);
            snprintf(0x2001b9ac, 0x80, 0x000a9f2a, param_2 + 0xd, param_2 + 0x25);
            {
                int a1 = device_info_text_width_get();
                int a2 = device_info_text_height_get_clamped();
                int a3 = device_info_text_width_get();
                int a4 = device_info_text_height_get_clamped();
                gui_utf_draw(0, 0x2001b9ac, 0, a1 + 0xe8, a2, a3 + 0x1ae, a4 + 0x1b, 1, 0, 0, 0, 0);
            }
            {
                int a1 = device_info_text_width_get();
                int a2 = device_info_text_height_get_clamped();
                int a3 = device_info_text_width_get();
                int a4 = device_info_text_height_get_clamped();
                gui_utf_draw(0, param_2 + 0x7d, 0, a1, a2 + 0x6c, a3 + 200, a4 + 0x87, 1, 0, 0, 0, 0);
            }
            {
                int a1 = device_info_text_width_get();
                int a2 = device_info_text_height_get_clamped();
                int a3 = device_info_text_width_get();
                int a4 = device_info_text_height_get_clamped();
                gui_utf_draw(0, param_2 + 0x3d, 0, a1, a2 + 0x1d, a3 + 0x1ae, a4 + 0x38, 1, 0, 0, 0, 0);
            }
            iVar9 = get_device_info();
            iVar9 = *(volatile unsigned char*)(*(volatile int*)(iVar9 + 0xfec) + 0x5e) - 1;
            if (iVar9 != 0) iVar9 = 1;
            uVar12 = get_timestamp();
            {
                int a1 = device_info_text_width_get();
                int a2 = device_info_text_height_get_clamped();
                int a3 = device_info_text_width_get();
                int a4 = device_info_text_height_get_clamped();
                gui_clock_draw(uVar12, a1, a2 + 2, a3 + 0x4c, a4 + 0x1d, 3, iVar9);
            }
            navigation_direction_img_display(*(volatile unsigned char*)(param_2 + 1));
            uVar13 = 0;
            lbuf32[0] = *(volatile unsigned*)0x000a8c57;
            lbuf32[1] = *(volatile unsigned*)(0x000a8c57 + 4);
            do {
                iVar9 = 0;
                do {
                    iVar10 = *(volatile int*)(iVar6 + uVar13 * 4);
                    bVar1 = *(volatile unsigned char*)(iVar10 + iVar9);
                    if (bVar1 != 0)
                        *(volatile unsigned char*)(iVar10 + iVar9) =
                            bVar1 & *(volatile unsigned char*)(
                                (unsigned)lbuf[iVar11] * 0x140 +
                                (int)(uVar13 % 0x1a) * 0xa00 + 0x000aae20 + iVar9);
                    iVar9 = iVar9 + 1;
                } while (iVar9 != 0x140);
                uVar13 = uVar13 + 1;
            } while (uVar13 != 199);
            iVar9 = get_device_info();
            uVar12 = *(volatile unsigned*)(iVar9 + 0xeb4);
            iVar9 = get_device_info();
            iVar11 = iVar11 + 1;
            reflash_fb_data_to_lcd(uVar12, *(volatile unsigned*)(iVar9 + 0xeb8), 0, 0, 0x280, 199);
        } while (iVar11 != 4);
        gui_canvas_flags_set_bit1();
        {
            int a1 = device_info_text_width_get();
            int a2 = device_info_text_height_get_clamped();
            int a3 = device_info_text_width_get();
            int a4 = device_info_text_height_get_clamped();
            gui_utf_draw(0, 0x2001b9ac, 0, a1 + 0xe8, a2, a3 + 0x1ae, a4 + 0x1b, 1, 0, 0, 0, 0);
            int b1 = device_info_text_width_get();
            int b2 = device_info_text_height_get_clamped();
            int b3 = device_info_text_width_get();
            int b4 = device_info_text_height_get_clamped();
            gui_utf_draw(0, param_2 + 0x7d, 0, b1, b2 + 0x6c, b3 + 200, b4 + 0x87, 1, 0, 0, 0, 0);
            int c1 = device_info_text_width_get();
            int c2 = device_info_text_height_get_clamped();
            int c3 = device_info_text_width_get();
            int c4 = device_info_text_height_get_clamped();
            gui_utf_draw(0, param_2 + 0x3d, 0, c1, c2 + 0x1d, c3 + 0x1ae, c4 + 0x38, 1, 0, 0, 0, 0);
            iVar11 = get_device_info();
            iVar11 = *(volatile unsigned char*)(*(volatile int*)(iVar11 + 0xfec) + 0x5e) - 1;
            if (iVar11 != 0) iVar11 = 1;
            uVar12 = get_timestamp();
            int d1 = device_info_text_width_get();
            int d2 = device_info_text_height_get_clamped();
            int d3 = device_info_text_width_get();
            int d4 = device_info_text_height_get_clamped();
            gui_clock_draw(uVar12, d1, d2 + 2, d3 + 0x4c, d4 + 0x1d, 3, iVar11);
        }
    }
    piVar2 = (int*)0x2000230c;
    pcVar5 = (unsigned char*)0x2001ba2d;
    pcVar4 = (unsigned char*)0x20010323;
    if (*(volatile unsigned char*)0x20010323 == 1) {
        int do_bd8 = 0;
        if (*(volatile unsigned char*)0x20010326 == 1) {
            if (2 < *piVar2) {
                if (*(volatile int*)0x20007554 == 0)
                    log_message(((unsigned long)"%s(): reflash overview map ....\n"), ((unsigned long)"navigation_overview_map_display"));
                else
                    debug_print();
            }
            if (*(volatile int*)(param_2 + 0xb1) == 0x1210) {
                if (2 < *piVar2) {
                    if (*(volatile int*)0x20007554 == 0)
                        log_message(0x000a9ee1, ((unsigned long)"navigation_overview_map_display"));
                    else
                        debug_print();
                }
                memset_bytes(0x2001ba2e, 0, 0x1210);
                FUN_0007d376(0x20007574, 0, 0xffffffff, 0xffffffff);
                memcpy(0x2001ba2e, 0x20015e52, 0x1210);
            } else {
                if (2 < *piVar2) {
                    if (*(volatile int*)0x20007554 == 0)
                        log_message(0x000a9eff, ((unsigned long)"navigation_overview_map_display"));
                    else
                        debug_print();
                }
                memset_bytes(0x2001ba2e, 0, 0x1210);
                FUN_0007d376(0x20007574, 0, 0xffffffff, 0xffffffff);
                decode_rle_byte_pairs(0x20015e52, *(volatile unsigned*)(param_2 + 0xb1), 0x2001ba2e);
            }
            *pcVar5 = 1;
            FUN_0007d37a(0x20007574);
            do_bd8 = 1;
        } else if (*(volatile unsigned char*)0x2001ba2d == 1) {
            do_bd8 = 1;
        }
        if (do_bd8) {
            int a1 = device_info_text_width_get();
            int a2 = device_info_text_height_get_clamped();
            int a3 = device_info_text_width_get();
            int a4 = device_info_text_height_get_clamped();
            gui_bitmps_merge_draw(a1 + 0x1b6, a2, a3 + 0x240, a4 + 0x88,
                         0x2001c336 - 0x908, 0x2001c336, 2, 0xf);
        }
        *pcVar4 = 0;
    }
    pcVar4 = (unsigned char*)0x20010324;
    if (*(volatile unsigned char*)0x20010324 == 1) {
        if (2 < *(volatile int*)0x2000230c) {
            if (*(volatile int*)0x20007554 == 0)
                log_message(((unsigned long)"%s(): reflash text info ....\n"), ((unsigned long)"navigation_overview_map_display"));
            else
                debug_print();
        }
        memset_bytes(0x2001b9ac, 0, 0x80);
        snprintf(0x2001b9ac, 0x80, 0x000a9f2a, param_2 + 0xd, param_2 + 0x25);
        {
            int a1 = device_info_text_width_get();
            int a2 = device_info_text_height_get_clamped();
            int a3 = device_info_text_width_get();
            int a4 = device_info_text_height_get_clamped();
            gui_utf_draw(0, 0x2001b9ac, 0, a1 + 0xe8, a2, a3 + 0x1ae, a4 + 0x1b, 1, 0, 0, 0, 0);
            int b1 = device_info_text_width_get();
            int b2 = device_info_text_height_get_clamped();
            int b3 = device_info_text_width_get();
            int b4 = device_info_text_height_get_clamped();
            gui_utf_draw(0, param_2 + 0x3d, 0, b1, b2 + 0x1d, b3 + 0x1ae, b4 + 0x38, 1, 0, 0, 0, 0);
            int c1 = device_info_text_width_get();
            int c2 = device_info_text_height_get_clamped();
            int c3 = device_info_text_width_get();
            int c4 = device_info_text_height_get_clamped();
            gui_utf_draw(0, param_2 + 0x7d, 0, c1, c2 + 0x6c, c3 + 200, c4 + 0x87, 1, 0, 0, 0, 0);
            iVar11 = get_device_info();
            iVar11 = *(volatile unsigned char*)(*(volatile int*)(iVar11 + 0xfec) + 0x5e) - 1;
            if (iVar11 != 0) iVar11 = 1;
            uVar12 = get_timestamp();
            int d1 = device_info_text_width_get();
            int d2 = device_info_text_height_get_clamped();
            int d3 = device_info_text_width_get();
            int d4 = device_info_text_height_get_clamped();
            gui_clock_draw(uVar12, d1, d2 + 2, d3 + 0x4c, d4 + 0x1d, 3, iVar11);
        }
        navigation_direction_img_display(*(volatile unsigned char*)(param_2 + 1));
        *pcVar4 = 0;
    }
    *(volatile unsigned char*)(iVar3 + 4) = 0;
    *(volatile unsigned char*)(iVar3 + 5) = 1;
    *(volatile unsigned char*)(iVar3 + 0x15) = 0;
}
