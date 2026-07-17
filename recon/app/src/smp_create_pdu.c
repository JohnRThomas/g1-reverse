/* Reconstructed smp_create_pdu @ 0x830b0  (CFG-directed candidate) */
#include <stdint.h>
extern int FUN_00082ff6(void *flags, uint32_t bit);
extern void FUN_00083090(void *flags, uint32_t bit);
extern void *FUN_0008181a(void *pool, uint32_t reserve, uint32_t timeout_lo, uint32_t timeout_hi);
extern void *FUN_0005f5d0(void *buf, uint32_t len);
void *smp_create_pdu(void *smp, uint8_t op) {
    void *flags = (uint8_t *)smp + 4;
    uint32_t timeout_lo = FUN_00082ff6(flags, 4u) ? 0u : 0x000f0000u;
    void *buf = FUN_0008181a(0, 0, timeout_lo, 0);
    if (!buf) {
        FUN_00083090(flags, 4u);
    } else {
        *(uint8_t *)FUN_0005f5d0((uint8_t *)buf + 12, 1u) = op;
    }
    return buf;
}
