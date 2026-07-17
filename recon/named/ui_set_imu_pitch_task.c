/* readable reconstruction; identity: FUN_00046b80 @ 0x00046b80
 * public-name: ui_set_imu_pitch_task
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   gui_set_active_canvas                    <= FUN_000431b4 @ 0x000431b4
 *   gui_screen_clear                         <= FUN_000431c0 @ 0x000431c0
 *   gui_canvas_flags_set_bit1                <= FUN_000432d0 @ 0x000432d0
 *   gui_canvas_flags_clear_bit1              <= FUN_000432ec @ 0x000432ec
 *   gui_reset_dynamic_bitmap_frame_state     <= FUN_00043308 @ 0x00043308
 *   imu_pitch_task_reset_render_state        <= FUN_000436f8 @ 0x000436f8
 *   set_imu_pitch_reflash                    <= FUN_000469bc @ 0x000469bc
 *   ui_set_imu_pitch_task                    <= FUN_00046b80 @ 0x00046b80
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 * address symbols (name @ address):
 *   rodata_a8e98                             @ 0x000a8e98
 *   rodata_aae20                             @ 0x000aae20
 *   rodata_d71ad                             @ 0x000d71ad
 *   rodata_d71e3                             @ 0x000d71e3
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_imu_pitch_task_state                   @ 0x2001cf8f
 */
/* Reconstructed FUN_00046b80 @ 0x46b80  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int log_message(int,...);
extern int get_device_info(int,...);
extern int debug_print(int,...);
extern int gui_set_active_canvas(int,...);
extern int gui_screen_clear(int,...);
extern int gui_canvas_flags_set_bit1(int,...);
extern int gui_canvas_flags_clear_bit1(int,...);
extern int gui_reset_dynamic_bitmap_frame_state(int,...);
extern int imu_pitch_task_reset_render_state(int,...);
extern int FUN_0004382c(int,...);
extern int set_imu_pitch_reflash(int,...);
extern int reflash_fb_data_to_lcd(int,...);
extern int FUN_0007d3dc(int,...);

unsigned ui_set_imu_pitch_task(int param_1, unsigned param_2, int param_3)
{
    unsigned char bVar1,bVar2; int iVar4,iVar6,iVar8,iVar9,iVar12;
    unsigned char *puVar7; unsigned uVar10,uVar11;
    union { struct { unsigned local_30; int iStack_2c; }; unsigned char b[8]; } u;
    unsigned char auStack_28[4];
    volatile char *pcVar3 = (volatile char*)0x2001cf8f;
    volatile int *puVar5;

    get_device_info(0);
    gui_set_active_canvas(param_1 + 0x24);
    gui_canvas_flags_set_bit1(0);
    if(*pcVar3 == 0){
        if(param_3 == 1){
            if(pcVar3[1] != 0) return 0;
            FUN_0007d3dc(0);
            gui_screen_clear(0);
            imu_pitch_task_reset_render_state(0);
            pcVar3[0]=0; pcVar3[1]=0; pcVar3[2]=0;
            pcVar3[1]=1;
            gui_reset_dynamic_bitmap_frame_state(0);
            *pcVar3 = 1;
            gui_canvas_flags_clear_bit1(0);
            puVar5 = (volatile int*)0x000a8e98;
            iVar9 = 0;
            do {
                set_imu_pitch_reflash(0);
                uVar10 = 0;
                u.local_30 = *puVar5;
                do {
                    iVar8 = 0;
                    u.iStack_2c = puVar5[1];
                    do {
                        iVar4 = 0x000aae20;
                        iVar12 = *(int*)(param_1 + 0x24 + uVar10*4);
                        bVar2 = *(unsigned char*)(iVar12 + iVar8);
                        puVar7 = auStack_28;
                        iVar6 = u.iStack_2c;
                        if(bVar2 != 0){
                            bVar1 = *(volatile unsigned char*)((unsigned)u.b[iVar9]*0x140 + (uVar10%0x1a)*0xa00 + 0x000aae20 + iVar8);
                            puVar7 = (unsigned char*)(unsigned)bVar1;
                            *(unsigned char*)(iVar12+iVar8) = bVar2 & bVar1;
                            iVar6 = iVar4;
                        }
                        iVar8 = iVar8+1;
                    } while(iVar8 != 0x140);
                    uVar10 = uVar10+1;
                } while(uVar10 != 199);
                iVar8 = get_device_info(u.local_30, iVar6, puVar7);
                uVar11 = *(unsigned*)(iVar8 + 0xeb4);
                iVar8 = get_device_info(0);
                iVar9 = iVar9+1;
                reflash_fb_data_to_lcd(uVar11, *(unsigned*)(iVar8+0xeb8), 0,0,0x280,199);
            } while(iVar9 != 8);
            gui_canvas_flags_set_bit1(0);
            return 0;
        }
        if(param_3 != 2) return 0;
        if(2 < *(volatile int*)0x2000230c){
            if(*(volatile int*)0x20007554 == 0) log_message(0x000d71ad,0x000d71e3);
            else debug_print(0);
        }
        gui_screen_clear(0);
    } else {
        if(*pcVar3 != 1) return 0;
        if(param_3 == 1){ set_imu_pitch_reflash(0); return 0; }
        if(param_3 != 2) return 0;
        if(2 < *(volatile int*)0x2000230c){
            if(*(volatile int*)0x20007554 == 0) log_message(0x000d71ad,0x000d71e3);
            else debug_print(0);
        }
        FUN_0004382c(0);
    }
    FUN_0007d3dc(0);
    pcVar3[0]=0; pcVar3[1]=0; pcVar3[2]=0;
    return 0;
}
