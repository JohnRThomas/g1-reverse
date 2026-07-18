/* readable reconstruction; identity: FUN_0100e294 @ 0x0100e294
 * public-name: ble_ext_adv_header_field_get
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   ble_ext_adv_header_field_get             <= FUN_0100e294 @ 0x0100e294
 */
/* net-core ble_ext_adv_header_field_get @ 0x0100e294, exact extent 0xd6.
 * Raw/address backmap: FUN_0100e294@0x0100e294.
 * Field selectors 0..6 address AdvA, TargetA, CTEInfo, ADI, AuxPtr,
 * SyncInfo and TxPower; selector 7 addresses the remaining ACAD bytes.
 */
#include <stddef.h>
#include <stdint.h>
#define ble_ext_adv_header_field_get ble_ext_adv_header_field_get

uint8_t *ble_ext_adv_header_field_get(uint8_t *packet, uint32_t field)
{
    uint32_t header_length = packet[3] & 0x3fu;
    uint32_t flags;
    uint32_t offset = 5u;

    if (header_length == 0u) {
        return NULL;
    }
    flags = packet[4];

    if (field == 0u) return (flags & 0x01u) ? packet + offset : NULL;
    if (flags & 0x01u) offset += 6u;
    if (field == 1u) return (flags & 0x02u) ? packet + offset : NULL;
    if (flags & 0x02u) offset += 6u;
    if (field == 2u) return (flags & 0x04u) ? packet + offset : NULL;
    if (flags & 0x04u) offset += 1u;
    if (field == 3u) return (flags & 0x08u) ? packet + offset : NULL;
    if (flags & 0x08u) offset += 2u;
    if (field == 4u) return (flags & 0x10u) ? packet + offset : NULL;
    if (flags & 0x10u) offset += 3u;
    if (field == 5u) return (flags & 0x20u) ? packet + offset : NULL;
    if (flags & 0x20u) offset += 18u;
    if (field == 6u) return (flags & 0x40u) ? packet + offset : NULL;
    if (flags & 0x40u) offset += 1u;

    if (field != 7u || header_length < offset - 4u) {
        return NULL;
    }
    return packet + offset;
}
