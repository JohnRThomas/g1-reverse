/* Reconstructed FUN_0002a65c @ 0x2a65c */
#include <stdint.h>

extern void DEBUG_PRINT(uint32_t, uint32_t);
extern void FUN_00019c70(uint32_t, uint32_t);
extern void FUN_00023a54(void *);
extern void FUN_0002ace0(void);
extern int FUN_00032ee4(void);
extern void FUN_00032fe8(void);
extern void FUN_0003304c(void);
extern void FUN_00047ad0(void *);
extern void FUN_00049638(void *);
extern void FUN_0007cb66(uint32_t, uint32_t, uint32_t, uint32_t,
                         void *, int32_t, uint32_t, uint32_t);
extern void FUN_000864c2(uint32_t);

#define CREATE_DISPATCH_THREAD(control, stack, stack_size, entry, context, priority) \
    FUN_0007cb66((control), (stack), (stack_size), (entry), \
                 (context), (priority), 0, 0)

void FUN_0002a65c(char *dispatch_mode)
{
    int battery_critical;
    uint32_t final_entry;

    if (*(volatile int *)0x2000230cUL > 2) {
        if (*(volatile uint32_t *)0x20007554UL == 0)
            DEBUG_PRINT(0x000a18bfUL, 0x000a1a98UL);
        else
            FUN_00019c70(0x000a18bfUL, 0x000a1a98UL);
    }

    FUN_000864c2(0x20007b3cUL);
    FUN_00023a54(dispatch_mode);
    FUN_0002ace0();

    battery_critical = FUN_00032ee4();
    if (battery_critical == 0) {
        CREATE_DISPATCH_THREAD(0x200046b8UL, 0x20026a68UL, 0xc00,
                               0x0002a8d9UL, dispatch_mode, -10);
        CREATE_DISPATCH_THREAD(0x200041a8UL, 0x20024868UL, 0x400,
                               0x000286f9UL, dispatch_mode, -10);
    } else {
        CREATE_DISPATCH_THREAD(0x200046b8UL, 0x20026a68UL, 0xc00,
                               0x0002685dUL, dispatch_mode, -10);
        FUN_00032fe8();
        FUN_0003304c();
    }

    CREATE_DISPATCH_THREAD(0x200040d0UL, 0x20023c68UL, 0xc00,
                           0x0002a4f5UL, 0, -9);

    if ((uint8_t)dispatch_mode[0] == 1 || (uint8_t)dispatch_mode[0] == 2) {
        CREATE_DISPATCH_THREAD(0x200045e0UL, 0x20026268UL, 0x800,
                               0x00028bedUL, dispatch_mode, -13);
        CREATE_DISPATCH_THREAD(0x20004508UL, 0x20025a68UL, 0x800,
                               0x0002692dUL, dispatch_mode, -12);
        if ((uint8_t)dispatch_mode[0] == 1) {
            FUN_00047ad0(dispatch_mode);
        } else {
            CREATE_DISPATCH_THREAD(0x20004430UL, 0x20025468UL, 0x600,
                                   0x00027cfdUL, dispatch_mode, -11);
        }
        FUN_00049638(dispatch_mode);
    }

    final_entry = FUN_00032ee4() == 1 ? 0x00028a1dUL : 0x0002a0d9UL;
    CREATE_DISPATCH_THREAD(0x20004358UL, 0x20025068UL, 0x400,
                           final_entry, dispatch_mode, -14);
    CREATE_DISPATCH_THREAD(0x20004280UL, 0x20024c68UL, 0x400,
                           0x0002955dUL, dispatch_mode, -13);
}
