/* Reconstructed put_whitelist_app_from_app @ 0x35688  (parity: 300/300 trials, PROVEN) */

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef void (*fn2_t)(uint32_t, uint32_t);

extern void DEBUG_PRINT(uint32_t a, uint32_t b, uint32_t c);
extern void FUN_00019c70(void);
extern uint32_t FUN_00019cd0(uint32_t a, uint32_t b, uint32_t c);
extern uint32_t FUN_00034dbc(uint32_t a);
extern uint32_t FUN_00035050(uint32_t a);
extern uint32_t FUN_00035608(void);
extern uint32_t FUN_00076d6c(uint32_t a);
extern void FUN_00076d7c(uint32_t a);
extern void FUN_00086c78(uint32_t a, uint32_t b, uint32_t c);

void put_whitelist_app_from_app(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4, uint32_t param_5)
{
    volatile uint32_t *piVar1 = (volatile uint32_t*)0x20009fbcUL;
    uint32_t iVar2;
    uint32_t format_string;

    if (*piVar1 == 0) {
        iVar2 = FUN_00076d6c(0x1800);
        *piVar1 = iVar2;
        if (iVar2 == 0) {
            if (*(volatile uint32_t*)0x20007554UL == 0) {
                DEBUG_PRINT(0x000a7c9cUL, 0x000a8a6fUL, 0x1caUL);
            } else {
                FUN_00019c70();
            }
        } else {
            FUN_00086c78(iVar2, 0, 0x1800);
        }
    }
    if (*piVar1 == 0) goto LAB_call;

    iVar2 = FUN_00019cd0(*piVar1, param_3, param_4);
    *(uint8_t*)(param_5 + 1) = (uint8_t)iVar2;
    if (iVar2 != 0xc9) goto LAB_call;

    iVar2 = FUN_00035050(*piVar1);
    if (iVar2 == 0) {
        iVar2 = FUN_00034dbc(*piVar1);
        if (iVar2 == 0) {
            iVar2 = *(volatile uint32_t*)0x20007554UL;
            format_string = 0x000a89e8UL;
        } else {
            iVar2 = FUN_00035608();
            if (iVar2 == 0) goto LAB_cleanup;
            iVar2 = *(volatile uint32_t*)0x20007554UL;
            format_string = 0x000a89c8UL;
        }
        if (iVar2 == 0) {
            DEBUG_PRINT(format_string, 0, 0);
        } else {
            FUN_00019c70();
        }
        *(uint8_t*)(param_5 + 1) = 0xca;
    }

LAB_cleanup:
    FUN_00076d7c(*piVar1);
    *piVar1 = 0;
LAB_call:
    ((fn2_t)(*(uint32_t*)(param_1 + 0xc)))(param_5, 2);
}

