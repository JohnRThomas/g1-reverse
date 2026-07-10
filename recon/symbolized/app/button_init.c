#include "g1_app_symbols.h"
/* named: button_init */
/* globals referenced:
//   0x00087b48  g_gpio1_dev                  
//   0x00087b60  g_gpio0_dev                  
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed button_init @ 0x17a40  (parity: 200/200 trials, PROVEN) */
extern int DEBUG_PRINT(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern int FUN_00017688(unsigned int, unsigned int);
extern void gpio_pin_set_checked(unsigned int, unsigned int, unsigned int);
extern unsigned int gpio_pin_get_raw_checked(unsigned int, unsigned int);
extern void FUN_00017858(unsigned int, unsigned int);
extern unsigned int gpio_pin_get_checked(unsigned int);
extern void debug_print(void);
extern int get_board_rev_flag(void);
extern int z_device_is_ready(unsigned int);

unsigned char button_init(void)
{
    volatile int *piVar2 = (volatile int *)((uintptr_t)&g_log_level) /*=0x2000230c*/;
    unsigned int uVar15 = 0;
    int iVar5, iVar6, iVar16;
    unsigned char bVar4;
    unsigned int uVar7,uVar8,uVar9,uVar10,uVar11,uVar12,uVar13;
    unsigned int uVar14 = 0, uVar18;
    void *pcVar17;

    FUN_00017688(0, ((uintptr_t)&tbl_ffc8) /*=0x10000*/);
    FUN_00017688(0, ((uintptr_t)&tbl_ffc8) /*=0x10000*/);
    FUN_00017688(0, ((uintptr_t)&tbl_ffc8) /*=0x10000*/);
    FUN_00017688(0, ((uintptr_t)&tbl_ffc8) /*=0x10000*/);
    FUN_00017688(0, ((uintptr_t)&rodata_30000) /*=0x30000*/);
    gpio_pin_set_checked(((uintptr_t)&g_gpio0_dev) /*=0x87b60*/, 0x18, 1);
    FUN_00017688(0, ((uintptr_t)&rodata_30000) /*=0x30000*/);
    gpio_pin_set_checked(((uintptr_t)&g_gpio0_dev) /*=0x87b60*/, 0x13, 0);
    FUN_00017688(0, ((uintptr_t)&rodata_30000) /*=0x30000*/);
    gpio_pin_set_checked(((uintptr_t)&g_gpio0_dev) /*=0x87b60*/, 0x15, 0);
    FUN_00017688(0, ((uintptr_t)&rodata_30000) /*=0x30000*/);
    gpio_pin_set_checked(((uintptr_t)&g_gpio0_dev) /*=0x87b60*/, 0x1e, 1);
    FUN_00017688(0, ((uintptr_t)&rodata_30000) /*=0x30000*/);
    gpio_pin_set_checked(((uintptr_t)&g_gpio0_dev) /*=0x87b60*/, 0x17, 0);

    iVar16 = ((uintptr_t)&g_gpio1_dev) /*=0x87b48*/;
    iVar5 = z_device_is_ready(((uintptr_t)&g_gpio1_dev) /*=0x87b48*/);
    if (iVar5 == 0) {
        if (1 < *piVar2) {
            iVar5 = *(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
            uVar15 = "%s(): SW0 GPIO port device not ready\n\n" /*=0x99f81*/;
LAB_b48_1:
            if (iVar5 == 0) {
                DEBUG_PRINT(uVar15, "button_init" /*=0x9a126*/, 0,0,0,0);
            } else {
                debug_print();
            }
        }
    } else {
        iVar6 = FUN_00017688(((uintptr_t)&tbl_889d0) /*=0x889d0*/, ((uintptr_t)&tbl_ffc8) /*=0x10000*/);
        iVar5 = ((uintptr_t)&g_button_irq_cb1) /*=0x20006a10*/;
        if (-1 < iVar6) {
            *(volatile unsigned int *)((uintptr_t)&g_button_irq_cb1_handler) /*=0x20006a14*/ = ((uintptr_t)&tbl_17914) /*=0x1793d*/;
            *(volatile unsigned int *)(iVar5+8) = 0x200;
            pcVar17 = *(void **)(*(int *)(iVar16 + 8) + 0x1c);
            if (pcVar17 == 0) {
                if (1 < *piVar2) {
                    iVar5 = *(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
                    uVar15 = "%s(): Unable to configure SW0 GPIO pin!\n\n" /*=0x99fa8*/;
                    goto LAB_b48_1;
                }
            } else {
                int r = ((int (*)(int,int,int))pcVar17)(iVar16, iVar5, 1);
                if (r < 0) {
                    if (1 < *piVar2) {
                        iVar5 = *(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
                        uVar15 = "%s(): Unable to configure SW0 GPIO pin!\n\n" /*=0x99fa8*/;
                        goto LAB_b48_1;
                    }
                } else {
                    FUN_00017858(((uintptr_t)&tbl_889d0) /*=0x889d0*/, 0x5c00000);
                    if (1 < *piVar2) {
                        if (*(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                            DEBUG_PRINT("%s(): done, pin= %d\n\n" /*=0x99fd2*/, "button_init" /*=0x9a126*/, 9,0,0,0);
                        } else {
                            debug_print();
                        }
                    }
                }
            }
        }
    }

    iVar5 = z_device_is_ready(((uintptr_t)&g_gpio1_dev) /*=0x87b48*/);
    if (iVar5 == 0) {
        if (*piVar2 < 2) goto LAB_c40;
        iVar16 = *(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
        uVar15 = "%s(): SW0 GPIO port device not ready\n\n" /*=0x99f81*/;
        uVar14 = "nfc_gpo_init" /*=0x9a119*/;
    } else {
        iVar6 = FUN_00017688(((uintptr_t)&tbl_889d0) /*=0x889e0*/, ((uintptr_t)&tbl_ffc8) /*=0x10000*/);
        iVar5 = ((uintptr_t)&g_button_irq_cb2) /*=0x20006a04*/;
        if (iVar6 < 0) goto LAB_c40;
        *(volatile unsigned int *)((uintptr_t)&g_button_irq_cb2_handler) /*=0x20006a08*/ = ((uintptr_t)&tbl_17808) /*=0x17819*/;
        *(volatile unsigned int *)(iVar5+8) = 0x400;
        pcVar17 = *(void **)(*(int *)(iVar16 + 8) + 0x1c);
        if (pcVar17 != 0) {
            int r = ((int (*)(int,int,int))pcVar17)(((uintptr_t)&g_gpio1_dev) /*=0x87b48*/, iVar5, 1);
            if (-1 < r) {
                iVar16 = get_board_rev_flag();
                if (iVar16 == 0) {
                    uVar15 = 0x5c00000;
                } else {
                    uVar15 = 0x3c00000;
                }
                FUN_00017858(((uintptr_t)&tbl_889d0) /*=0x889e0*/, uVar15);
                if (1 < *piVar2) {
                    if (*(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                        DEBUG_PRINT("%s(): panel_power_status %d tmr_status %d nfc_lpd_status %d touch_power_status %d\n" /*=0x9a0c6*/, "nfc_gpo_init" /*=0x9a119*/, 10,0,0,0);
                    } else {
                        debug_print();
                    }
                }
                goto LAB_c40;
            }
        }
        if (*piVar2 < 2) goto LAB_c40;
        iVar16 = *(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
        uVar15 = "%s(): Unable to configure SW0 GPIO pin!\n\n" /*=0x99fa8*/;
        uVar14 = "nfc_gpo_init" /*=0x9a119*/;
    }
    if (iVar16 == 0) {
        DEBUG_PRINT(uVar15, uVar14, 0,0,0,0);
    } else {
        debug_print();
    }
LAB_c40:
    bVar4 = (unsigned char)gpio_pin_get_checked(0x1a);
    uVar7 = gpio_pin_get_checked(0x19);
    uVar8 = gpio_pin_get_checked(0x1c);
    uVar9 = gpio_pin_get_checked(0x1b);
    uVar10 = gpio_pin_get_raw_checked(((uintptr_t)&g_gpio0_dev) /*=0x87b60*/, 0x18);
    uVar11 = gpio_pin_get_raw_checked(((uintptr_t)&g_gpio0_dev) /*=0x87b60*/, 0x13);
    uVar12 = gpio_pin_get_raw_checked(((uintptr_t)&g_gpio0_dev) /*=0x87b60*/, 0x15);
    uVar13 = gpio_pin_get_raw_checked(((uintptr_t)&g_gpio0_dev) /*=0x87b60*/, 0x1e);
    if (1 < *piVar2) {
        uVar18 = bVar4;
        if (*(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT("%s(): DEVICE_ID1_PIN: %d, device1_status: %d\n" /*=0x99fe8*/, "get_device_hw_id" /*=0x9a132*/, 0x1a, uVar18,0,0);
        } else {
            debug_print();
        }
        if (1 < *piVar2) {
            uVar7 = uVar7 & 0xff;
            if (*(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): DEVICE_ID2_PIN: %d, device2_status: %d\n" /*=0x9a016*/, "get_device_hw_id" /*=0x9a132*/, 0x19, uVar7,0,0);
            } else {
                debug_print();
            }
            if (1 < *piVar2) {
                uVar8 = uVar8 & 0xff;
                if (*(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    DEBUG_PRINT("%s(): DEVICE_ID3_PIN: %d, device3_status: %d\n" /*=0x9a044*/, "get_device_hw_id" /*=0x9a132*/, 0x1c, uVar8,0,0);
                } else {
                    debug_print();
                }
                if (1 < *piVar2) {
                    uVar9 = uVar9 & 0xff;
                    if (*(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                        DEBUG_PRINT("%s(): DEVICE_ID4_PIN: %d, device4_status: %d\n" /*=0x9a072*/, "get_device_hw_id" /*=0x9a132*/, 0x1b, uVar9,0,0);
                    } else {
                        debug_print();
                    }
                    if (1 < *piVar2) {
                        if (*(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                            DEBUG_PRINT("%s(): device_compat_val: %d %d %d %d\n" /*=0x9a0a0*/, "get_device_hw_id" /*=0x9a132*/, uVar18, uVar7, uVar8, uVar9);
                        } else {
                            debug_print();
                        }
                        if (1 < *piVar2) {
                            if (*(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                DEBUG_PRINT("%s(): panel_power_status %d tmr_status %d nfc_lpd_status %d touch_power_status %d\n" /*=0x9a0c6*/, "get_device_hw_id" /*=0x9a132*/, uVar10 & 0xff, uVar11 & 0xff, uVar12 & 0xff, uVar13 & 0xff);
                            } else {
                                debug_print();
                            }
                        }
                    }
                }
            }
        }
    }
    return bVar4;
}

