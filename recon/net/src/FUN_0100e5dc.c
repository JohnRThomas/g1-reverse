/* net-core FUN_0100e5dc @ 0x100e5dc  (CFG-directed candidate) */
#include <stdint.h>

/* Raw back-map: FUN_0100e5dc @ 0x0100e5dc, exact extent 0x10 bytes. */
void FUN_0100e5dc(uint8_t *header, uint32_t type)
{
    *header = (uint8_t)((*header & 0xfcu) | (type & 3u));
}
