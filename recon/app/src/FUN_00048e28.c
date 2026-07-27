/* Reconstructed FUN_00048e28 @ 0x48e28 */
#include <stdint.h>

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_00048b5c(unsigned int, unsigned int, unsigned int, int);

unsigned int FUN_00048e28(unsigned int owner, unsigned int requested,
                         unsigned int payload, int mode)
{
    volatile uint8_t *state = (volatile uint8_t *)0x2001d447;
    volatile int *log_level = (volatile int *)0x2000230c;
    volatile int *alternate_log = (volatile int *)0x20007554;
    unsigned int current = state[1];

    if (mode == 2) {
        if (requested != current && current != 0) {
            if (*log_level > 0) {
                if (*alternate_log == 0)
                    DEBUG_PRINT(0x000ef7bb, 0x000f01d3, payload, 0);
                else
                    FUN_00019c70(0x000ef7bb, 0x000f01d3, payload,
                                 *alternate_log);

                if (*log_level > 0) {
                    current = state[1];
                    if (*alternate_log == 0)
                        DEBUG_PRINT(0x000ef7ef, 0x000f01d3, current, requested);
                    else
                        FUN_00019c70(0x000ef7ef, 0x000f01d3,
                                     current, requested);

                    if (*log_level > 0) {
                        current = state[1];
                        if (*alternate_log == 0)
                            DEBUG_PRINT(0x000ef87a, 0x000f01d3, current, 0);
                        else
                            FUN_00019c70(0x000ef87a, 0x000f01d3, current,
                                         *alternate_log);
                    }
                }
            }
            FUN_00048b5c(owner, requested, payload, 2);
            return 0xffffffff;
        }
    } else if (mode == 1) {
        if (requested != current && current != 0) {
            if (*log_level > 0) {
                if (*alternate_log == 0)
                    DEBUG_PRINT(0x000ef8d7, 0x000f01d3, payload, 0);
                else
                    FUN_00019c70(0x000ef8d7, 0x000f01d3, payload,
                                 *alternate_log);

                if (*log_level > 0) {
                    current = state[1];
                    if (*alternate_log == 0)
                        DEBUG_PRINT(0x000ef937, 0x000f01d3, current,
                                    requested);
                    else
                        FUN_00019c70(0x000ef937, 0x000f01d3, current,
                                     requested);

                    if (*log_level > 0) {
                        current = state[1];
                        if (*alternate_log == 0)
                            DEBUG_PRINT(0x000ef9bf, 0x000f01d3, current, 0);
                        else
                            FUN_00019c70(0x000ef9bf, 0x000f01d3, current,
                                         *alternate_log);
                    }
                }
            }

            FUN_00048b5c(owner, state[1], payload, 2);
            if (*log_level > 0) {
                if (*alternate_log == 0)
                    DEBUG_PRINT(0x000efa29, 0x000f01d3, requested, 0);
                else
                    FUN_00019c70(0x000efa29, 0x000f01d3, requested,
                                 *alternate_log);
            }
            state[1] = (uint8_t)requested;
        }
    } else if (requested != current && *log_level > 0) {
        if (*alternate_log == 0)
            DEBUG_PRINT(0x000efaa5, 0x000f01d3, payload, 0);
        else
            FUN_00019c70(0x000efaa5, 0x000f01d3, payload,
                         *alternate_log);

        if (*log_level > 0) {
            current = state[1];
            if (*alternate_log == 0)
                DEBUG_PRINT(0x000ef937, 0x000f01d3, current, requested);
            else
                FUN_00019c70(0x000ef937, 0x000f01d3, current, requested);
        }
    }

    FUN_00048b5c(owner, requested, payload, mode);
    return 0;
}
