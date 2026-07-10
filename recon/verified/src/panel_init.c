/* Reconstructed panel_init @ 0x47538  (parity: 300/300 trials, PROVEN) */

typedef unsigned int uint32_t;

extern void DEBUG_PRINT(uint32_t a, uint32_t b, uint32_t c);
extern void FUN_00019c70(void);
extern void FUN_0007d642(uint32_t a, uint32_t b);
extern void FUN_0007d658(uint32_t a, uint32_t b);
extern void FUN_0007d67e(uint32_t a);
extern void FUN_0007d6ae(uint32_t a);
extern void FUN_0007d74e(void);
extern void FUN_0007d772(uint32_t a);
extern void FUN_0007d77c(uint32_t a);

void panel_init(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
    if (*(volatile int*)0x2000230cUL > 3) {
        if (*(volatile uint32_t*)0x20007554UL == 0) {
            DEBUG_PRINT(0x99969UL, 0xd741bUL, 0);
        } else {
            FUN_00019c70();
        }
    }
    FUN_0007d74e();
    FUN_0007d77c(6);
    FUN_0007d642(1,0x10);
    FUN_0007d6ae(0);
    FUN_0007d658(0,0);
    FUN_0007d658(0,0x14);
    FUN_0007d658(0x18,0);
    FUN_0007d658(0x18,0x14);
    FUN_0007d658(0xc,10);
    FUN_0007d77c(0x71);
    FUN_0007d77c(0x97);
    FUN_0007d772(1);
    FUN_0007d77c(0x73);
    FUN_0007d77c(0x97);
    FUN_0007d772(1);
    FUN_0007d67e(0xf);
    FUN_0007d642(0x31,4);
    FUN_0007d77c(0xa3);
    FUN_0007d77c(0x97);
    FUN_0007d772(1);
}

