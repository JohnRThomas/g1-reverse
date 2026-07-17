/* Reconstructed FUN_000821f4 @ 0x821f4. */
#include <stdint.h>
extern int FUN_000585f0(uintptr_t, unsigned, unsigned);
extern void FUN_00058568(void);
extern unsigned char* FUN_0005f5d0(int,int);
extern void FUN_000821a4(uintptr_t,int);

void FUN_000821f4(uintptr_t owner, int opcode, uint16_t handle,
                  unsigned status)
{
    if (opcode == 0)
        return;

    int item = FUN_000585f0(owner, 1, 4);
    if (item == 0) {
        FUN_00058568();
        return;
    }

    uint8_t *payload = FUN_0005f5d0(item + 0xc, 4);
    *(volatile uint8_t *)(payload + 0) = (uint8_t)opcode;
    *(volatile uint16_t *)(payload + 1) = handle;
    *(volatile uint8_t *)(payload + 3) = (uint8_t)status;
    FUN_000821a4(owner, item);
}
