/* Reconstructed reset_all_usr_data @ 0x2316c. */
#include <stdint.h>

extern void FUN_00037098(void);
extern void FUN_0002f878(uint32_t);
extern void FUN_0007c26e(uint32_t);
extern void FUN_000244a8(uint32_t);
extern void FUN_00023b78(void);
extern void FUN_00023c88(void);
extern void FUN_00022ddc(void *);
extern void FUN_000230bc(void *);
extern void FUN_00016738(void);
extern void FUN_0005420c(uint32_t, uint32_t);
extern void FUN_000167f4(uint32_t);
extern uint32_t FUN_0004c0a8(uint32_t);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

#define LOG_LEVEL (*(volatile int32_t *)0x2000230c)
#define LOG_BACKEND (*(volatile uint32_t *)0x20007554)

void FUN_0002316c(uint8_t *user_data, int reset_radio)
{
    FUN_00037098();
    if (user_data[0] == 1) {
        FUN_0002f878(0xff);
        FUN_0007c26e(1000);
    }

    for (uint32_t slot = 0; slot != 4; ++slot) {
        FUN_000244a8(slot);
        FUN_0007c26e(200);
    }
    FUN_00023b78();
    FUN_0007c26e(200);
    FUN_00023c88();
    FUN_0007c26e(200);
    FUN_00022ddc(user_data);
    FUN_000230bc(user_data);
    FUN_0007c26e(500);
    FUN_00016738();
    FUN_0007c26e(500);
    FUN_0005420c(0, 0);

    if (!reset_radio)
        return;

    FUN_0007c26e(1000);
    FUN_000167f4(1);
    FUN_0007c26e(1000);
    if (LOG_LEVEL > 0) {
        if (LOG_BACKEND == 0)
            DEBUG_PRINT(0x0009e6d7, 0x0009e764);
        else
            FUN_00019c70(0x0009e6d7, 0x0009e764);
    }
    for (;;) {
        FUN_0007c26e(500);
        DEBUG_PRINT(FUN_0004c0a8(1));
    }
}
