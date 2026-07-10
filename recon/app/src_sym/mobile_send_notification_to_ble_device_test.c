/* Reconstructed mobile_send_notification_to_ble_device_test @ 0x21c04  (parity: 300/300 trials, PROVEN) */

typedef unsigned int uint32_t;

extern uint32_t FUN_00064ca4(void);
extern void FUN_0008509e(uint32_t a, uint32_t b, uint32_t c);
extern void FUN_00085046(uint32_t a, uint32_t b, uint32_t c);
extern uint32_t FUN_00085014(uint32_t a);
extern void DEBUG_PRINT(uint32_t a, uint32_t b, uint32_t c);
extern void debug_print(void);
extern uint32_t strlen(uint32_t a);
extern void subcontracing_send_data_pkcs7(uint32_t a, uint32_t b, uint32_t c, uint32_t d);
extern void FUN_00064b1c(uint32_t a);

uint32_t mobile_send_notification_to_ble_device_test(uint32_t param_1, uint32_t param_2, uint32_t param_3)
{
    uint32_t uVar1;
    uint32_t uVar2;
    uint32_t uVar3;

    uVar1 = FUN_00064ca4();
    FUN_0008509e(uVar1, 0x9d759UL, 0x9d749UL);
    FUN_0008509e(uVar1, 0x9b257UL, param_1);
    FUN_0008509e(uVar1, 0x9d76cUL, 0x9d768UL);
    FUN_0008509e(uVar1, 0x9d775UL, param_2);
    FUN_0008509e(uVar1, 0xf3fdeUL, 0x9d77dUL);
    FUN_0008509e(uVar1, 0x9d790UL, 0x9d789UL);
    uVar2 = FUN_00064ca4();
    FUN_00085046(uVar2, 0x9d79dUL, uVar1);
    uVar1 = FUN_00085014(uVar2);
    if (*(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */ > 2) {
        if (*(volatile uint32_t*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
            DEBUG_PRINT(0x9d7aeUL, 0x9dfe8UL, uVar1);
        } else {
            debug_print();
        }
    }
    uVar3 = strlen(uVar1);
    subcontracing_send_data_pkcs7(uVar1, uVar3, 0x4b, param_3);
    FUN_00064b1c(uVar2);
    return 0;
}

