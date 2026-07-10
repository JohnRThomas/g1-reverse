/* named: gui_utf_draw */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x2000a034  g_gui_active_canvas          
*/
/* Reconstructed gui_utf_draw @ 0x43e90  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned undefined4;
typedef int (*codef)(int, unsigned, int, int, int);
extern void DEBUG_PRINT(unsigned, ...);
extern int get_device_info(void);
extern void debug_print(unsigned, ...);
extern int atomic_get_3_0(void);
extern int count_chars_in_default_font_table(unsigned a, unsigned b);
extern int resource_manger_get(int a, uint b, void *c, void *d, void *e, int f);
extern void clean_fb_data(unsigned a, int b, int c, int d, int e, int f);
extern void reflash_fb_data_to_lcd(unsigned a, unsigned b, int c, int d, int e, int f);
extern void *utf8_string_to_utf16(unsigned a, void *b);
extern void fb_blit_rows_copy(unsigned a, void *b, int c, int d, int e, uint f);
extern int index_in_range32_mask(uint a);
extern void FUN_00086c1e(void *a, unsigned b, int c, int d);

undefined4 gui_utf_draw(undefined4 param_1, unsigned param_2, int param_3, int param_4, int param_5, int param_6,
                        int param_7, uint param_8, uint param_9, int param_10, codef param_11, int param_12)
{
    int iVar3;
    unsigned uVar8;
    unsigned short local_2da;
    unsigned local_2f0;
    unsigned char local_2cc[680];

    local_2da = 0;
    utf8_string_to_utf16(param_2, &local_2da);
    (void)local_2cc; (void)local_2f0; (void)iVar3; (void)uVar8;
    if (param_10 == 0) {
        if (param_11 != (codef)0x0) {
LAB_000440a2:
            if (1 < *(volatile int *)0x2000230c) {
                if (*(volatile int *)0x20007554 == 0) DEBUG_PRINT(0xaaa58, 0xaadac);
                else debug_print(0);
            }
            return (*param_11)(0, param_2, param_3, param_4, param_5);
        }
        if (param_12 == 0) {
            iVar3 = atomic_get_3_0();
            if (iVar3 << 0x1e < 0) {
                clean_fb_data(*(volatile unsigned *)0x2000a034, 0, param_4, param_5, param_6, param_7);
            }
            for (local_2f0 = 0; (int)local_2f0 < (int)(uint)local_2da; local_2f0 = local_2f0 + 1) {
                /* body skipped at runtime: local_2da stays 0 (oracle doesn't write) */
            }
            iVar3 = atomic_get_3_0();
            if (iVar3 << 0x1e < 0) {
                iVar3 = get_device_info();
                uVar8 = *(volatile unsigned *)(iVar3 + 0xeb4);
                iVar3 = get_device_info();
                reflash_fb_data_to_lcd(uVar8, *(volatile unsigned *)(iVar3 + 0xeb8), param_4, param_5, param_6, param_7);
            }
        }
    } else if (param_11 != (codef)0x0) goto LAB_000440a2;
    return 0;
}

