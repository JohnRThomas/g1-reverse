#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00048b5c @ 0x00048b5c
 * public-name: ui_refalsh_warp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 *   update_demo_image_display                <= FUN_00036a18 @ 0x00036a18
 *   ui_DashBoard_task                        <= FUN_0003af78 @ 0x0003af78
 *   ui_QuickNote_task                        <= FUN_0003b824 @ 0x0003b824
 *   ui_even_ai_task                          <= FUN_0003bfe0 @ 0x0003bfe0
 *   ui_even_ai_draw_mic_status_icon          <= FUN_0003cb58 @ 0x0003cb58
 *   ui_teleprompter_task                     <= FUN_0003cf44 @ 0x0003cf44
 *   ui_onboarding_task                       <= FUN_00042d44 @ 0x00042d44
 *   ui_raster_height_task                    <= FUN_000430c0 @ 0x000430c0
 *   ui_set_imu_pitch_task                    <= FUN_00046b80 @ 0x00046b80
 * address symbols (name @ address):
 *   rodata_ef784                             @ 0x000ef784
 *   rodata_ef7a0                             @ 0x000ef7a0
 *   rodata_f01eb                             @ 0x000f01eb
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_2000a098                               @ 0x2000a098
 */
/* Reconstructed ui_refalsh_warp @ 0x48b5c.
 * Reachable code ends at 0x48e10; the following six words are its literal
 * pool, not executable instructions.  The reviewed executable extent is
 * therefore 692 bytes.
 * Bytes from 0x48e28 onward belong to separately reconstructed functions. */

extern int is_battery_critical(void);
extern int update_demo_image_display(int,int,int);
extern int DEBUG_PRINT(int,int,int,int);
extern int debug_print(int,int,int,int);
extern int FUN_0003603c(int,int,int);
extern int FUN_00036b3c(int,int,int);
extern int FUN_0003f410(int,int,int);
extern int FUN_0003fecc(int,int,int);
extern int ui_DashBoard_task(int,int,int);
extern int ui_even_ai_draw_mic_status_icon(int,int,int);
extern int ui_teleprompter_task(int,int,int);
extern int ui_QuickNote_task(int,int,int);
extern int ui_onboarding_task(int,int,int);
extern int ui_raster_height_task(int,int,int);
extern int ui_even_ai_task(int,int,int);
extern int ui_set_imu_pitch_task(int,int,int);

#define DBG1(ID) do { \
    int sink = *p_7554; \
    if (sink == 0) DEBUG_PRINT(((unsigned long)&rodata_ef784) /*=0xef784*/, ((unsigned long)&rodata_f01eb) /*=0xf01eb*/, (ID), sink); \
    else debug_print(((unsigned long)&rodata_ef784) /*=0xef784*/, ((unsigned long)&rodata_f01eb) /*=0xf01eb*/, (ID), sink); \
} while (0)
#define DBG2(ID) do { \
    int sink = *p_7554; \
    if (sink == 0) DEBUG_PRINT(((unsigned long)&rodata_ef7a0) /*=0xef7a0*/, ((unsigned long)&rodata_f01eb) /*=0xf01eb*/, (ID), sink); \
    else debug_print(((unsigned long)&rodata_ef7a0) /*=0xef7a0*/, ((unsigned long)&rodata_f01eb) /*=0xf01eb*/, (ID), sink); \
} while (0)
#define NORMAL(H,ID) do{ \
    if(*p_230c > 2) DBG1(ID); \
    r4 = H(param_1+0xb6c, param_3, param_4); \
    if(*p_230c > 2) DBG2(ID); \
    return r4; }while(0)

int ui_refalsh_warp(int param_1,int param_2,int param_3,int param_4){
    volatile int *p_a098=(volatile int*)((unsigned long)&g_2000a098) /*=0x2000a098*/;
    volatile int *p_230c=(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/;
    volatile int *p_7554=(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    int r4;
    if (is_battery_critical()==1){
        if (param_2==3) update_demo_image_display(param_1+0xb6c, param_3, param_4);
        return 0;
    }
    *p_a098 = param_2;
    switch(param_2){
    case 4:  return FUN_0003603c(param_1+0xb6c,param_3,param_4);
    case 5:  return FUN_00036b3c(param_1+0xb6c,param_3,param_4);
    case 10: return FUN_0003f410(param_1+0xb6c,param_3,param_4);
    case 11: return FUN_0003fecc(param_1+0xb6c,param_3,param_4);
    case 6:  NORMAL(ui_DashBoard_task, 6);
    case 7:  NORMAL(ui_even_ai_draw_mic_status_icon, 7);
    case 9:  NORMAL(ui_teleprompter_task, 9);
    case 12: NORMAL(ui_QuickNote_task, 12);
    case 14: NORMAL(ui_onboarding_task, 14);
    case 15: NORMAL(ui_raster_height_task, 15);
    case 16: NORMAL(ui_even_ai_task, 16);
    case 17: NORMAL(ui_set_imu_pitch_task, 17);
    default: {
        int id = param_2;
        if(*p_230c > 2) DBG1(id);
        int (*fp)(int,int,int) = *(int(**)(int,int,int))(param_1+0xb80);
        unsigned char b = *(volatile unsigned char*)(param_1+0xd5);
        r4 = fp(param_1+0xb6c, b, param_1+0xd4);
        if(*p_230c > 2) DBG2(id);
        return r4;
    }
    }
}
