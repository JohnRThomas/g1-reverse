/* Reconstructed FUN_000227d0 @ 0x227d0. */
#include <stdint.h>

extern void DEBUG_PRINT(uint32_t format, ...);
extern void FUN_00019c70(uint32_t format, ...);
extern int FUN_00022658(const void *source, void *destination, int count);

int FUN_000227d0(const uint8_t *source, uint8_t *destination,
                 uint32_t byte_count)
{
    uint32_t blocks = ((byte_count >> 12) + 1) & 0xff;
    int final_block = (int)blocks - 1;
    int final_count = (int16_t)(byte_count - ((uint32_t)final_block << 12));
    unsigned int block = 0;
    int total = 0;

    if (*(volatile int *)0x20007554u == 0)
        DEBUG_PRINT(0x0009e3db, byte_count);
    else
        FUN_00019c70(0x0009e3db, byte_count);

    while ((uint8_t)block < blocks) {
        int count = final_block <= (int)block ? final_count : 0x1000;
        total += FUN_00022658(source + block * 0x1000,
                             destination + block * 0x1000, count);
        ++block;
    }
    return total;
}
