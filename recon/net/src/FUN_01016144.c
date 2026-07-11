/* net-core FUN_01016144 @ 0x1016144
 * Missing internal tail-dispatch target recovered as a first-class function.
 * Code occupies 0x1016144..0x1016159; the global-base literal is at
 * 0x101615c and the next owned function starts at 0x1016160. */
#include <stdint.h>

extern void FUN_0100b594(void *context, uint32_t event);
extern void FUN_01014b18(uint32_t argument, uint32_t flags);

void FUN_01016144(void *context, uint32_t event)
{
    volatile uintptr_t *owner_slot = (volatile uintptr_t *)0x21000f68u;
    uintptr_t owner = owner_slot[1];

    if (*(volatile uint8_t *)(owner + 0x2eeu) == 0)
        FUN_0100b594(context, event);
    else
        FUN_01014b18(0, 0);
}
