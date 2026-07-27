/* Full ABI-faithful reconstruction of FUN_0004d594 @ 0x4d594 (220 bytes). */
#include <stdint.h>

extern uint32_t FUN_0004d56c(void);
extern void g1_recon_z_log_msg_free(uint32_t item);
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(uintptr_t, uint32_t);
extern uint64_t thunk_FUN_00074f68(void);
extern void FUN_0004d4a8(uint32_t low, uint32_t high);
extern int g1_recon_z_log_msg_pending(void);

struct listener_entry {
    void (**vtable)(struct listener_entry *, uint32_t);
    const uint8_t *state;
    uint32_t reserved[2];
};

int FUN_0004d594(void)
{
    if (*(volatile uint8_t *)0x2001d44bu == 0)
        return 0;

    uint32_t item = FUN_0004d56c();
    if (item != 0) {
        __atomic_sub_fetch((uint32_t *)0x2000a0d8u, 1, __ATOMIC_ACQ_REL);

        struct listener_entry *entry = (struct listener_entry *)0x000882a0u;
        struct listener_entry *end = (struct listener_entry *)0x000882b0u;
        while (entry < end) {
            if (end < entry) {
                FUN_0007e2fa(0x00099cbdu, 0x000f0cffu,
                             0x000f0caeu, 0x1c5u);
                FUN_0007e2fa(0x000f0d20u);
                FUN_0007e2ec(0x000f0caeu, 0x1c5u);
            }
            if (entry->state[5] != 0)
                (*entry->vtable)(entry, item);
            ++entry;
        }
        g1_recon_z_log_msg_free(item);
    }

    volatile uint64_t *deadline = (volatile uint64_t *)0x200056a0u;
    if (*(volatile int32_t *)0x2000a0d4u > 0) {
        uint64_t now = (thunk_FUN_00074f68() * UINT64_C(1000)) >> 15;
        uint64_t elapsed = now - *deadline;
        if (elapsed >= UINT64_C(1001))
            FUN_0004d4a8((uint32_t)elapsed, (uint32_t)(elapsed >> 32));
    }
    *deadline += UINT64_C(1000);

    return g1_recon_z_log_msg_pending();
}
