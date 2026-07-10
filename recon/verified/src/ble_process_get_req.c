/* Reconstructed ble_process_get_req @ 0x1a064  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <stddef.h>

extern void DEBUG_PRINT();
extern int  FUN_00016568();
extern int  FUN_000167a8();
extern void FUN_00019b54();
extern void FUN_00019c70();
extern void FUN_00033abc();
extern void FUN_00035498();
extern void FUN_00048998();
extern void FUN_0004a424();
extern int  FUN_0007ce00();
extern void FUN_00086c04();
extern void FUN_00086c1e();
extern void FUN_00086c78();
extern void FUN_00086fee();

#define LVL_A (*(volatile int32_t*)0x2000230cUL)
#define LVL_B (*(volatile int32_t*)0x20007554UL)
#define G_20018462 (*(volatile uint8_t*)0x20018462UL)

typedef void (*fp_t)(void);

void ble_process_get_req(uint8_t *param_1, uint8_t *packet, uint8_t *param_3)
{
    uint8_t switchval;
    int32_t iVar9;
    uint8_t uVar1;

    FUN_00086c78();
    *(*(volatile uint32_t **)(param_1 + 0x10)) = *(volatile uint32_t *)packet;
    *(volatile uint32_t *)(param_1 + 0x14) = (uint32_t)*(volatile uint16_t *)(packet + 2);
    switchval = *packet;

    switch (switchval) {
    case 0x29:
        FUN_00019b54();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        break;
    case 0x2a:
        FUN_00019b54();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        break;
    case 0x2b:
        FUN_00019b54();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        break;
    case 0x2c:
        if (*(volatile int8_t *)(param_3 + 1) == 1) {
            *(volatile uint8_t *)(param_1 + 0x8ec) = 0;
        } else if (*(volatile int8_t *)(param_3 + 1) == 2) {
            *(volatile uint8_t *)(param_1 + 0x8ec) = 1;
        }
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        FUN_00019b54();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        break;
    case 0x2d:
        FUN_00019b54();
        FUN_0004a424();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        break;
    case 0x2e:
        FUN_00035498();
        return;
    case 0x32:
        FUN_00019b54();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        break;
    case 0x33:
        FUN_00019b54();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        break;
    case 0x34:
        FUN_00019b54();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        break;
    case 0x35:
        FUN_00019b54();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        break;
    case 0x36:
        FUN_00033abc();
        return;
    case 0x37:
        FUN_00019b54();
        break;
    case 0x38:
        if (0 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        break;
    case 0x39:
        if (*(volatile int16_t *)(param_3 + 1) == *(volatile int16_t *)(packet + 2)) {
            FUN_00086c78();
            iVar9 = FUN_0007ce00();
            if (iVar9 == 0) {
                if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
            } else {
                if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
            }
        } else {
            if (0 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
            FUN_00086c78();
        }
        break;
    case 0x3a:
        if (0 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        break;
    case 0x3b:
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        break;
    case 0x3c:
        if (0 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        break;
    case 0x3d: {
        int16_t uVar16 = *(volatile int16_t *)(param_3 + 1);
        int16_t uVar13 = *(volatile int16_t *)(packet + 2);
        if (uVar16 != uVar13) {
            if (LVL_A < 2) { return; }
            if (LVL_B != 0) { FUN_00019c70(); return; }
            DEBUG_PRINT();
            return;
        }
        uVar1 = *(volatile uint8_t *)(param_3 + 5);
        FUN_00086c78();
        FUN_00086c1e();
        iVar9 = FUN_00016568();
        G_20018462 = uVar1;
        if (iVar9 == 1) { FUN_00048998(); }
        break;
    }
    case 0x3e:
        if (0 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        iVar9 = FUN_000167a8();
        FUN_00086c04();
        FUN_00086c04();
        break;
    default:
        if (1 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        FUN_00086fee();
        break;
    }

    {
        fp_t pcVar14 = *(fp_t *)(param_1 + 0xc);
        pcVar14();
    }
}

