/* Reconstructed panel_init @ 0x47538. */
#include <stdint.h>

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern void FUN_0007d642(uint32_t a, uint32_t b);
extern void FUN_0007d658(uint32_t a, uint32_t b);
extern void FUN_0007d67e(uint32_t a);
extern void FUN_0007d6ae(uint32_t a);
extern void FUN_0007d74e(void);
extern void FUN_0007d772(uint32_t a);
extern void FUN_0007d77c(uint32_t a);

void panel_init(void)
{
    if (*(volatile int*)0x2000230cUL > 3) {
        if (*(volatile uint32_t*)0x20007554UL == 0) {
            DEBUG_PRINT(0x00099969u, 0x000d741bu);
        } else {
            FUN_00019c70(0x00099969u, 0x000d741bu);
        }
    }
    FUN_0007d74e();
    FUN_0007d77c(6);
    FUN_0007d642(1, 0x10);
    FUN_0007d6ae(0);
    FUN_0007d658(0, 0);
    FUN_0007d658(0, 0x14);
    FUN_0007d658(0x18, 0);
    FUN_0007d658(0x18, 0x14);
    FUN_0007d658(0xc, 10);
    FUN_0007d77c(0x71);
    FUN_0007d77c(0x97);
    FUN_0007d772(1);
    FUN_0007d77c(0x73);
    FUN_0007d77c(0x97);
    FUN_0007d772(1);
    FUN_0007d67e(0xf);
    FUN_0007d642(0x31, 4);
    FUN_0007d77c(0xa3);
    FUN_0007d77c(0x97);
    FUN_0007d772(1);
}
