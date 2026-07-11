/* Reconstructed FUN_00030754 @ 0x30754 */
#include <stdint.h>

extern int FUN_0003016c(uint32_t);
extern int FUN_00030178(uint32_t, uint32_t);
extern int FUN_000302cc(void);
extern int FUN_000302f8(uint32_t, void *);
extern int FUN_00030340(uint32_t, uint32_t, void *, uint32_t);
extern void *FUN_00076d6c(uint32_t);
extern void FUN_00076d7c(void *);
extern uint32_t FUN_0007cf34(uint32_t, uint32_t, uint32_t);
extern int FUN_0007d05e(void *, uint32_t);
extern void FUN_00086c04(void *, const void *, uint32_t);
extern void FUN_00086c78(void *, int, uint32_t);

#define PHASE (*(volatile uint8_t *)UINT32_C(0x20019dad))

uint32_t FUN_00030754(int mode)
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

    if (FUN_000302cc() != 0)
        return UINT32_MAX;

    if (mode == 0) {
        if (FUN_000302f8(0x1ba8, &scratch) < 0)
            return 0;
        if (scratch == UINT32_C(0x06000007))
            return 0;
    }

    rc = FUN_00030178(0x4408, 0x14);
    if (rc == 0) {
        int polls = 200;
        FUN_0003016c(1);
        for (;;) {
            uint32_t status = FUN_000302f8(0x4410, &scratch);
            if (status != 0)
                break;
            if ((int32_t)(scratch << 2) < 0) {
                range_start = 0;
                range_end = 0;
                scratch = 0;
                if (FUN_000302f8(0x1c30, &range_start) == 0 &&
                    FUN_000302f8(0x1c34, &range_end) == 0 &&
                    FUN_00030178(0xff20, UINT32_C(0x3c00f091)) == 0 &&
                    FUN_00030178(0x4820, 4) == 0 &&
                    FUN_0007d05e(&scratch, 0x7fc) == 0) {
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
                                FUN_0007d05e(&range_start, 0x3ff8) == 0 &&
                                FUN_0007d05e(&range_end, 0x3ffc) == 0 &&
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
            FUN_0003016c(1);
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
            uint8_t *packet = (uint8_t *)FUN_00076d6c(0x108);
            if (packet == 0)
                goto cleanup;
            FUN_00086c78(packet, 1, 0x108);
            *(uint16_t *)(packet + 4) = 0x10;
            *(uint16_t *)packet = 0;
            packet[2] = 0;
            packet[3] = sequence;
            packet[6] = (uint8_t)(address >> 8);
            packet[7] = 0;
            FUN_00086c04(packet + 8,
                         (const void *)(uintptr_t)(UINT32_C(0xf00a29ed) + address),
                         0x100);
            rc = FUN_00030340(1, 2, packet, 0x108);
            if (rc != 0) {
                FUN_00076d7c(packet);
                goto cleanup;
            }
            FUN_00076d7c(packet);
            address += 0x100;
            ++sequence;
        } while (address != UINT32_C(0x10003b00));

        {
            uint8_t *packet = (uint8_t *)FUN_00076d6c(0xa4);
            if (packet != 0) {
                FUN_00086c78(packet + 1, 1, 0xa3);
                *(uint16_t *)packet = 0;
                packet[2] = 0;
                packet[3] = sequence;
                *(uint32_t *)(packet + 4) = UINT32_C(0x003b0010);
                FUN_00086c04(packet + 8, (const void *)UINT32_C(0x000a64ed), 0x9c);
                rc = FUN_00030340(1, 2, packet, 0xa4);
                if (rc != 0) {
                    FUN_00076d7c(packet);
                    goto cleanup;
                }
                FUN_00076d7c(packet);
                PHASE = 6;
                FUN_00030178(0x4444, 0x10000);
                FUN_00030178(0xff20, UINT32_C(0x3c00ffff));
                FUN_000302f8(0x4744, &scratch);
                FUN_00030178(0x4744, scratch & 0xffffffu);
                FUN_00030178(0xff20, UINT32_C(0x3c00f011));
                FUN_00030178(0x4444, 0);
                FUN_0003016c(0x19);
                scratch = 0;
                for (rc = 10; rc >= 0; --rc) {
                    if (FUN_000302f8(0x4410, &scratch) != 0)
                        break;
                    if ((scratch & 1u) != 0)
                        return 0;
                    FUN_0003016c(1);
                }
            }
        }
    }

cleanup:
    rc = FUN_00030178(0xff20, UINT32_C(0x3c00f091));
    if (rc == 0 && FUN_000302f8(0x4748, &saved_4748) == 0 &&
        (saved_4748 == 0 || FUN_00030178(0x4748, 0) == 0) &&
        FUN_000302f8(0x4744, &limit) == 0 &&
        ((limit >> 24) == 0 || FUN_00030178(0x4744, limit & 0xffffffu) == 0) &&
        FUN_00030178(0xff20, UINT32_C(0x3c00f011)) == 0 && mode != 1)
        return UINT32_C(0xfffffffd);
    return UINT32_MAX;
}
