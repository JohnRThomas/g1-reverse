/* net-core FUN_01026bfe @ 0x1026bfe  (CFG-directed candidate) */
/* CPUNET 0x01026bfe, true executable extent 0x96. Raw backmap: FUN_01026bfe. */
#include <stdint.h>

extern void sdc_assertion_fail(uint32_t domain, uint32_t line); /* FUN_01008d00 */
extern void controller_packed_cursor_advance(void *owner, void *cursor); /* FUN_0100951c */

uint32_t FUN_01026bfe(uint8_t *owner, uint16_t **completed)
{
    uint16_t *record = (uint16_t *)(owner + 0x18 +
                                   (*(uint16_t *)(owner + 4) & 0x7fffu));
    *completed = 0;
    if (*(uint16_t *)(owner + 0x0e) == 0u) {
        return 0u;
    }
    *(uint16_t *)(owner + 0x0a) = (uint16_t)(*(uint16_t *)(owner + 0x0a) +
                                             *(uint16_t *)(owner + 0x0e));
    if (*(uint16_t *)(owner + 0x0a) > *record) {
        sdc_assertion_fail(0x14u, 0x151u);
    }
    if (*(uint16_t *)(owner + 0x0a) == *record) {
        controller_packed_cursor_advance(owner, owner + 4);
        *(uint16_t *)(owner + 0x0a) = 0u;
        *completed = record;
    }
    *(uint16_t *)(owner + 0x0e) = 0u;
    return 1u;
}
