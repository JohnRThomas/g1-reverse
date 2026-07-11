/* net-core FUN_0103afac @ 0x103afac */
#include <stdint.h>
extern void FUN_0103aec6(void *);
extern uint32_t FUN_0103ac46(void *, uint32_t);
extern void FUN_010353ec(void *, uint32_t, uint32_t);
extern void FUN_0103acca(void *);
extern void FUN_0103aec2(void *);

void FUN_0103afac(void *object, const uint8_t *record)
{
    uint8_t *base = object;
    uint32_t id = *(const uint32_t *)(record - 8) & 0xffffu;
    void *lock = base + 0x58;
    FUN_0103aec6(lock);
    void *channel = *(void **)(base + 0xa4);
    uint32_t value = FUN_0103ac46(channel, id);
    if (*(uint32_t *)(*(uint8_t **)(base + 0xa0) + 0x18) == 1)
        FUN_010353ec(channel, id, value);
    FUN_0103acca(channel);
    FUN_0103aec2(lock);
}
