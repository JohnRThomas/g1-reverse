/* Reconstructed FUN_0004e98c @ 0x4e98c, exact code extent 16 bytes. */
#include <stdint.h>

extern uint32_t FUN_0004e8c0(uint32_t index, uint32_t a1,
                            uint32_t a2, uint32_t a3);

uint32_t FUN_0004e98c(uint32_t index, uint32_t a1, uint32_t a2, uint32_t a3,
                      uint32_t a4, uint32_t a5, uint32_t a6, uint32_t a7)
{
    if (index > 2u) {
        (void)a4; (void)a5; (void)a6; (void)a7;
        return FUN_0004e8c0(index, a1, a2, a3);
    }
    return *(const uint8_t *)(0x000f1590u + index);
}
