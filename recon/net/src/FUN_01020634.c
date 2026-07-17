/* net-core FUN_01020634 @ 0x1020634  (CFG-directed candidate) */

#include <stdint.h>
extern void sdc_assertion_fail(uint32_t module, uint32_t line) __attribute__((noreturn));
extern void sdc_llcp_note_unsupported_pdu(void);
extern int32_t FUN_010218b4(void);
extern int32_t FUN_01025bbc(void);
extern int32_t FUN_01025bd4(uint32_t operation);
extern void FUN_01025b8c(void);

void FUN_01020634(void)
{
    volatile uint8_t *controller = (volatile uint8_t *)0x210015f0u;
    volatile uint8_t *radio = (volatile uint8_t *)0x4100c000u;
    volatile uint8_t *timer = (volatile uint8_t *)0x41008000u;
    volatile uint8_t *egu = (volatile uint8_t *)0x4100f000u;
    volatile uint8_t *nvic = (volatile uint8_t *)0xe000e100u;

    *(volatile uint32_t *)(radio + 0x548) = 0u;
    *(volatile uint32_t *)(radio + 0x544) = 0u;
    *(volatile uint32_t *)(radio + 0x540) = 0u;
    *(volatile uint32_t *)(radio + 0x54c) = 0u;
    sdc_llcp_note_unsupported_pdu();

    if (*(volatile uint16_t *)(controller + 0x1c) > 0x95u) {
        uint32_t state = (uint32_t)FUN_010218b4();
        if (state + 1u > 1u) {
            sdc_assertion_fail(0x3eu, 0x4fcu);
        }
    }

    if (controller[0x45] != 0u) {
        int32_t result = FUN_01025bbc();
        if (result != 0) {
            sdc_assertion_fail(0x3eu, 0x512u);
        }
        controller[0x45] = 0u;
    }

    if (FUN_01025bd4(0u) != 0) {
        sdc_assertion_fail(0x3eu, 0x515u);
    }

    *(volatile uint32_t *)(egu + 0x508) = 0x1df8u;
    *(volatile uint32_t *)(radio + 0x1c4) = 0u;
    *(volatile uint32_t *)(timer + 0x80) = 0u;
    *(volatile uint32_t *)(timer + 0x84) = 0u;
    *(volatile uint32_t *)(timer + 0x88) = 0u;
    *(volatile uint32_t *)(timer + 0x80) = 0u;
    *(volatile uint32_t *)(timer + 0x84) = 0u;
    *(volatile uint32_t *)(radio + 0xc8) = 0u;
    *(volatile uint32_t *)(radio + 0xc4) = 0u;
    FUN_01025b8c();
    *(volatile uint32_t *)(timer + 0x1a8) = 0u;
    *(volatile uint32_t *)(radio + 0x1c0) = 0u;
    controller[0x0c] = 0u;
    *(volatile uint32_t *)(radio + 0x548) = 0u;
    *(volatile uint64_t *)(controller + 0x20) = 0u;
    *(volatile uint32_t *)(radio + 0x544) = 0u;
    *(volatile uint32_t *)(radio + 0x540) = 0u;
    *(volatile uint32_t *)(radio + 0x54c) = 0u;
    *(volatile uint32_t *)(radio + 0x148) = 0u;
    *(volatile uint32_t *)(radio + 0x144) = 0u;
    *(volatile uint32_t *)(radio + 0x140) = 0u;
    *(volatile uint32_t *)(radio + 0x14c) = 0u;
    *(volatile uint32_t *)(nvic + 0x80) = 0x100u;
    __atomic_thread_fence(__ATOMIC_SEQ_CST);
    __atomic_signal_fence(__ATOMIC_SEQ_CST);
    *(volatile uint32_t *)(nvic + 0x180) = 0x100u;
}
