/* Full reconstruction FUN_0007f064 @ 0x7f064 (exact extent 12 bytes). */
#include <stdint.h>
struct object_7f064 { uint32_t unused[2]; struct vtable_7f064 *vtable; };
struct vtable_7f064 { uint32_t unused[3]; uint32_t *(*get_value)(void); };
uint32_t FUN_0007f064(struct object_7f064 *object)
{
    return *object->vtable->get_value();
}
