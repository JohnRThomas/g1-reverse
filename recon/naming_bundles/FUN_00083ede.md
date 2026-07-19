### FUN_00083ede  @ 0x00083ede  (size=358)

callers (3): FUN_000838dc, FUN_00083cde, FUN_00084b14
callees (1): FUN_00061f64

```c
/* readable reconstruction; identity: FUN_00083ede @ 0x00083ede
 * public-name: FUN_00083ede
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_00083ede @ 0x83ede. */
#include <stdint.h>

extern uintptr_t FUN_00061f64(uint32_t *channel_index);

static void write_channel_mask(uint32_t *channel_index, unsigned offset)
{
    uintptr_t channel_state = FUN_00061f64(channel_index);
    *(volatile uint32_t *)(channel_state + offset) =
        1u << (channel_index[0] & 0xffu);
}

int FUN_00083ede(const uint32_t *records, unsigned record_count,
                 uintptr_t device)
{
    uint32_t channel_index[2];

    for (unsigned index = 0; index < record_count; ++index) {
        uint32_t encoded = records[index];
        uint32_t channel = encoded & 0x7fu;
        unsigned kind = encoded >> 16;
        unsigned submode = (encoded >> 9) & 0x0fu;
        unsigned option_bit = 0;
        unsigned enabled_bit = 0;
        int mask_offset = -1;

        if (channel == 0x7fu) {
            channel = UINT32_MAX;
        }
        channel_index[0] = channel;

        switch (kind) {
        case 0x00:
            *(volatile uint32_t *)(device + 0x50c) = channel;
            mask_offset = 8;
            option_bit = 1;
            enabled_bit = 1;
            break;
        case 0x01:
            *(volatile uint32_t *)(device + 0x514) = channel;
            break;
        case 0x02:
            *(volatile uint32_t *)(device + 0x508) = channel;
            mask_offset = 8;
            option_bit = 1;
            enabled_bit = 1;
            break;
        case 0x03:
            *(volatile uint32_t *)(device + 0x510) = channel;
            break;
        case 0x0b:
            *(volatile uint32_t *)(device + 0x508) = channel;
            if (submode == 0) {
                submode = 6;
            }
            break;
        case 0x0c:
            *(volatile uint32_t *)(device + 0x50c) = channel;
            if (submode == 0) {
                submode = 6;
            }
            break;
        case 0x14:
            *(volatile uint32_t *)(device + 0x540) = channel;
            mask_offset = 12;
            option_bit = 1;
            enabled_bit = 1;
            break;
        case 0x15:
            *(volatile uint32_t *)(device + 0x544) = channel;
            break;
        case 0x16:
            *(volatile uint32_t *)(device + 0x560) = channel;
            mask_offset = (encoded & 0x4000u) ? 8 : 12;
            option_bit = 1;
            enabled_bit = 1;
            break;
        case 0x17:
            *(volatile uint32_t *)(device + 0x564) = channel;
            mask_offset = (encoded & 0x4000u) ? 8 : 12;
            option_bit = 1;
            enabled_bit = 1;
            break;
        case 0x18:
            *(volatile uint32_t *)(device + 0x568) = channel;
            mask_offset = (encoded & 0x4000u) ? 8 : 12;
            option_bit = 1;
            enabled_bit = 1;
            break;
        case 0x19:
            *(volatile uint32_t *)(device + 0x56c) = channel;
            mask_offset = (encoded & 0x4000u) ? 8 : 12;
            option_bit = 1;
            enabled_bit = 1;
            break;
        case 0x1d:
            *(volatile uint32_t *)(device + 0x524) = channel;
            enabled_bit = 1;
            break;
        case 0x1e:
            *(volatile uint32_t *)(device + 0x528) = channel;
            mask_offset = 8;
            option_bit = 1;
            enabled_bit = 1;
            break;
        case 0x1f:
            *(volatile uint32_t *)(device + 0x530) = channel;
            enabled_bit = 1;
            break;
        case 0x20:
            *(volatile uint32_t *)(device + 0x534) = channel;
            enabled_bit = 1;
            break;
        case 0x21:
            *(volatile uint32_t *)(device + 0x538) = channel;
            enabled_bit = 1;
            break;
        case 0x22:
            *(volatile uint32_t *)(device + 0x53c) = channel;
            enabled_bit = 1;
            break;
        default:
            return -0x86;
        }

        if (channel == UINT32_MAX) {
            continue;
        }
        if (mask_offset >= 0) {
            write_channel_mask(channel_index, (unsigned)mask_offset);
        }

        encoded = records[index];
        if ((encoded & 0x2000u) != 0) {
            option_bit = 0;
            enabled_bit = 1;
        }
        channel_index[0] = channel;
        uintptr_t channel_state = FUN_00061f64(channel_index) +
                                  channel_index[0] * sizeof(uint32_t);
        volatile uint32_t *configuration =
            (volatile uint32_t *)(channel_state + 0x200);
        uint32_t preserved = *configuration & 0xfffcf0f0u;
        *configuration = preserved | (submode << 8) |
                         (((encoded >> 7) & 3u) << 2) |
                         option_bit | (enabled_bit << 1);
    }
    return 0;
}
```