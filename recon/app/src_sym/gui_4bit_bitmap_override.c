/* Reconstructed gui_4bit_bitmap_override @ 0x43d78  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t, ...);
extern void *get_device_info(void);
extern void debug_print(uint32_t, ...);
extern int atomic_get_3_0(void);
extern int resource_manger_get(int, uint32_t, int*, int*, uint32_t*, int);
extern void reflash_fb_data_to_lcd(uint32_t, uint32_t, unsigned int, unsigned int, int, int);
extern void FUN_0007d586(uint32_t, uint32_t, int, int, unsigned int, unsigned int);

unsigned int gui_4bit_bitmap_override(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    int iVar1;
    unsigned int uVar2;
    int local_1c = 0;
    int local_18 = 0;
    uint32_t local_14 = 0;

    if ((param_2 < 0x281) && (param_3 < 0x1e1)) {
        iVar1 = resource_manger_get(4, param_1, &local_1c, &local_18, &local_14, 0);
        if (-1 < iVar1) {
            FUN_0007d586(*(volatile uint32_t*)0x2000a034UL, local_14, local_1c, local_18, param_2, param_3);
            iVar1 = atomic_get_3_0();
            if ((iVar1 << 0x1e) < 0) {
                iVar1 = (int)(intptr_t)get_device_info();
                uVar2 = *(uint32_t*)(intptr_t)(iVar1 + 0xeb4);
                iVar1 = (int)(intptr_t)get_device_info();
                reflash_fb_data_to_lcd(uVar2, *(uint32_t*)(intptr_t)(iVar1 + 0xeb8), param_2, param_3, local_1c + param_2, local_18 + param_3);
            }
            return 0;
        }
        if (1 < *(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */) {
            if (*(volatile int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
                DEBUG_PRINT(0x000aa8ebUL, 0x000aacafUL);
            } else {
                debug_print(0x000aa8ebUL, 0x000aacafUL);
            }
        }
    } else if (0 < *(volatile int*)0x2000230cUL) {
        if (*(volatile int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x000aaa01UL, 0x000aacafUL, param_2, param_3);
        } else {
            debug_print(0x000aaa01UL, 0x000aacafUL, param_2, param_3);
        }
    }
    return 0xffffffffUL;
}

