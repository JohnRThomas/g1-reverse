#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00017a40 @ 0x00017a40
 * public-name: button_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_pin_configure_17688                 <= FUN_00017688 @ 0x00017688
 *   gpio_pin_set_checked                     <= FUN_00017768 @ 0x00017768
 *   gpio_pin_get_raw_checked                 <= FUN_000177c4 @ 0x000177c4
 *   gpio_pin_configure                       <= FUN_00017858 @ 0x00017858
 *   gpio_pin_get_checked                     <= FUN_00017980 @ 0x00017980
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   get_board_rev_flag                       <= FUN_00025284 @ 0x00025284
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 *   rodata_17819                             @ 0x00017819
 *   ADDR_nfc_field_event_signal_sem_THUMB    @ 0x0001793d
 *   rodata_30000                             @ 0x00030000
 *   g_gpio1_dev                              @ 0x00087b48
 *   g_gpio0_dev                              @ 0x00087b60
 *   rodata_88340                             @ 0x00088340
 *   rodata_889d0                             @ 0x000889d0
 *   rodata_889e0                             @ 0x000889e0
 *   rodata_99f81                             @ 0x00099f81
 *   rodata_99fd2                             @ 0x00099fd2
 *   rodata_99fe8                             @ 0x00099fe8
 *   rodata_9a016                             @ 0x0009a016
 *   rodata_9a044                             @ 0x0009a044
 *   rodata_9a072                             @ 0x0009a072
 *   rodata_9a0a0                             @ 0x0009a0a0
 *   rodata_9a0c6                             @ 0x0009a0c6
 *   rodata_9a119                             @ 0x0009a119
 *   rodata_9a126                             @ 0x0009a126
 *   rodata_9a132                             @ 0x0009a132
 *   g_log_level                              @ 0x2000230c
 *   g_button_irq_cb2                         @ 0x20006a04
 *   g_button_irq_cb2_handler                 @ 0x20006a08
 *   g_button_irq_cb1                         @ 0x20006a10
 *   g_button_irq_cb1_handler                 @ 0x20006a14
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed button_init @ 0x17a40  (parity: 200/200 trials, PROVEN) */
#include <stdint.h>
extern int log_message(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern int gpio_pin_configure_17688(unsigned int, unsigned int);
extern void gpio_pin_set_checked(unsigned int, unsigned int, unsigned int);
extern unsigned int gpio_pin_get_raw_checked(unsigned int, unsigned int);
extern void gpio_pin_configure(unsigned int, unsigned int);
extern unsigned int gpio_pin_get_checked(unsigned int);
extern void debug_print(void);
extern int get_board_rev_flag(void);
extern int z_device_is_ready(unsigned int);

unsigned char button_init(void)
{
    volatile int *piVar2 = (volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    unsigned int uVar15 = 0;
    int iVar5, iVar6, iVar16;
    unsigned char bVar4;
    unsigned int uVar7,uVar8,uVar9,uVar10,uVar11,uVar12,uVar13;
    unsigned int uVar14 = 0, uVar18;
    void *pcVar17;
    unsigned int gpio_specs[9][2];
    volatile const unsigned int *spec_data =
        (volatile const unsigned int *)((unsigned long)&rodata_88340) /*=0x88340*/;

    for (unsigned int spec = 0; spec < 9; ++spec) {
        gpio_specs[spec][0] = spec_data[spec * 2];
        gpio_specs[spec][1] = spec_data[spec * 2 + 1];
    }

    gpio_pin_configure_17688((uintptr_t)gpio_specs[0], ((unsigned long)&rodata_10000) /*=0x10000*/);
    gpio_pin_configure_17688((uintptr_t)gpio_specs[1], ((unsigned long)&rodata_10000) /*=0x10000*/);
    gpio_pin_configure_17688((uintptr_t)gpio_specs[2], ((unsigned long)&rodata_10000) /*=0x10000*/);
    gpio_pin_configure_17688((uintptr_t)gpio_specs[3], ((unsigned long)&rodata_10000) /*=0x10000*/);
    gpio_pin_configure_17688((uintptr_t)gpio_specs[4], ((unsigned long)&rodata_30000) /*=0x30000*/);
    gpio_pin_set_checked(((unsigned long)&g_gpio0_dev) /*=0x87b60*/, 0x18, 1);
    gpio_pin_configure_17688((uintptr_t)gpio_specs[5], ((unsigned long)&rodata_30000) /*=0x30000*/);
    gpio_pin_set_checked(((unsigned long)&g_gpio0_dev) /*=0x87b60*/, 0x13, 0);
    gpio_pin_configure_17688((uintptr_t)gpio_specs[6], ((unsigned long)&rodata_30000) /*=0x30000*/);
    gpio_pin_set_checked(((unsigned long)&g_gpio0_dev) /*=0x87b60*/, 0x15, 0);
    gpio_pin_configure_17688((uintptr_t)gpio_specs[7], ((unsigned long)&rodata_30000) /*=0x30000*/);
    gpio_pin_set_checked(((unsigned long)&g_gpio0_dev) /*=0x87b60*/, 0x1e, 1);
    gpio_pin_configure_17688((uintptr_t)gpio_specs[8], ((unsigned long)&rodata_30000) /*=0x30000*/);
    gpio_pin_set_checked(((unsigned long)&g_gpio0_dev) /*=0x87b60*/, 0x17, 0);

    iVar16 = ((unsigned long)&g_gpio1_dev) /*=0x87b48*/;
    iVar5 = z_device_is_ready(((unsigned long)&g_gpio1_dev) /*=0x87b48*/);
    if (iVar5 == 0) {
        if (1 < *piVar2) {
            iVar5 = *(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
            uVar15 = ((unsigned long)&rodata_99f81) /*=0x99f81*/;
LAB_b48_1:
            if (iVar5 == 0) {
                log_message(uVar15, ((unsigned long)&rodata_9a126) /*=0x9a126*/, 0,0,0,0);
            } else {
                debug_print();
            }
        }
    } else {
        iVar6 = gpio_pin_configure_17688(((unsigned long)&rodata_889d0) /*=0x889d0*/, ((unsigned long)&rodata_10000) /*=0x10000*/);
        iVar5 = ((unsigned long)&g_button_irq_cb1) /*=0x20006a10*/;
        if (-1 < iVar6) {
            *(volatile unsigned int *)((unsigned long)&g_button_irq_cb1_handler) /*=0x20006a14*/ = ADDR_nfc_field_event_signal_sem_THUMB /*=0x1793d*/;
            *(volatile unsigned int *)(iVar5+8) = 0x200;
            pcVar17 = *(void **)(*(int *)(iVar16 + 8) + 0x1c);
            if (pcVar17 == 0) {
                if (1 < *piVar2) {
                    iVar5 = *(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                    uVar15 = 0x00099fa8UL;
                    goto LAB_b48_1;
                }
            } else {
                int r = ((int (*)(int,int,int))pcVar17)(iVar16, iVar5, 1);
                if (r < 0) {
                    if (1 < *piVar2) {
                        iVar5 = *(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                        uVar15 = 0x00099fa8UL;
                        goto LAB_b48_1;
                    }
                } else {
                    gpio_pin_configure(((unsigned long)&rodata_889d0) /*=0x889d0*/, 0x5c00000);
                    if (1 < *piVar2) {
                        if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                            log_message(((unsigned long)&rodata_99fd2) /*=0x99fd2*/, ((unsigned long)&rodata_9a126) /*=0x9a126*/, 9,0,0,0);
                        } else {
                            debug_print();
                        }
                    }
                }
            }
        }
    }

    iVar5 = z_device_is_ready(((unsigned long)&g_gpio1_dev) /*=0x87b48*/);
    if (iVar5 == 0) {
        if (*piVar2 < 2) goto LAB_c40;
        iVar16 = *(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        uVar15 = ((unsigned long)&rodata_99f81) /*=0x99f81*/;
        uVar14 = ((unsigned long)&rodata_9a119) /*=0x9a119*/;
    } else {
        iVar6 = gpio_pin_configure_17688(((unsigned long)&rodata_889e0) /*=0x889e0*/, ((unsigned long)&rodata_10000) /*=0x10000*/);
        iVar5 = ((unsigned long)&g_button_irq_cb2) /*=0x20006a04*/;
        if (iVar6 < 0) goto LAB_c40;
        *(volatile unsigned int *)((unsigned long)&g_button_irq_cb2_handler) /*=0x20006a08*/ = ((unsigned long)&rodata_17819) /*=0x17819*/;
        *(volatile unsigned int *)(iVar5+8) = 0x400;
        pcVar17 = *(void **)(*(int *)(iVar16 + 8) + 0x1c);
        if (pcVar17 != 0) {
            int r = ((int (*)(int,int,int))pcVar17)(((unsigned long)&g_gpio1_dev) /*=0x87b48*/, iVar5, 1);
            if (-1 < r) {
                iVar16 = get_board_rev_flag();
                if (iVar16 == 0) {
                    uVar15 = 0x5c00000;
                } else {
                    uVar15 = 0x3c00000;
                }
                gpio_pin_configure(((unsigned long)&rodata_889e0) /*=0x889e0*/, uVar15);
                if (1 < *piVar2) {
                    if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                        log_message(((unsigned long)&rodata_9a0c6) /*=0x9a0c6*/, ((unsigned long)&rodata_9a119) /*=0x9a119*/, 10,0,0,0);
                    } else {
                        debug_print();
                    }
                }
                goto LAB_c40;
            }
        }
        if (*piVar2 < 2) goto LAB_c40;
        iVar16 = *(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        uVar15 = 0x00099fa8UL;
        uVar14 = ((unsigned long)&rodata_9a119) /*=0x9a119*/;
    }
    if (iVar16 == 0) {
        log_message(uVar15, uVar14, 0,0,0,0);
    } else {
        debug_print();
    }
LAB_c40:
    bVar4 = (unsigned char)gpio_pin_get_checked(0x1a);
    uVar7 = gpio_pin_get_checked(0x19);
    uVar8 = gpio_pin_get_checked(0x1c);
    uVar9 = gpio_pin_get_checked(0x1b);
    uVar10 = gpio_pin_get_raw_checked(((unsigned long)&g_gpio0_dev) /*=0x87b60*/, 0x18);
    uVar11 = gpio_pin_get_raw_checked(((unsigned long)&g_gpio0_dev) /*=0x87b60*/, 0x13);
    uVar12 = gpio_pin_get_raw_checked(((unsigned long)&g_gpio0_dev) /*=0x87b60*/, 0x15);
    uVar13 = gpio_pin_get_raw_checked(((unsigned long)&g_gpio0_dev) /*=0x87b60*/, 0x1e);
    if (1 < *piVar2) {
        uVar18 = bVar4;
        if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)&rodata_99fe8) /*=0x99fe8*/, ((unsigned long)&rodata_9a132) /*=0x9a132*/, 0x1a, uVar18,0,0);
        } else {
            debug_print();
        }
        if (1 < *piVar2) {
            uVar7 = uVar7 & 0xff;
            if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)&rodata_9a016) /*=0x9a016*/, ((unsigned long)&rodata_9a132) /*=0x9a132*/, 0x19, uVar7,0,0);
            } else {
                debug_print();
            }
            if (1 < *piVar2) {
                uVar8 = uVar8 & 0xff;
                if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    log_message(((unsigned long)&rodata_9a044) /*=0x9a044*/, ((unsigned long)&rodata_9a132) /*=0x9a132*/, 0x1c, uVar8,0,0);
                } else {
                    debug_print();
                }
                if (1 < *piVar2) {
                    uVar9 = uVar9 & 0xff;
                    if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                        log_message(((unsigned long)&rodata_9a072) /*=0x9a072*/, ((unsigned long)&rodata_9a132) /*=0x9a132*/, 0x1b, uVar9,0,0);
                    } else {
                        debug_print();
                    }
                    if (1 < *piVar2) {
                        if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                            log_message(((unsigned long)&rodata_9a0a0) /*=0x9a0a0*/, ((unsigned long)&rodata_9a132) /*=0x9a132*/, uVar18, uVar7, uVar8, uVar9);
                        } else {
                            debug_print();
                        }
                        if (1 < *piVar2) {
                            if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                log_message(((unsigned long)&rodata_9a0c6) /*=0x9a0c6*/, ((unsigned long)&rodata_9a132) /*=0x9a132*/, uVar10 & 0xff, uVar11 & 0xff, uVar12 & 0xff, uVar13 & 0xff);
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
