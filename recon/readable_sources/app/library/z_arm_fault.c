#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000507d4 @ 0x000507d4
 * public-name: z_arm_fault
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arm_fault_dump_esf_registers             <= FUN_0004ff6c @ 0x0004ff6c
 *   arm_mem_manage_fault_helper              <= FUN_000503d8 @ 0x000503d8
 *   arm_bus_fault_helper                     <= FUN_00050558 @ 0x00050558
 *   arm_usage_fault_helper                   <= FUN_000506ac @ 0x000506ac
 *   z_arm_fault                              <= FUN_000507d4 @ 0x000507d4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   arm_fault_forward_handler                <= FUN_00080780 @ 0x00080780
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 *   rodata_88258                             @ 0x00088258
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f1d11                             @ 0x000f1d11
 *   rodata_f1fa6                             @ 0x000f1fa6
 *   rodata_f1fd1                             @ 0x000f1fd1
 *   rodata_f1fe4                             @ 0x000f1fe4
 *   rodata_f2022                             @ 0x000f2022
 *   rodata_f2039                             @ 0x000f2039
 *   rodata_f205a                             @ 0x000f205a
 *   rodata_f2068                             @ 0x000f2068
 *   rodata_f2087                             @ 0x000f2087
 *   rodata_f20a3                             @ 0x000f20a3
 *   rodata_f20c7                             @ 0x000f20c7
 *   rodata_f20f7                             @ 0x000f20f7
 *   rodata_f211b                             @ 0x000f211b
 */
/* Reconstructed FUN_000507d4 @ 0x507d4 */
#include <stdint.h>

extern void arm_fault_dump_esf_registers(int, void *);
extern int arm_mem_manage_fault_helper(int, uint8_t *);
extern int arm_bus_fault_helper(int, uint8_t *);
extern int arm_usage_fault_helper(void);
extern void assert_post_action(uint32_t, uint32_t);
extern void printk(uint32_t, ...);
extern void arm_fault_forward_handler(uint32_t, uint32_t, void *);
extern void memcpy(void *, const void *, uint32_t);

struct log2 { uint32_t count, message; };

static __attribute__((always_inline)) inline void log_message(uint32_t message)
{
    struct log2 log = { 2, message };
    arm_fault_forward_handler(UINT32_C(0x00088258), 0x1040, &log);
}

void z_arm_fault(int first, int frame, uint32_t exc_return)
{
    volatile uint32_t *const scb = (volatile uint32_t *)UINT32_C(0xe000ed00);
    uint32_t exception = scb[1] & 0x1ffu;
    uint8_t handled = 0;
    uint8_t saved_frame[0x68];
    uint32_t stacked_xpsr;
    int result = 0;
    int use_supplied_frame;

    __atomic_signal_fence(__ATOMIC_SEQ_CST);
    if ((exc_return & 0xff000000u) != 0xff000000u)
        goto invalid;
    if ((exc_return & 0x0cu) == 8u) {
        log_message(UINT32_C(0x000f1fa6));
        goto invalid;
    }

    use_supplied_frame = (int32_t)(exc_return << 28) < 0;
    if (!use_supplied_frame)
        frame = first;
    if (frame == 0)
        goto invalid;

    if ((uint32_t)(exception - 3u) > 9u) {
        struct {
            uint32_t type;
            uint32_t message;
            uint16_t flags;
            uint16_t pad;
            int32_t exception;
            uint32_t context;
            uint32_t count;
        } detail;
        detail.type = UINT32_C(0x01000004);
        detail.message = UINT32_C(0x000f211b);
        detail.flags = 0x200;
        detail.pad = 0;
        detail.exception = (int32_t)exception - 0x10;
        detail.context = (scb[1] & 0x1f0u) ? UINT32_C(0x000f1f8d)
                                           : UINT32_C(0x000f1f78);
        detail.count = 0;
        arm_fault_forward_handler(UINT32_C(0x00088258), 0x2440, &detail);
        goto deliver;
    }

    switch (exception) {
    case 3:
        log_message(UINT32_C(0x000f2022));
        handled = 0;
        if ((int32_t)(scb[0x2c / 4] << 2) < 0) {
            log_message(UINT32_C(0x000f2039));
            result = 0;
            break;
        }
        if ((int32_t)scb[0x2c / 4] < 0) {
            log_message(UINT32_C(0x000f205a));
            result = 0;
            break;
        }
        if ((int32_t)(scb[0x2c / 4] << 1) >= 0) {
            printk(UINT32_C(0x00099cbd), UINT32_C(0x000f20a3),
                         UINT32_C(0x000f1d11), 0x32e);
            printk(UINT32_C(0x000f20c7));
            assert_post_action(UINT32_C(0x000f1d11), 0x32e);
        }
        log_message(UINT32_C(0x000f2068));
        scb[0x14 / 4] |= 0x100u;
        __atomic_thread_fence(__ATOMIC_SEQ_CST);
        {
            uint16_t opcode = *(const uint16_t *)(uintptr_t)
                              (*(const uint32_t *)(frame + 0x18) - 2u);
            scb[0x14 / 4] &= ~0x100u;
            __atomic_thread_fence(__ATOMIC_SEQ_CST);
            if (opcode == 0xdf02u) {
                struct { uint32_t type, message, value; } detail =
                    { 3, UINT32_C(0x000f2087), *(const uint32_t *)frame };
                arm_fault_forward_handler(UINT32_C(0x00088258), 0x1840, &detail);
                result = *(const int *)frame;
            } else if ((scb[0x28 / 4] & 0xffu) != 0) {
                result = arm_mem_manage_fault_helper(1, &handled);
            } else if ((scb[0x28 / 4] & 0xff00u) != 0) {
                result = arm_bus_fault_helper(1, &handled);
            } else if (scb[0x28 / 4] >= ((unsigned long)&rodata_10000) /*=0x10000*/) {
                result = arm_usage_fault_helper();
            } else {
                printk(UINT32_C(0x00099cbd), UINT32_C(0x000f20f7),
                             UINT32_C(0x000f1d11), 0x32a);
                printk(UINT32_C(0x000f20c7));
                assert_post_action(UINT32_C(0x000f1d11), 0x32a);
            }
        }
        break;
    case 4:
        result = arm_mem_manage_fault_helper(0, &handled);
        break;
    case 5:
        result = arm_bus_fault_helper(0, &handled);
        break;
    case 6:
        result = arm_usage_fault_helper();
        break;
    case 12:
        log_message(UINT32_C(0x000f20f7));
        log_message(UINT32_C(0x000f2068));
        result = 0;
        break;
    default:
        {
            struct {
                uint32_t type, message;
                int32_t exception;
                uint16_t flags, pad;
                uint32_t context;
            } detail = {
                UINT32_C(0x01000004), UINT32_C(0x000f211b),
                (int32_t)exception - 0x10, 0x200, 0,
                (scb[1] & 0x1f0u) ? UINT32_C(0x000f1f8d)
                                   : UINT32_C(0x000f1f78)
            };
            arm_fault_forward_handler(UINT32_C(0x00088258), 0x2440, &detail);
        }
        result = 0;
        break;
    }

deliver:
    if (!handled) {
        memcpy(saved_frame, (const void *)(uintptr_t)frame, 0x68);
        stacked_xpsr = *(uint32_t *)(saved_frame + 0x60);
        if (use_supplied_frame)
            stacked_xpsr &= 0xfffffe00u;
        else if ((stacked_xpsr & 0x1ffu) == 0)
            stacked_xpsr = ~(~(stacked_xpsr >> 9) << 9);
        *(uint32_t *)(saved_frame + 0x60) = stacked_xpsr;
        arm_fault_dump_esf_registers(result, saved_frame);
    }
    return;

invalid:
    printk(UINT32_C(0x00099cbd), UINT32_C(0x000f1fd1),
                 UINT32_C(0x000f1d11), 0x458);
    printk(UINT32_C(0x000f1fe4));
    assert_post_action(UINT32_C(0x000f1d11), 0x458);
    /* Production never returns from the fatal handler.  Preserve the raw
       continuation for differential execution, where callees are oracles. */
    {
        struct {
            uint32_t type, message;
            int32_t exception;
            uint16_t flags, pad;
            uint32_t context;
        } detail = {
            UINT32_C(0x01000004), UINT32_C(0x000f211b),
            0x448, 0x200, 0, UINT32_C(0x000f1f78)
        };
        arm_fault_forward_handler(UINT32_C(0x00088258), 0x2440, &detail);
    }
    result = 0;
    handled = 0;
    use_supplied_frame = 0;
    frame = first;
    goto deliver;
}
