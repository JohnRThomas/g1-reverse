/* readable reconstruction; identity: FUN_01019750 @ 0x01019750
 * public-name: FUN_01019750
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   sdc_work_submit                          <= FUN_0100ef88 @ 0x0100ef88
 *   sdc_buffer_payload_get                   <= FUN_010270d2 @ 0x010270d2
 *   sdc_buffer_descriptor_resolve            <= FUN_0102714a @ 0x0102714a
 */
/* net-core FUN_01019750 @ 0x1019750 */
#include <stdint.h>
extern void sdc_assertion_fail(uint32_t, uint32_t);
extern uint32_t FUN_0100a5a0(void);
extern uint32_t FUN_0100a5b4(void);
extern int FUN_0100ca98(uint8_t, void *);
extern void sdc_work_submit(void *, const void *, uint32_t);
extern int FUN_01026d3e(void);
extern int FUN_01026f32(uint32_t, uint16_t, uint32_t);
extern uint8_t *sdc_buffer_payload_get(uint32_t);
extern void sdc_buffer_descriptor_resolve(uint32_t, uint32_t *, uint16_t *);

static void copy_six(uint8_t *destination, const uint8_t *source)
{
    *(uint32_t *)destination = *(const uint32_t *)source;
    *(uint16_t *)(destination + 4) = *(const uint16_t *)(source + 4);
}

void FUN_01019750(const uint8_t *owner, uint32_t kind,
                   const uint8_t *near_address, uint32_t address_kind,
                   uint8_t identity, uint8_t channel, int8_t power)
{
    uint32_t token = FUN_0100a5a0();
    uint32_t handle;
    uint16_t unused;
    uint8_t *entry;

    if (FUN_01026d3e() == 1)
        return;
    sdc_buffer_descriptor_resolve(token, &handle, &unused);
    entry = sdc_buffer_payload_get(handle);

    for (unsigned offset = 0x12; offset <= 0x2a; offset += 4)
        *(uint32_t *)(entry + offset) = 0;
    entry[0x12] = 1;

    switch (kind) {
    case 0: entry[0x1c] = (entry[0x1c] & 0xec) | 0x13; break;
    case 1: entry[0x1c] = (entry[0x1c] & 0xea) | 0x15; break;
    case 2: entry[0x1c] |= 0x10; break;
    case 6: entry[0x1c] = (entry[0x1c] & 0xed) | 0x12; break;
    default:
        sdc_assertion_fail(0x33, 0x314);
        entry[0x1c] = (entry[0x1c] & 0xed) | 0x12;
        break;
    }

    if (identity == UINT8_MAX) {
        entry[0x13] = owner[0x11];
        copy_six(entry + 0x14, *(const uint8_t *const *)(owner + 4));
    } else {
        if (FUN_0100ca98(identity, entry + 0x13) == 0)
            sdc_assertion_fail(0x33, 0xe6);
        entry[0x13] |= 2;
    }

    entry[0x1b] = (uint8_t)power;
    *(uint16_t *)(entry + 0x1e) = 1;
    entry[0x20] = 0xff;
    if (entry[0x1c] & 4) {
        const uint8_t *source = near_address;
        if ((uint32_t)(address_kind - 2) > 1)
            source = *(const uint8_t *const *)(owner + 8);
        copy_six(entry + 0x26, source);
        entry[0x25] = (uint8_t)address_kind;
    } else {
        entry[0x25] = 0xff;
    }
    entry[0x2d] = channel;
    entry[0x2c] = 0x7f;

    token = FUN_0100a5a0();
    if (FUN_01026f32(token, (uint16_t)FUN_0100a5b4(), 1) == 0)
        sdc_assertion_fail(0x33, 0x334);
    entry[8] = 0;
    sdc_work_submit(entry, (const void *)0x01019a9d, 6);
}
