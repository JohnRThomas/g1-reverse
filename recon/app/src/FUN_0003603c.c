/* CPUAPP ui_ancs_notification_task @ 0x0003603c.
 * Raw/back-map identity: FUN_0003603c, exact extent 0x128 bytes. */
#include <stdint.h>

extern void FUN_000431c0(void);
extern void FUN_000438d0(void);
extern void FUN_000431b4(void *framebuffer);
extern void FUN_000432d0(void);
extern uint32_t FUN_00034390(void);
extern uint32_t FUN_00033cf8(void);
extern uint32_t FUN_000342e0(uintptr_t *message);
extern void FUN_00035f28(void *framebuffer, uint32_t message_index);
extern void FUN_00035afc(uint32_t message_index, uintptr_t message);
extern void DEBUG_PRINT(uintptr_t format, ...);
extern void FUN_00019c70(uintptr_t format, ...);

#define LOG_ROUTE (*(volatile uint32_t *)0x20007554u)
#define LAST_GROUP (*(volatile uint8_t *)0x200033d3u)
#define LAST_INDEX (*(volatile uint8_t *)0x200033d2u)
#define MESSAGE_ACTIVE (*(volatile uint8_t *)0x2001b80fu)
#define MESSAGE_MASK_ACTIVE (*(volatile uint8_t *)0x2001b80eu)
#define DISPLAY_DIRTY (*(volatile uint8_t *)0x20018d9fu)

#define TASK_LOG(format) do { \
    if (LOG_ROUTE == 0u) DEBUG_PRINT((format)); \
    else FUN_00019c70((format)); \
} while (0)

uint32_t ui_ancs_notification_task(uint8_t *canvas, uint32_t unused,
                                   uint32_t phase)
{
    uintptr_t message = 0u;
    uint32_t group;
    uint32_t index;

    (void)unused;
    if (phase == 2u) {
        TASK_LOG(0x000a8c60u);
        LAST_GROUP = 0xffu;
        LAST_INDEX = 0xffu;
        if (MESSAGE_ACTIVE == 0u)
            FUN_000431c0();
        else {
            FUN_000438d0();
            MESSAGE_ACTIVE = 0u;
        }
        DISPLAY_DIRTY = 0u;
        return 0u;
    }
    if (phase == 0u)
        return 0u;

    if (LAST_GROUP == 0xffu) {
        FUN_000431b4(canvas + 0x24);
        FUN_000432d0();
        FUN_000431c0();
    }
    group = FUN_00034390();
    index = FUN_00033cf8();
    if (LAST_GROUP == (uint8_t)group && LAST_INDEX == (uint8_t)index)
        return 0u;
    if (FUN_000342e0(&message) > 9u) {
        TASK_LOG(0x000a8c80u);
        LAST_GROUP = 0xffu;
        LAST_INDEX = 0xffu;
        return 0u;
    }
    if (*(volatile uint8_t *)(message + 0x0f) == 0u) {
        LAST_GROUP = 0xffu;
        LAST_INDEX = 0xffu;
        TASK_LOG(0x000a8c97u);
        return 0u;
    }
    if (*(volatile uint8_t *)(message + 0x0e) == 0u) {
        LAST_GROUP = 0xffu;
        LAST_INDEX = 0xffu;
        TASK_LOG(0x000a8cb6u);
        return 0u;
    }
    if (MESSAGE_MASK_ACTIVE != 0u) {
        FUN_00035f28(canvas + 0x24, index);
        MESSAGE_MASK_ACTIVE = 0u;
    }
    FUN_00035afc(index, message);
    LAST_GROUP = (uint8_t)group;
    LAST_INDEX = (uint8_t)index;
    DISPLAY_DIRTY = 0u;
    return 0u;
}
