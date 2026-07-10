/* named: power_down_panel */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed power_down_panel @ 0x15fdc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t, ...);
extern void panel_pwr_gpio_deassert(void);
extern void debug_print(uint32_t, ...);
extern int app_msleep_thunk_a(int);
extern int dev_write_reg3(int, ...);

unsigned int power_down_panel(void)
{
    volatile int *piVar1 = (volatile int*)0x2000230cUL;
    int iVar2;
    unsigned int format_string;

    app_msleep_thunk_a(2);
    panel_pwr_gpio_deassert();
    if (0 < *piVar1) {
        if (*(volatile int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x0009949aUL, 0x00099c17UL);
        } else {
            debug_print(0x0009949aUL, 0x00099c17UL);
        }
    }
    app_msleep_thunk_a(0x10);
    iVar2 = dev_write_reg3(*(volatile uint32_t*)(*(volatile uint32_t*)(0x00087d10UL + 4) + 0x1c), 4, 3, 1);
    if (iVar2 < 0) {
        if (*piVar1 < 1) {
            return 0;
        }
        iVar2 = *(volatile int*)0x20007554UL;
        format_string = 0x0009940bUL;
    } else {
        if (0 < *piVar1) {
            if (*(volatile int*)0x20007554UL == 0) {
                DEBUG_PRINT(0x000994b9UL, 0x00099c17UL);
            } else {
                debug_print(0x000994b9UL, 0x00099c17UL);
            }
        }
        app_msleep_thunk_a(5);
        iVar2 = dev_write_reg3(*(volatile uint32_t*)(*(volatile uint32_t*)(0x00087cf8UL + 4) + 0x1c), 8, 1);
        if (iVar2 < 0) {
            if (*piVar1 < 1) {
                return 0;
            }
            iVar2 = *(volatile int*)0x20007554UL;
            format_string = 0x00099329UL;
        } else {
            if (*piVar1 < 1) {
                return 0;
            }
            iVar2 = *(volatile int*)0x20007554UL;
            format_string = 0x000994d3UL;
        }
    }
    if (iVar2 == 0) {
        DEBUG_PRINT(format_string, 0x00099c17UL);
    } else {
        debug_print(format_string, 0x00099c17UL);
    }
    return 0;
}

