/* Reconstructed FUN_0002e594 @ 0x2e594 */
#include <stdint.h>

extern int FUN_0008638c(uint32_t);
extern void DEBUG_PRINT(uint32_t, ...);
extern void FUN_00019c70(void);

struct io_part { void *data; uint32_t length; uint8_t type; };
typedef int (*transfer_fn)(uint32_t, struct io_part *, uint32_t, uint32_t);

int FUN_0002e594(uint8_t request, uint16_t *result)
{
    volatile uint32_t *device_slot = (volatile uint32_t *)0x200023fc;
    uint32_t device = *device_slot;
    uint16_t response = 0;
    if (FUN_0008638c(device) == 0) {
        if (*(volatile int *)0x2000230c > 0) {
            if (*(volatile int *)0x20007554 == 0)
                DEBUG_PRINT(0x000a3af8, 0x000a3d26);
            else
                FUN_00019c70();
        }
        return -19;
    }
    struct { struct io_part tx, rx; } parts = {
        { &request, 1, 0 }, { &response, 2, 7 }
    };
    transfer_fn transfer = *(transfer_fn *)(uintptr_t)(*(uint32_t *)(device + 8) + 8);
    int status = transfer(device, &parts.tx, 2, 0x45);
    if (status < 0) {
        if (*(volatile int *)0x2000230c > 0) {
            if (*(volatile int *)0x20007554 == 0)
                DEBUG_PRINT(0x000a3b17, 0x000a3d26, 0x45);
            else
                FUN_00019c70();
        }
        return -2;
    }
    *result = (uint16_t)((response << 8) | (response >> 8));
    return 0;
}
