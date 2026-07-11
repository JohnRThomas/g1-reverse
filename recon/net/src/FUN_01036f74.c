/* net-core FUN_01036f74 @ 0x1036f74 */
#include <stdint.h>

extern void FUN_01036f24(void *node);
extern void FUN_01039bbe(uintptr_t file, uintptr_t message, unsigned line, ...);
extern void FUN_01039bb0(uintptr_t message, unsigned line);

void FUN_01036f74(int force_advance)
{
    uint8_t *state = (uint8_t *)0x21004b28;
    uint8_t *head = *(uint8_t **)(state + 8);
    uint8_t *candidate = *(uint8_t **)(state + 0x18);

    if (candidate == state + 0x18 || candidate == 0)
        candidate = *(uint8_t **)(state + 0x0c);

    if (force_advance == 0) {
        if (head == 0) {
            FUN_01039bbe(0x0103d2a7, 0x0103eb0e, 0x8f, 0);
            FUN_01039bb0(0x0103eb0e, 0x8f);
        }
        if ((head[0x0d] & 0x1f) == 0 &&
            *(uint32_t *)(candidate + 0x18) == 0 &&
            *(uint16_t *)(head + 0x0e) > 0x7f) {
            *(uint8_t **)(state + 0x14) = head;
            return;
        }
    }

    if (candidate != head)
        FUN_01036f24(candidate);
    *(uint8_t **)(state + 0x14) = candidate;
}
