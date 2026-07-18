/* net-core FUN_01016170 @ 0x1016170  (CFG-directed candidate) */
#include <stdint.h>
extern void FUN_01013e98(void *owner, uint32_t state);
void FUN_01016170(uint8_t *owner) {
    *(uint16_t *)(owner + 0xc5) = 0;
    owner[0xc9] = 0;
    FUN_01013e98(owner, owner[0x2eb] ? 2u : 3u);
}
