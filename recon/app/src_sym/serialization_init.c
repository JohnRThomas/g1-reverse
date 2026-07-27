/* Reconstructed serialization_init @ 0x25c54  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);
extern int ipc_service_open_instance(uint32_t);
extern unsigned long long FUN_0004cbec(uint32_t, uint32_t, uint32_t);
extern void FUN_00072908(uint32_t, int, int, int);

unsigned int serialization_init(void)
{
    volatile int *piVar1 = (volatile int*)0x2000230cUL;
    int iVar2;
    unsigned int format_string;
    unsigned long long uVar3;

    if (2 < *piVar1) {
        if (*(volatile int*)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
            DEBUG_PRINT(0x0009f5ecUL, 0x0009f6f1UL);
        } else {
            debug_print(0x0009f5ecUL, 0x0009f6f1UL);
        }
    }
    iVar2 = ipc_service_open_instance(0x00087c08UL);
    if ((iVar2 < 0) && (iVar2 != -0x78)) {
        if (*piVar1 < 1) {
            return 0xffffffffUL;
        }
        iVar2 = *(volatile int*)0x20007554UL /* device_info.is_debug @+0xb58 */;
        format_string = 0x0009f611UL;
    } else {
        if (2 < *piVar1) {
            if (*(volatile int*)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
                DEBUG_PRINT(0x0009f63cUL, 0x0009f6f1UL);
            } else {
                debug_print(0x0009f63cUL, 0x0009f6f1UL);
            }
        }
        uVar3 = FUN_0004cbec(0x00087c08UL, 0x20007a78UL /* device_info_t+0x107c (unmapped region) */, 0x200023dcUL);
        if (-1 < (int)uVar3) {
            FUN_00072908(0x200039c8UL, (int)(uVar3 >> 32), -1, -1);
            *(volatile int*)0x20007a80UL /* device_info_t+0x1084 (unmapped region) */ = 1;
            if (1 < *piVar1) {
                if (*(volatile int*)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
                    DEBUG_PRINT(0x0009f67eUL, 0x0009f6f1UL);
                } else {
                    debug_print(0x0009f67eUL, 0x0009f6f1UL);
                }
            }
            return 0;
        }
        if (*piVar1 < 1) {
            return 0xffffffffUL;
        }
        iVar2 = *(volatile int*)0x20007554UL /* device_info.is_debug @+0xb58 */;
        format_string = 0x0009f64fUL;
    }
    if (iVar2 == 0) {
        DEBUG_PRINT(format_string, 0x0009f6f1UL);
    } else {
        debug_print(format_string, 0x0009f6f1UL);
    }
    return 0xffffffffUL;
}

