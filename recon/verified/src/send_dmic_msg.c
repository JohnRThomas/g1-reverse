/* Reconstructed send_dmic_msg @ 0x19ed4. */

#include <stdint.h>

struct dmic_message {
    uint32_t header;
    uint8_t tail[199];
};

typedef int (*dmic_send_fn)(const void *message, unsigned int length);

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern void *FUN_000167a8(void);
extern unsigned int FUN_0002ecf4(void);
extern int FUN_0002ed00(void *payload);
extern void FUN_0007cbfe(void *state, int enabled);
extern void FUN_00086c78(void *destination, int value, unsigned int length);
extern unsigned long long thunk_FUN_00074f68(void);

int send_dmic_msg(uint8_t *transport)
{
    volatile uint8_t *sequence = (volatile uint8_t *)0x20010321UL;
    volatile int *failure_count = (volatile int *)0x20007558UL;
    struct dmic_message message;
    uint8_t old_sequence;
    int result;

    message.header = 0;
    FUN_00086c78(message.tail, 0, sizeof(message.tail));
    ((uint8_t *)&message.header)[0] = 0xf1;

    do {
        ((uint8_t *)&message.header)[1] = *sequence;
        if (FUN_0002ecf4() == 0) {
            return 0;
        }

        result = FUN_0002ed00((uint8_t *)&message + 2);
        if (result != 0) {
            return result;
        }

        result = (*(dmic_send_fn *)(transport + 0x0c))(&message, 202);
        if (result < 0 && ++*failure_count > 9) {
            FUN_0007cbfe(FUN_000167a8(), 1);
            if (*(volatile int *)0x2000230cUL > 0) {
                if (*(volatile int *)0x20007554UL == 0) {
                    DEBUG_PRINT(0x0009b45eUL, 0x0009e0a4UL,
                                *failure_count);
                } else {
                    FUN_00019c70(0x0009b45eUL, 0x0009e0a4UL,
                                 *failure_count);
                }
            }
            *failure_count = 0;
            return result;
        }

        if (*(volatile int *)0x2000755cUL + 1 < 100) {
            ++*(volatile int *)0x2000755cUL;
        } else {
            unsigned long long timestamp;
            unsigned long long scaled_timestamp;
            int report_count;

            *(volatile int *)0x2000755cUL = 0;
            timestamp = thunk_FUN_00074f68();
            report_count = *(volatile int *)0x20007560UL;
            *(volatile int *)0x20007560UL = report_count + 1;
            if (*(volatile int *)0x2000230cUL > 0) {
                scaled_timestamp = (timestamp * 1000ULL + 0x7fffULL) >> 15;
                if (*(volatile int *)0x20007554UL == 0) {
                    DEBUG_PRINT(0x0009b482UL, 0x0009e0a4UL,
                                (report_count + 1) * 100, *failure_count,
                                (uint32_t)scaled_timestamp,
                                (uint32_t)(scaled_timestamp >> 32));
                } else {
                    FUN_00019c70(0x0009b482UL, 0x0009e0a4UL,
                                 (report_count + 1) * 100, *failure_count,
                                 (uint32_t)scaled_timestamp,
                                 (uint32_t)(scaled_timestamp >> 32));
                }
            }
        }

        old_sequence = *sequence;
        *sequence = old_sequence + 1;
    } while (((old_sequence + 1) & 3) != 0);

    return 0;
}
