/* Full reconstruction FUN_00053d70 @ 0x00053d70 (226-byte exact extent). */
#include <stdint.h>

extern void *FUN_00053cd4(uint32_t opcode, uint32_t reserve);
extern void FUN_00086534(void *, uint32_t, uint32_t);
extern uint64_t FUN_0005ee18(void *);
extern uintptr_t FUN_0005f2d4(void *, uint32_t, uint32_t, uint32_t);
extern uint64_t FUN_0005f200(uintptr_t, uintptr_t, uint32_t, uint32_t);
extern int FUN_00072908(void *, uint32_t, uint32_t, uint32_t);
extern void FUN_0007e2fa(uintptr_t, ...);
extern void FUN_00080ea2(uintptr_t, uint32_t, const void *);
extern void FUN_0005f24c(void *);
extern void FUN_0007e2ec(uintptr_t, uint32_t) __attribute__((noreturn));

struct log_record4 { uint32_t count, format, opcode, status; };

int FUN_00053d70(uint32_t opcode, void *command, void **result)
{
    /* Reserve the complete aligned event object.  The firmware uses 28 bytes
     * of payload in a 32-byte stack slot. */
    uint8_t completion[32];
    uint8_t status;

    if (command == 0) {
        command = FUN_00053cd4(opcode, 0);
        if (command == 0)
            return -105;
    }
    FUN_00086534(completion, 0, 1);
    uint64_t indexed = FUN_0005ee18(command);
    int slot = (int)indexed;
    *(void **)(0x2000abf4u + (uint32_t)slot * 12u + 8u) = completion;
    uintptr_t token = FUN_0005f2d4(command, (uint32_t)(indexed >> 32), 1, 12);
    uint64_t inherited = FUN_0005f200(0x2000214cu, token, 1, 12);
    int wait_error = FUN_00072908(completion, (uint32_t)(inherited >> 32), 0x50000u, 0);
    if (wait_error != 0) {
        FUN_0007e2fa(0x00099cbdu, 0x000a7a10u, 0x000f2e84u, 0x152u);
        FUN_0007e2fa(0x000f301eu, opcode, wait_error);
        FUN_0007e2ec(0x00099cbdu, 0x152u);
    }
    status = *(volatile uint8_t *)(0x2000abf4u + (uint32_t)FUN_0005ee18(command) * 12u);
    if (status == 0) {
        if (result != 0) *result = command;
        else FUN_0005f24c(command);
        return 0;
    }
    struct log_record4 record = {4, 0x000f304au, opcode, status};
    FUN_00080ea2(0x00088138u, 0x2080u, &record);
    FUN_0005f24c(command);
    return status == 9 ? -111 : status == 13 ? -12 : -5;
}
