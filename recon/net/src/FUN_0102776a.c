/* net-core FUN_0102776a @ 0x102776a  (CFG-directed candidate) */
#include <stdint.h>
void FUN_0102776a(uint16_t *entry, uint16_t key_length, uint16_t value_length)
{
    entry[1] = key_length;
    entry[0] = value_length;
}
