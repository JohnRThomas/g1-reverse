/* readable reconstruction; identity: FUN_010199f4 @ 0x010199f4
 * public-name: FUN_010199f4
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010199f4 @ 0x10199f4  (CFG-directed candidate) */

#include <stdint.h>
extern uint32_t FUN_0100a5a0(void);
extern uint8_t *sdc_buffer_payload_get(uint32_t) __asm__("FUN_010270d2");
extern void sdc_buffer_descriptor_resolve(uint32_t, uint32_t *, uint8_t *) __asm__("FUN_0102714a");
uint32_t FUN_010199f4(uint8_t *entry, uint8_t *descriptor, uint32_t type,
                      uint32_t flag, uint8_t features, uint8_t mode)
{
    if (mode == 0) {
        if (type == 1) {
            if (flag != 0) return flag;
            return features == 2 ? 0u : 1u;
        }
        if (type == 0) {
            if ((features & 0x0cu) == 0) return 0;
            return (descriptor[1] >> 4) & 1u;
        }
        return 1;
    }
    if (mode != 1)
        return mode == 2 ? flag : (flag | 1u);
    if (type == 1)
        return entry[0x0c] == 2;
    if (type == 2)
        return 0;
    if (type != 0)
        return 1;
    uint32_t resolved;
    uint8_t metadata[2];
    sdc_buffer_descriptor_resolve(FUN_0100a5a0(), &resolved, metadata);
    uint8_t *payload = sdc_buffer_payload_get(resolved);
    return payload[flag == 0 ? 0x13 : 0x25] == 0xff ? 0u : 1u;
}
