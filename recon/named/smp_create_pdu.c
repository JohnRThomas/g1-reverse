/* readable reconstruction; identity: FUN_000830b0 @ 0x000830b0
 * public-name: smp_create_pdu
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   att_create_pdu_reserve4                  <= FUN_0008181a @ 0x0008181a
 *   atomic_test_bit                          <= FUN_00082ff6 @ 0x00082ff6
 *   atomic_set_bit                           <= FUN_00083090 @ 0x00083090
 * address symbols (name @ address):
 *   rodata_f0000                             @ 0x000f0000
 */
/* Reconstructed smp_create_pdu @ 0x830b0  (CFG-directed candidate) */
#include <stdint.h>
extern int atomic_test_bit(void *flags, uint32_t bit);
extern void atomic_set_bit(void *flags, uint32_t bit);
extern void *att_create_pdu_reserve4(void *pool, uint32_t reserve, uint32_t timeout_lo, uint32_t timeout_hi);
extern void *net_buf_simple_add(void *buf, uint32_t len);
void *smp_create_pdu(void *smp, uint8_t op) {
    void *flags = (uint8_t *)smp + 4;
    uint32_t timeout_lo = atomic_test_bit(flags, 4u) ? 0u : 0x000f0000u;
    void *buf = att_create_pdu_reserve4(0, 0, timeout_lo, 0);
    if (!buf) {
        atomic_set_bit(flags, 4u);
    } else {
        *(uint8_t *)net_buf_simple_add((uint8_t *)buf + 12, 1u) = op;
    }
    return buf;
}
