/* OpenAMP rpmsg_unregister_endpoint @ 0x0103ad56, exact extent 0x52.
 * Raw/address backmaps:
 *   FUN_0103ad56@0x0103ad56
 *   metal_mutex_acquire = FUN_0103ad4a@0x0103ad4a
 *   metal_mutex_release = FUN_01036824@0x01036824
 */
#include <stdint.h>
#define rpmsg_unregister_endpoint FUN_0103ad56

extern void FUN_0103ad4a(void *lock);
extern void FUN_01036824(void *lock);
#define metal_mutex_acquire FUN_0103ad4a
#define metal_mutex_release FUN_01036824

void rpmsg_unregister_endpoint(uint8_t *endpoint)
{
    uint8_t *device = *(uint8_t **)(endpoint + 0x20);
    uint32_t address;
    uint8_t *next;
    uint8_t *previous;

    metal_mutex_acquire(device + 0x58);
    address = *(uint32_t *)(endpoint + 0x24) - 0x400u;
    if (address < 128u) {
        uint32_t *bitmap = (uint32_t *)(device + 0x48);
        bitmap[address >> 5] &= ~(1u << (address & 31u));
    }

    next = *(uint8_t **)(endpoint + 0x34);
    previous = *(uint8_t **)(endpoint + 0x38);
    *(uint8_t **)(next + 4) = previous;
    *(uint8_t **)previous = next;
    *(uint8_t **)(endpoint + 0x34) = endpoint + 0x34;
    *(uint8_t **)(endpoint + 0x38) = endpoint + 0x34;
    *(uint32_t *)(endpoint + 0x20) = 0u;
    metal_mutex_release(device + 0x58);
}
