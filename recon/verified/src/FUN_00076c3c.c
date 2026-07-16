/* Reconstructed FUN_00076c3c @ 0x76c3c */
#include <stdint.h>
#include <stddef.h>
extern void FUN_00076b9c(void);
extern void FUN_00076ba8(void);
extern void FUN_00076bcc(void *);
extern void FUN_0005109c(void *);
extern void *FUN_00086b14(void *, uint32_t);
extern void *FUN_00086c78(void *, int, size_t);

void *FUN_00076c3c(uint32_t *error)
{
    FUN_00076b9c();
    uint8_t *root = *(uint8_t **)(uintptr_t)0x0009873c;
    if (*(uint32_t *)(root + 0x18) == 0) FUN_00076bcc(root);
    uint8_t *block = root + 0x48;
    for (;;) {
        int32_t count = *(int32_t *)(block + 4);
        volatile uint8_t *slot = *(uint8_t **)(block + 8);
        while (--count >= 0) {
            if (*(volatile int16_t *)(slot + 0x0c) == 0) {
                *(volatile uint32_t *)(slot + 0x64) = 0;
                *(volatile uint32_t *)(slot + 0x0c) = 0xffff0001;
                FUN_0005109c((void *)(slot + 0x58));
                FUN_00076ba8();
                *(volatile uint32_t *)(slot + 0x00) = 0;
                *(volatile uint32_t *)(slot + 0x18) = 0;
                *(volatile uint32_t *)(slot + 0x04) = 0;
                *(volatile uint32_t *)(slot + 0x08) = 0;
                *(volatile uint32_t *)(slot + 0x10) = 0;
                *(volatile uint32_t *)(slot + 0x14) = 0;
                FUN_00086c78((void *)(slot + 0x5c), 0, 8);
                *(volatile uint32_t *)(slot + 0x34) = 0;
                *(volatile uint32_t *)(slot + 0x38) = 0;
                *(volatile uint32_t *)(slot + 0x48) = 0;
                *(volatile uint32_t *)(slot + 0x4c) = 0;
                return (void *)slot;
            }
            slot += 0x68;
        }
        if (*(uint8_t **)block == 0) {
            void *next = FUN_00086b14(error, 4);
            *(void **)block = next;
            if (!next) { FUN_00076ba8(); *error = 12; return 0; }
        }
        block = *(uint8_t **)block;
    }
}
