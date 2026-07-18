/* readable reconstruction; identity: FUN_00030754 @ 0x00030754
 * public-name: flash_firmware_update_transfer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   attr_store_retry_delay                   <= FUN_0003016c @ 0x0003016c
 *   attr_store_set                           <= FUN_00030178 @ 0x00030178
 *   verify_image_checksum                    <= FUN_000302cc @ 0x000302cc
 *   attr_store_get                           <= FUN_000302f8 @ 0x000302f8
 *   flash_firmware_update_transfer           <= FUN_00030754 @ 0x00030754
 *   malloc                                   <= FUN_00076d6c @ 0x00076d6c
 *   free                                     <= FUN_00076d7c @ 0x00076d7c
 *   attr_configure_mode3_readback            <= FUN_0007d05e @ 0x0007d05e
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_ff20                              @ 0x0000ff20
 *   rodata_10000                             @ 0x00010000
 *   rodata_a49ed                             @ 0x000a49ed
 *   rodata_a64ed                             @ 0x000a64ed
 *   g_pt_nfc_link_busy                       @ 0x20019dad
 */
/* Reconstructed FUN_00030754 @ 0x30754 */
#include <stdint.h>

extern int attr_store_retry_delay(uint32_t);
extern int attr_store_set(uint32_t, uint32_t);
extern int verify_image_checksum(void);
extern int attr_store_get(uint32_t, void *);
extern int FUN_00030340(uint32_t, uint32_t, void *, uint32_t);
extern void *malloc(uint32_t);
extern void free(void *);
extern uint32_t FUN_0007cf34(uint32_t, uint32_t, uint32_t);
extern int attr_configure_mode3_readback(void *, uint32_t);
extern void memcpy(void *, const void *, uint32_t);
extern void memset_bytes(void *, int, uint32_t);

#define PHASE (*(volatile uint8_t *)UINT32_C(0x20019dad))

uint32_t flash_firmware_update_transfer(int mode)
{
    uint32_t limit = 0;
    uint32_t device_word = 0;
    int saved_4748 = 0;
    uint32_t range_start = 0;
    uint32_t range_end = 0;
    uint32_t scratch = 0;
    uint32_t address;
    uint32_t range_limit;
    int rc;

    if (verify_image_checksum() != 0)
        return UINT32_MAX;

    if (mode == 0) {
        if (attr_store_get(0x1ba8, &scratch) < 0)
            return 0;
        if (scratch == UINT32_C(0x06000007))
            return 0;
    }

    rc = attr_store_set(0x4408, 0x14);
    if (rc == 0) {
        int polls = 200;
        attr_store_retry_delay(1);
        for (;;) {
            uint32_t status = attr_store_get(0x4410, &scratch);
            if (status != 0)
                break;
            if ((int32_t)(scratch << 2) < 0) {
                range_start = 0;
                range_end = 0;
                scratch = 0;
                if (attr_store_get(0x1c30, &range_start) == 0 &&
                    attr_store_get(0x1c34, &range_end) == 0 &&
                    attr_store_set(0xff20, UINT32_C(0x3c00f091)) == 0 &&
                    attr_store_set(0x4820, 4) == 0 &&
                    attr_configure_mode3_readback(&scratch, 0x7fc) == 0) {
                    uint32_t identity = FUN_0007cf34(UINT32_C(0x000a49ed),
                                                     0x1b9c, 0x37f8);
                    device_word = __builtin_bswap32(identity);
                    PHASE = 1;
                    if (FUN_00030340(1, 1, 0, 0) == 0) {
                        scratch = UINT32_C(0x803f0010);
                        PHASE = 2;
                        if (FUN_00030340(2, 2, &scratch, 4) == 0) {
                            PHASE = 4;
                            uint32_t command[4] = {
                                0, UINT32_C(0xf83f0010),
                                UINT32_C(0x22202220), device_word
                            };
                            range_start = 0;
                            range_end = 0;
                            if (FUN_00030340(1, 2, command, 0x10) == 0 &&
                                attr_configure_mode3_readback(&range_start, 0x3ff8) == 0 &&
                                attr_configure_mode3_readback(&range_end, 0x3ffc) == 0 &&
                                range_start == UINT32_C(0x20222022) &&
                                range_end == __builtin_bswap32(device_word)) {
                                address = UINT32_C(0x10002000);
                                range_limit = UINT32_C(0x10003f80);
                                goto program_ranges;
                            }
                        }
                    }
                }
                break;
            }
            attr_store_retry_delay(1);
            if (polls-- == 0)
                break;
        }
    }
    goto cleanup;

program_ranges:
    do {
        scratch = ((((address & 0xffu) << 8) | ((address >> 8) & 0xffu)) << 16) |
                  UINT32_C(0x10);
        PHASE = 2;
        rc = FUN_00030340(2, 2, &scratch, 4);
        if (rc != 0)
            goto cleanup;
        address += 0x80;
    } while (address != range_limit);

    {
        uint8_t sequence = 1;
        PHASE = 3;
        address = UINT32_C(0x10002000);
        do {
            uint8_t *packet = (uint8_t *)malloc(0x108);
            if (packet == 0)
                goto cleanup;
            memset_bytes(packet, 1, 0x108);
            *(uint16_t *)(packet + 4) = 0x10;
            *(uint16_t *)packet = 0;
            packet[2] = 0;
            packet[3] = sequence;
            packet[6] = (uint8_t)(address >> 8);
            packet[7] = 0;
            memcpy(packet + 8,
                         (const void *)(uintptr_t)(UINT32_C(0xf00a29ed) + address),
                         0x100);
            rc = FUN_00030340(1, 2, packet, 0x108);
            if (rc != 0) {
                free(packet);
                goto cleanup;
            }
            free(packet);
            address += 0x100;
            ++sequence;
        } while (address != UINT32_C(0x10003b00));

        {
            uint8_t *packet = (uint8_t *)malloc(0xa4);
            if (packet != 0) {
                memset_bytes(packet + 1, 1, 0xa3);
                *(uint16_t *)packet = 0;
                packet[2] = 0;
                packet[3] = sequence;
                *(uint32_t *)(packet + 4) = UINT32_C(0x003b0010);
                memcpy(packet + 8, (const void *)UINT32_C(0x000a64ed), 0x9c);
                rc = FUN_00030340(1, 2, packet, 0xa4);
                if (rc != 0) {
                    free(packet);
                    goto cleanup;
                }
                free(packet);
                PHASE = 6;
                attr_store_set(0x4444, 0x10000);
                attr_store_set(0xff20, UINT32_C(0x3c00ffff));
                attr_store_get(0x4744, &scratch);
                attr_store_set(0x4744, scratch & 0xffffffu);
                attr_store_set(0xff20, UINT32_C(0x3c00f011));
                attr_store_set(0x4444, 0);
                attr_store_retry_delay(0x19);
                scratch = 0;
                for (rc = 10; rc >= 0; --rc) {
                    if (attr_store_get(0x4410, &scratch) != 0)
                        break;
                    if ((scratch & 1u) != 0)
                        return 0;
                    attr_store_retry_delay(1);
                }
            }
        }
    }

cleanup:
    rc = attr_store_set(0xff20, UINT32_C(0x3c00f091));
    if (rc == 0 && attr_store_get(0x4748, &saved_4748) == 0 &&
        (saved_4748 == 0 || attr_store_set(0x4748, 0) == 0) &&
        attr_store_get(0x4744, &limit) == 0 &&
        ((limit >> 24) == 0 || attr_store_set(0x4744, limit & 0xffffffu) == 0) &&
        attr_store_set(0xff20, UINT32_C(0x3c00f011)) == 0 && mode != 1)
        return UINT32_C(0xfffffffd);
    return UINT32_MAX;
}
